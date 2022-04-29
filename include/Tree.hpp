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

#include "Node.hpp"
#include "commonFunctions.hpp"
#include "json.hpp"

using json = nlohmann::json;

template <class T> class Tree
{

  public:
    void fillFromJson(const json &treeJson)
    {
        // Fill tree from json-file. Must be compatible, preferably exported from tree

        // Tree settings
        if (treeJson["tree"]["settings"]["globalIndent"] != nullptr)
            globalIndent = treeJson["tree"]["settings"]["globalIndent"];

        std::unordered_map<int, std::shared_ptr<Node<T>>> nodes;

        struct nodeChildren
        {
            int left, right;
        };


        // Extract nodes
        std::unordered_map<int, nodeChildren> childrenIndexes;
        for (auto &nodeData : treeJson["nodes"])
        {
            std::shared_ptr<Node<T>> newNode{std::make_shared<Node<T>>(nodeData)};

            std::cout << *newNode << std::endl;

            if (nodeData.contains("isRoot"))
            {
                if (nodeData.at("isRoot").is_boolean())
                {
                    if (nodeData.at("isRoot"))
                    {
                        setRoot(newNode);
                        _size++;
                    }
                }
            }

            nodes[nodeData["treeIndex"]] = newNode;

            // Store index of parents. If no parent, index is -1
            if (nodeData.contains("leftIdx"))
            {
                if (nodeData["leftIdx"].is_number_integer())
                    childrenIndexes[nodeData["treeIndex"]].left = nodeData["leftIdx"];
                else
                    childrenIndexes[nodeData["treeIndex"]].left = -1;
            }
            else
            {
                childrenIndexes[nodeData["treeIndex"]].left = -1;
            }

            if (nodeData.contains("rightIdx"))
            {
                if (nodeData["rightIdx"].is_number_integer())
                    childrenIndexes[nodeData["treeIndex"]].right = nodeData["rightIdx"];
                else
                    childrenIndexes[nodeData["treeIndex"]].right = -1;
            }
            else
            {
                childrenIndexes[nodeData["treeIndex"]].right = -1;
            }
        }

        // For testing - printing out all nodeindexes
        for (auto idx : childrenIndexes){
            std::cout << "[" << idx.second.left << "] <- [" << idx.first << "] -> [" << idx.second.right << "]" << std::endl;
        }



        for (auto [index, node] : nodes)
        {

            // Get index of parents
            int leftChildIdx = childrenIndexes[index].left;
            int rightChildIdx = childrenIndexes[index].right;

            std::cout << *node << std::endl;

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

    [[nodiscard]] json toJson() const
    {
        json nodes;
        _root->traverseDFS([&nodes](Node<T> *node) { nodes.push_back(node->toJson()); });

        COM::debug("All nodes ok");
        json j = json{{
                          "nodes",
                          nodes,
                      },
                      {"tree", {{"settings", {{"globalIndent", globalIndent}}}}}};
        return j;
    }

    void setRoot(std::shared_ptr<Node<T>> n)
    {
        if(_root)
            _root->setRootFlag(false);

        _root = n;
        _root->setRootFlag(true);
    }

    T removeNode(size_t index)
    {
        T removedData;

        size_t prevIndex = _root->getIdx();

        if (prevIndex == index)
        {
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
                if (node->leftPtr())
                {
                    if (node->leftPtr()->getIdx() == index)
                    {
                        removedData = *node->leftPtr()->getData();
                        if (node->leftPtr()->isLeaf())
                        {
                            node->setLeft(nullptr);
                        }
                        else
                        {
                            T dummy("Dummy", std::to_string(DummyId()));
                            node->leftPtr()->setData(dummy);
                        }
                        return;
                    }
                }
                if (node->rightPtr())
                {
                    if (node->rightPtr()->getIdx() == index)
                    {
                        removedData = *node->rightPtr()->getData();
                        if (node->rightPtr()->isLeaf())
                        {
                            node->setRight(nullptr);
                        }
                        else
                        {
                            T dummy("Dummy", std::to_string(DummyId()));
                            node->rightPtr()->setData(dummy);
                        }
                        return;
                    }
                }
            });
        }
        return removedData;
    }

    bool isEmpty()
    {
        return !_root;
    }

    [[nodiscard]] const Node<T> &viewNode(unsigned int index) const
    {
        // TODO
        return *_root;
    }

    [[nodiscard]] Person &getDataAt(unsigned int index)
    {
        // TODO
        return *_root->getData();
    }

    [[nodiscard]] const Person &viewDataAt(unsigned int index) const
    {
        // TODO
        return *_root->getData();
    }

    [[nodiscard]] Node<T> &viewRoot()
    {
        return *_root;
    }

    [[nodiscard]] Node<T> &getRoot()
    {
        return *_root;
    }

    [[nodiscard]] const Node<T> &viewRoot() const
    {
        return *_root;
    }

    void traverseDFS(Node<T> *nextNode, const std::function<void(Node<T> *)> &func)
    {

        if (!_root)
            return;

        func(nextNode);

        if (nextNode->leftPtr())
            traverseDFS(nextNode->leftPtr(), func);

        if (nextNode->rightPtr())
            traverseDFS(nextNode->rightPtr(), func);
    }

    void traverseBFS(const std::function<void(Node<T> *)> &func)
    {
        std::queue<Node<T> *> Q;

        if (_root)
            Q.push(_root.get());

        while (!Q.empty())
        {
            Node<T> *currentNode = Q.front();

            if (currentNode->leftPtr())
                Q.push(currentNode->leftPtr());
            if (currentNode->rightPtr())
                Q.push(currentNode->rightPtr());

            func(currentNode);

            Q.pop();
        }
    }

    void listOfNodes()
    {
        if (!_root)
            return;
        traverseDFS(_root.get(), [](Node<T> *node) { std::cout << *node->viewData() << std::endl; });
    }

    Node<T> *findNodeByIdx(unsigned int index)
    {
        if (_root->getIdx() == index)
        {
            return _root.get();
        }
        Node<T> *found = nullptr;
        traverseDFS(_root.get(), [&found, index](Node<T> *node) {
            if (node->getIdx() == index)
            {
                found = node;
                return;
            }
        });

        return found;
    }

    std::vector<Node<T> *> findNodeByString(const std::string &str)
    {
        // Will return a vector with pointers to all nodes containing a string = str
        std::vector<Node<T> *> nodes;
        if (!_root)
        {
            return nodes;
        }

        Node<T> *found = nullptr;
        _root->traverseDFS([&found, str, &nodes](Node<T> *node) {
            if (node->getData()->contains(str))
                nodes.push_back(node);
        });

        return nodes;
    }

    void addParent(int childIndex, std::shared_ptr<Node<T>> node)
    {
        Node<T> &childNode = findNodeByIdx(childIndex);
        if (childNode.addParent(std::shared_ptr<Node<T>>(node)))
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
