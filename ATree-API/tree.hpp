#pragma once // FORFEDREDIAGRAM_TREE_HPP

#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "helpers.hpp"
#include "json.hpp"
#include "node.hpp"

using json = nlohmann::json;

template <class T> class Tree
{

  public:
    enum DFSOrder
    {
        PRE,
        IN,
        POST
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

    void traverseDFS(Node<T> *node, const std::function<void(Node<T> *)> &func, DFSOrder order = DFSOrder::PRE)
    {
        if (!node)
            return;

        if (order == DFSOrder::PRE)
            func(node);

        traverseDFS(node->leftChild(), func, order);

        if (order == DFSOrder::IN)
            func(node);

        traverseDFS(node->rightChild(), func, order);

        if (order == DFSOrder::POST)
            func(node);
    }

    void traverseDFSWithDepth(Node<T> *node, const std::function<void(Node<T> *, int)> &func,
                              DFSOrder order = DFSOrder::PRE, int depth = 0)
    {
        if (!node)
            return;

        if (order == DFSOrder::PRE)
            func(node, depth);

        traverseDFSWithDepth(node->leftChild(), func, order, depth + 1);

        if (order == DFSOrder::IN)
            func(node, depth);

        traverseDFSWithDepth(node->rightChild(), func, order, depth + 1);

        if (order == DFSOrder::POST)
            func(node, depth);
    }

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

    Node<T> *findNodeByIdx(unsigned int index)
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
        // This will require the node-data to have a member-function "contains"
        // which checks for str in the data
        std::vector<Node<T> *> nodes;
        if (!_root)
        {
            return nodes;
        }

        Node<T> *found = nullptr;
        traverseDFS(getRoot(), [&found, str, &nodes](Node<T> *node) {
            if (node->getData()->contains(str))
                nodes.push_back(node);
        });

        return nodes;
    }

    void addParent(int childIndex, std::shared_ptr<Node<T>> node)
    {
        Node<T> &childNode = findNodeByIdx(childIndex);
        if (childNode.addChild(std::shared_ptr<Node<T>>(node)))
            ++_size;
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

// FORFEDREDIAGRAM_TREE_HPP
