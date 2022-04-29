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

        if (jsonFile.contains("treeIndex"))
        {
            if (jsonFile.at("treeIndex").is_number_integer())
            {
                _treeIndex = jsonFile.at("treeIndex");
                TreeId.update(_treeIndex);
            }
            else
            {
                _treeIndex = TreeId();
            }
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
        if (_left)
            leftIndex = _left->_treeIndex;
        else
            leftIndex = -1;

        if (_right)
            rightIndex = _right->_treeIndex;
        else
            rightIndex = -1;

        json j = json{
            {"_data", _data->toJson()},
            {"treeIndex", _treeIndex},
            {"leftIdx", leftIndex},
            {"rightIdx", rightIndex},
            {"isRoot", _isRoot}
        };
        return j;
    }

    void setData(const T &p)
    {
        _data = std::make_shared<T>(p);
    }

    bool addParent(std::shared_ptr<Node> n)
    {
        // Returns true if successfully added parent, false if not.
        if (!_left)
        {
            _left = n;
        }
        else if (!_right)
        {
            _right = n;
        }
        else
        {
            return false;
        }
        return true;
    }

    bool addParent(const T &p)
    {
        // Returns true if able to set parent

        if (!_left)
        {
            _left = std::make_shared<Node>(Node(p));
            return true;
        }
        else if (!_right)
        {
            _right = std::make_shared<Node>(Node(p));
            return true;
        }

        return false;
    }

    void traverseDFS(const std::function<void(Node *)> &f)
    {
        // DepthFirst - PreOrder

        f(this);

        if (_left)
            _left->traverseDFS(f);

        if (_right)
            _right->traverseDFS(f);
    }

    void traverseDFSWithDepth(const std::function<void(Node *, int)> &f, int depth = 0)
    {
        // DepthFirst - PreOrder. Used for printing with depth information

        f(this, depth);

        if (_left)
            _left->traverseDFSWithDepth(f, depth + 1);

        if (_right)
            _right->traverseDFSWithDepth(f, depth + 1);
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
        _left = node;
    }

    void setRight(std::shared_ptr<Node> node)
    {
        _right = node;
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
        return *_left;
    }

    [[nodiscard]] const Node &viewLeft() const
    {
        return *_left;
    }

    [[nodiscard]] Node *leftPtr() const
    {
        return _left.get();
    }

    [[nodiscard]] Node &getRight()
    {
        return *_right;
    }

    [[nodiscard]] const Node &viewRight() const
    {
        return *_right;
    }

    [[nodiscard]] Node *rightPtr() const
    {
        return _right.get();
    }

    [[nodiscard]] bool isLeaf() const
    {
        return (!_left && !_right);
    }

    [[nodiscard]] bool isRoot() const
    {
        return _isRoot;
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getParents()
    {
        return {_left, _right};
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
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};

// FORFEDREDIAGRAM_NODE_HPP