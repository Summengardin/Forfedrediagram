#pragma once // FORFEDREDIAGRAM_NODE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../include/ATree/globals.hpp"
#include "json.hpp"

using json = nlohmann::json;

template <class T> class Node
{
  public:

    explicit Node(const json &jsonFile) { this->fromJson(jsonFile); }

    explicit Node(const T &p)
    {
        _data = std::make_shared<T>(p);
        _treeIndex = TreeId();
    }

    void fromJson(const json &jsonFile)
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

    [[nodiscard]] json toJson() const
    {
        int leftIndex, rightIndex;
        if (_leftChild)
            leftIndex = _leftChild->_treeIndex;
        else
            leftIndex = -1;

        if (_rightChild)
            rightIndex = _rightChild->_treeIndex;
        else
            rightIndex = -1;

        json j = json{{"data", _data->toJson()},
                      {"treeIndex", _treeIndex},
                      {"leftIdx", leftIndex},
                      {"rightIdx", rightIndex},
                      {"isRoot", _isRoot}};
        return j;
    }

    void setData(const T &p) { _data = std::make_shared<T>(p); }

    bool addChild(std::shared_ptr<Node> n)
    {
        // Returns true if successfully added child, false if not.

        if (!_leftChild)
            _leftChild = n;
        else if (!_rightChild)
            _rightChild = n;
        else
            return false;
        return true;
    }

    bool addChild(const T &p)
    {
        // Returns true if successfully added child, false if not.
        auto child = std::make_shared<Node>(Node(p));
        return addChild(child);
    }

    void setRootFlag(bool rootFlag) { _isRoot = rootFlag; }

    void setLeft(std::shared_ptr<Node> node) { _leftChild = node; }

    void setRight(std::shared_ptr<Node> node) { _rightChild = node; }

    void updateIndex() { _treeIndex = TreeId(); }

    [[nodiscard]] unsigned int getIndex() const { return _treeIndex; }

    [[nodiscard]] const T *getData() const { return _data.get(); }

    [[nodiscard]] T *getData() { return _data.get(); }

    [[nodiscard]] const Node *leftChild() const { return _leftChild.get(); }

    [[nodiscard]] Node *leftChild() { return _leftChild.get(); }

    [[nodiscard]] const Node *rightChild() const { return _rightChild.get(); }

    [[nodiscard]] Node *rightChild() { return _rightChild.get(); }

    [[nodiscard]] std::shared_ptr<Node> leftChildOwnership() { return _leftChild; }

    [[nodiscard]] std::shared_ptr<Node> rightChildOwnership() { return _rightChild; }

    [[nodiscard]] bool isLeaf() const { return (!_leftChild && !_rightChild); }

    [[nodiscard]] bool isRoot() const { return _isRoot; }

    friend std::ostream &operator<<(std::ostream &os, Node &n)
    {
        os << "[Node] Idx: " << n.getIndex() << ", contains: " << *n.getData();
        return os;
    }

  private:
    bool _isRoot{false};
    unsigned int _treeIndex;
    std::shared_ptr<T> _data;
    std::shared_ptr<Node> _leftChild;
    std::shared_ptr<Node> _rightChild;
};

// FORFEDREDIAGRAM_NODE_HPP