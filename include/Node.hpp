#pragma once // FORFEDREDIAGRAM_NODE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "globals.hpp"
#include "json.hpp"

using json = nlohmann::json;

template <class T> class Node
{
  public:
    explicit Node(const json &jsonFile)
    {
        _data = std::make_shared<T>(jsonFile["data"]);

        if (jsonFile.contains("treeIndex") && jsonFile.at("treeIndex").is_number_integer())
        {
            _treeIndex = jsonFile.at("treeIndex");
            TreeId.update(_treeIndex);
        }
        else
        {
            _treeIndex = TreeId();
        }
    }

    explicit Node(const T &p)
    {
        _data = std::make_shared<T>(p);
        _treeIndex = TreeId();
    }

    [[nodiscard]] json toJson() const
    {
        int leftIndex, rightIndex;
        if (_leftChildNode)
            leftIndex = _leftChildNode->_treeIndex;
        else
            leftIndex = -1;

        if (_rightChildNode)
            rightIndex = _rightChildNode->_treeIndex;
        else
            rightIndex = -1;

        json j = json{{"_data", _data->toJson()},
                      {"treeIndex", _treeIndex},
                      {"leftIdx", leftIndex},
                      {"rightIdx", rightIndex},
                      {"isRoot", _isRoot}};
        return j;
    }

    void setData(const T &p)
    {
        _data = std::make_shared<T>(p);
    }

    bool addChild(std::shared_ptr<Node> n)
    {
        // Returns true if successfully added child, false if not.

        if (!_leftChildNode)
            _leftChildNode = n;
        else if (!_rightChildNode)
            _rightChildNode = n;
        else
            return false;

        return true;
    }

    bool addChild(const T &p)
    {
        // Returns true if successfully added child, false if not.

        if (!_leftChildNode)
        {
            _leftChildNode = std::make_shared<Node>(Node(p));
            return true;
        }
        else if (!_rightChildNode)
        {
            _rightChildNode = std::make_shared<Node>(Node(p));
            return true;
        }

        return false;
    }

    void traverseDFS(const std::function<void(Node *)> &f)
    {
        // DepthFirst - PreOrder

        f(this);

        if (_leftChildNode)
            _leftChildNode->traverseDFS(f);

        if (_rightChildNode)
            _rightChildNode->traverseDFS(f);
    }

    void traverseDFSWithDepth(const std::function<void(Node *, int)> &f, int depth = 0)
    {
        // DepthFirst - PreOrder. Used for printing with depth information

        f(this, depth);

        if (_leftChildNode)
            _leftChildNode->traverseDFSWithDepth(f, depth + 1);

        if (_rightChildNode)
            _rightChildNode->traverseDFSWithDepth(f, depth + 1);
    }

    void traverseBFS(const std::function<void(Node *)> &f)
    {
    }

    void setRootFlag(bool rootFlag)
    {
        _isRoot = rootFlag;
    }

    void setLeft(std::shared_ptr<Node> node)
    {
        _leftChildNode = node;
    }

    void setRight(std::shared_ptr<Node> node)
    {
        _rightChildNode = node;
    }

    void setIdx(unsigned int index)
    {
        _treeIndex = index;
    }

    [[nodiscard]] unsigned int getIdx() const
    {
        return _treeIndex;
    }

    [[nodiscard]] const T *viewData() const
    {
        return _data.get();
    }

    [[nodiscard]] T *getData()
    {
        return _data.get();
    }

    [[nodiscard]] Node &getLeft()
    {
        return *_leftChildNode;
    }

    [[nodiscard]] const Node &viewLeft() const
    {
        return *_leftChildNode;
    }

    [[nodiscard]] Node *leftChild() const
    {
        return _leftChildNode.get();
    }

    [[nodiscard]] Node &getRight()
    {
        return *_rightChildNode;
    }

    [[nodiscard]] const Node &viewRight() const
    {
        return *_rightChildNode;
    }

    [[nodiscard]] Node *rightChild() const
    {
        return _rightChildNode.get();
    }

    [[nodiscard]] bool isLeaf() const
    {
        return (!_leftChildNode && !_rightChildNode);
    }

    [[nodiscard]] bool isRoot() const
    {
        return _isRoot;
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getParents()
    {
        return {_leftChildNode, _rightChildNode};
    };

    friend std::ostream &operator<<(std::ostream &os, Node &n)
    {
        os << "[Node] Idx: " << n.getIdx() << ", contains: " << *n.viewData();
        return os;
    }

  private:
    bool _isRoot{false};
    unsigned int _treeIndex;
    std::shared_ptr<T> _data;
    std::shared_ptr<Node> _leftChildNode;
    std::shared_ptr<Node> _rightChildNode;
};

// FORFEDREDIAGRAM_NODE_HPP