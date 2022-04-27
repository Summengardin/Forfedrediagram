#pragma once// FORFEDREDIAGRAM_NODE_HPP


#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Person.hpp"
#include "globals.hpp"
#include "json.hpp"

using json = nlohmann::json;

template<class T>
class Node
{
public:
    explicit Node(const json &j)
    {
        data = std::make_shared<T>(j["data"]);
        //data->fromJson(j["data"]);
        //        if(j.contains("treeIdx") && j["treeIdx"] != nullptr)
        //            _treeIdx = j["treeIdx"];
        if (j.contains("treeIndex") && j["treeIndex"].is_string())
        {
            _treeIdx = j["treeIndex"];
            TreeId.update(_treeIdx);
        } else
            _treeIdx = TreeId();
    }


    explicit Node(const T &p)
    {
        data = std::make_shared<T>(p);
        _treeIdx = TreeId();
    }


    [[nodiscard]] json toJson() const
    {
        int leftIndex, rightIndex;
        if (_left)
            leftIndex = _left->_treeIdx;
        else
            leftIndex = -1;

        if (_right)
            rightIndex = _right->_treeIdx;
        else
            rightIndex = -1;


        json j = json{
                {"data", data->toJson()},
                {"treeIdx", _treeIdx},
                {"leftIdx", leftIndex},
                {"rightIdx", rightIndex},
        };
        return j;
    }


    void setData(const T &p)
    {
        data = std::make_shared<T>(p);
    }


    bool addParent(std::shared_ptr<Node> n)
    {
        // Returns true if successfully added parent, false if not.
        if (!_left)
        {
            _left = n;
        } else if (!_right)
        {
            _right = n;
        } else{

            return false;
        }
        return true;
    }


    void addParent(const T &p)
    {

        if (!_left)
        {
            _left = std::make_shared<Node>(Node(p));
        } else if (!_right)
        {
            _right = std::make_shared<Node>(Node(p));
        } else
        {
            std::cout << "T har allerede to foreldre" << std::endl;
        }
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


    void setLeft(std::shared_ptr<Node> &node)
    {
        _left = node;
    }


    void setRight(std::shared_ptr<Node> &node)
    {
        _right = node;
    }


    void setIdx(unsigned int index)
    {
        _treeIdx = index;
    }


    [[nodiscard]] unsigned int getIdx() const
    {
        return _treeIdx;
    }

    [[nodiscard]] const T *viewData() const
    {
        return data.get();
    }

    [[nodiscard]] T *getData()
    {
        return data.get();
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

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getParents()
    {
        return {_left, _right};
    };

    friend std::ostream &operator<<(std::ostream &os, Node &n)
    {
        os << "[Node] Idx: " << n.getIdx() << ", contains: " << n.viewData();
        return os;
    }

private:
    unsigned int _treeIdx;
    unsigned int id;
    std::shared_ptr<T> data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};


//FORFEDREDIAGRAM_NODE_HPP