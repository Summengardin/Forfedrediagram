#pragma once // FORFEDREDIAGRAM_TREE_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "globals.hpp"
#include "helpers.hpp"

#include "json/json.hpp"
using json = nlohmann::json;


namespace ATree
{

template <class T> class Node
{
  public:
    explicit Node(const T &data) : _data(std::make_shared<T>(data)), _treeIndex(TreeId()) {}


    explicit Node(const json &jsonFile) : _treeIndex(TreeId()) { this->fromJson(jsonFile); }


    void fromJson(const json &jsonFile)
    {
        _data = std::make_shared<T>(jsonFile["data"]);

        /*if (jsonFile.contains("treeIndex") && jsonFile.at("treeIndex").is_number_integer())
        {
            _treeIndex = jsonFile.at("treeIndex");
            TreeId.update(_treeIndex);
        }
        else
        {
            _treeIndex = TreeId();
        }*/
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

    [[nodiscard]] bool contains(const std::string &str) const
    {
        std::ostringstream nodeData;
        nodeData << *getData();

        return nodeData.str().find(str) != std::string::npos;
    }


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


template <class T> class Tree
{

  public:
    enum DFSOrder
    {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER,
    };


    void fillFromJson(const json &treeJson)
    {
        // Fill tree from json-file. Must be compatible, preferably exported from tree
        // It is done by first extracting all nodes from the tree into a map.
        // Then looping through the indexes and assigning children based on the indexes

        // Tree settings
        if (treeJson["tree"]["settings"]["globalIndent"] != nullptr)
            globalIndent = treeJson["tree"]["settings"]["globalIndent"];

        std::unordered_map<int, std::shared_ptr<Node<T>>> nodes;

        struct childrenIndex
        {
            int left, right;
        };

        // Extract nodes
        std::unordered_map<int, childrenIndex> childrenIndexes;
        for (auto &nodeData : treeJson["nodes"])
        {
            std::shared_ptr<Node<T>> newNode{std::make_shared<Node<T>>(nodeData)};

            std::cout << *newNode << std::endl;

            if (nodeData.contains("isRoot") && nodeData.at("isRoot").is_boolean() && nodeData.at("isRoot"))
            {
                setRoot(newNode);
                _size++;
            }

            nodes[nodeData["treeIndex"]] = newNode;

            // Store index of parents. If no parent, index is -1
            if (nodeData.contains("leftIdx") && nodeData["leftIdx"].is_number_integer())
                childrenIndexes[nodeData["treeIndex"]].left = nodeData["leftIdx"];
            else
                childrenIndexes[nodeData["treeIndex"]].left = -1;

            if (nodeData.contains("rightIdx") && nodeData["rightIdx"].is_number_integer())
                childrenIndexes[nodeData["treeIndex"]].right = nodeData["rightIdx"];
            else
                childrenIndexes[nodeData["treeIndex"]].right = -1;
        }

        for (auto [index, node] : nodes)
        {

            // Get index of parents
            int leftChildIdx = childrenIndexes[index].left;
            int rightChildIdx = childrenIndexes[index].right;

            // Add parents if they exist
            if (leftChildIdx != -1)
            {
                node->setLeft(nodes.at(leftChildIdx));
                ++_size;
            }
            if (rightChildIdx != -1)
            {
                node->setRight(nodes.at(rightChildIdx));
                ++_size;
            }
        }
    }


    [[nodiscard]] json toJson()
    {
        json nodes;
        traverseDFS(getRoot(), [&nodes](Node<T> *node) { nodes.push_back(node->toJson()); });

        // clang-format off
        json j = json{
                    {"nodes", nodes},
                    {"tree", {
                        {"settings", {
                            {"globalIndent", globalIndent}
                                    }}}}};
        // clang-format on
        return j;
    }


    void setRoot(std::shared_ptr<Node<T>> n)
    {
        if (_root)
            _root->setRootFlag(false);

        _root = n;
        _root->setRootFlag(true);
    }

    T removeNode(size_t index)
    {
        T removedData;

        size_t prevIndex = _root->getIndex();

        if (prevIndex == index)
        {
            // If root has index searched for

            removedData = *_root->getData();
            if (_root->isLeaf())
            {
                setRoot(nullptr);
            }
            else
            {
                T dummy("Dummy", std::to_string(DummyId()));
                _root->setData(dummy);
            }
        }
        else
        {
            traverseDFS(_root.get(), [index, &prevIndex, &removedData](Node<T> *node) {
                if (node->leftChild() && node->leftChild()->getIndex() == index)
                {
                    removedData = *node->leftChild()->getData();
                    if (node->leftChild()->isLeaf())
                    {
                        node->setLeft(nullptr);
                    }
                    else
                    {
                        T dummy("Dummy", std::to_string(DummyId()));
                        node->leftChild()->setData(dummy);
                    }
                    return;
                }

                if (node->rightChild() && node->rightChild()->getIndex() == index)
                {

                    removedData = *node->rightChild()->getData();
                    if (node->rightChild()->isLeaf())
                    {
                        node->setRight(nullptr);
                    }
                    else
                    {
                        T dummy("Dummy", std::to_string(DummyId()));
                        node->rightChild()->setData(dummy);
                    }
                    return;
                }
            });
        }

        return removedData;
    }


    [[nodiscard]] bool isEmpty() const { return !_root; }


    // TODO
    [[nodiscard]] T &getDataAt(unsigned int index) { return *_root->getData(); }


    // TODO
    [[nodiscard]] const T &getDataAt(unsigned int index) const { return *_root->getData(); }


    [[nodiscard]] const Node<T> *getRoot() const { return _root.get(); }


    [[nodiscard]] Node<T> *getRoot() { return _root.get(); }


    [[nodiscard]] std::shared_ptr<Node<T>> getRootOwnership() { return _root; }


    void traverseDFS(Node<T> *node, const std::function<void(Node<T> *)> &func, DFSOrder order = DFSOrder::PRE_ORDER)
    {
        if (!node)
            return;

        if (order == DFSOrder::PRE_ORDER)
            func(node);

        traverseDFS(node->leftChild(), func, order);

        if (order == DFSOrder::IN_ORDER)
            func(node);

        traverseDFS(node->rightChild(), func, order);

        if (order == DFSOrder::POST_ORDER)
            func(node);
    }


    void traverseDFSWithDepth(Node<T> *node, const std::function<void(Node<T> *, int)> &func,
                              DFSOrder order = DFSOrder::PRE_ORDER, int depth = 0)
    {
        if (!node)
            return;

        if (order == DFSOrder::PRE_ORDER)
            func(node, depth);

        traverseDFSWithDepth(node->leftChild(), func, order, depth + 1);

        if (order == DFSOrder::IN_ORDER)
            func(node, depth);

        traverseDFSWithDepth(node->rightChild(), func, order, depth + 1);

        if (order == DFSOrder::POST_ORDER)
            func(node, depth);
    }


    [[nodiscard]] int getSettingIndent() const { return globalIndent; }


    void setSettingIndent(int indent) { globalIndent = indent; }


    void traverseBFS(const std::function<void(Node<T> *)> &func)
    {
        std::queue<Node<T> *> Q;

        if (_root)
            Q.push(_root.get());

        while (!Q.empty())
        {
            Node<T> *currentNode = Q.front();

            if (currentNode->leftChild())
                Q.push(currentNode->leftChild());
            if (currentNode->rightChild())
                Q.push(currentNode->rightChild());

            func(currentNode);

            Q.pop();
        }
    }


    std::vector<Node<T> *> listAllNodes()
    {
        std::vector<Node<T> *> allNodes;

        if (_root)
            traverseDFS(getRoot(), [&allNodes](Node<T> *node) { allNodes.push_back(node); });

        return allNodes;
    }


    Node<T> *findNodeByIndex(unsigned int index)
    {
        if (_root->getIndex() == index)
        {
            return _root.get();
        }
        Node<T> *found = nullptr;
        traverseDFS(getRoot(), [&found, index](Node<T> *node) {
            if (node->getIndex() == index)
            {
                found = node;
                return;
            }
        });

        return found;
    }


    std::vector<Node<T> *> findNodeByString(const std::string &str)
    {
        // Will return a vector with pointers to all nodes containing str

        std::vector<Node<T> *> nodes;
        if (!_root)
        {
            return nodes;
        }

        Node<T> *found = nullptr;
        traverseBFS([&found, str, &nodes](Node<T> *node) {
            if (node->contains(str))
                nodes.push_back(node);
        });

        return nodes;
    }


/*    [[nodiscard]] size_t getSize() const
    {
        int size = 0;
        traverseDFS(getRoot(), [&size](Node<T> *node) { size++; });
        return size;
    };*/


    void addChild(int nodeIndex, std::shared_ptr<Node<T>> node)
    {
        Node<T> *childNode = findNodeByIndex(nodeIndex);
        childNode->addChild(std::shared_ptr<Node<T>>(node));
    }


    void addNode(std::shared_ptr<Node<T>> node)
    {
        // TODO
    }


  private:
    std::shared_ptr<Node<T>> _root;
    std::size_t _size = 0;

    // settings
    int globalIndent = 5;
};

} // namespace ATree

// FORFEDREDIAGRAM_TREE_HPP
