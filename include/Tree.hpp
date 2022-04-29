#pragma once//FORFEDREDIAGRAM_TREE_HPP

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


template<class T>
class Tree
{

public:
    void fillFromJson(const json &treeJson)
    {
        // Fill tree from json-file. Must be compatible, preferably exported from tree

        // Tree settings
        if (treeJson["tree"]["settings"]["globalIndent"] != nullptr)
            globalIndent = treeJson["tree"]["settings"]["globalIndent"];


        std::unordered_map<int, std::shared_ptr<Node<T>>> nodes;

        struct nodeParents {
            int left, right;
        };

        std::unordered_map<int, nodeParents> parentIdxs;
        for (auto &nodeData: treeJson["nodes"])
        {
            std::unique_ptr<Node<T>> newNode(std::make_unique<Node<T>>(nodeData));

            nodes[nodeData["treeIdx"]] = std::move(newNode);

            COM::debug("Node created");
            // Store index of parents. If no parent, index is -1
            if (nodeData.contains("leftIdx") && nodeData["leftIdx"].is_number_integer())
            {
                parentIdxs[nodeData["treeIdx"]].left = nodeData["leftIdx"];
            } else
            {
                parentIdxs[nodeData["treeIdx"]].left = -1;
            }

            if (nodeData["rightIdx"] != nullptr)
            {
                parentIdxs[nodeData["treeIdx"]].right = nodeData["rightIdx"];
            } else
            {
                parentIdxs[nodeData["treeIdx"]].right = -1;
            }
        }

        // Setting root node - node with uuid "1" from tree;
        // In this case we are not counting from 0
        setRoot(nodes[1]);
        ++_size;

        for (auto [key, value]: nodes)
        {

            // Get index of parents
            int leftIdx = parentIdxs[key].left;
            int rightIdx = parentIdxs[key].right;

            // Add parents if they exist
            if (leftIdx != -1)
            {
                value->setLeft(nodes.at(leftIdx));
                ++_size;
            }
            if (rightIdx != -1)
            {
                value->setRight(nodes.at(rightIdx));
                ++_size;
            }
        }
    }


    [[nodiscard]] json toJson() const
    {
        // All nodes as json-list
        json nodes;
        _root->traverseDFS([&nodes](Node<T> *node) {
            nodes.push_back(node->toJson());
        });


        json j = json{
                {
                        "nodes", nodes,
                },
                {"tree",
                 {{"settings", {{"globalIndent", globalIndent}}}}}};
        return j;
    }


    void setRoot(std::shared_ptr<Node<T>> n)
    {
        _root = n;
    }


    [[nodiscard]] Node<T> &getNode(unsigned int index)
    {
        //TODO
        return *_root;
    }


    void removeNode(size_t index){
        size_t prevIdx = _root->getIdx();
        if(prevIdx == index){
            setRoot(nullptr);
        }
        traverseDFS(_root.get(), [index, &prevIdx](Node<T>* node){
            if(node->leftPtr())
            {
                if (node->leftPtr()->getIdx() == index)
                {
                    if(node->leftPtr()->isLeaf()){
                        node->setLeft(nullptr);
                    } else{
                        T dummy("Dummy", std::to_string(TreeId()));
                        node->leftPtr()->setData(dummy);
                    }
                }
            }
            if(node->rightPtr())
            {
                if (node->rightPtr()->getIdx() == index)
                {
                    if(node->rightPtr()->isLeaf()){
                        node->setRight(nullptr);
                    } else{
                        T dummy("Dummy", std::to_string(TreeId()));
                        node->rightPtr()->setData(dummy);
                    }
                }
            }
        });

        //return removed;
    }


    bool isEmpty(){
        return !_root;
    }


    [[nodiscard]] const Node<T> &viewNode(unsigned int index) const
    {
        //TODO
        return *_root;
    }


    [[nodiscard]] Person &getDataAt(unsigned int index)
    {
        //TODO
        return *_root->getData();
    }


    [[nodiscard]] const Person &viewDataAt(unsigned int index) const
    {
        //TODO
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
        traverseDFS(_root.get(), [](Node<T> *node) {
            std::cout << *node->viewData() << std::endl;
        });
    }

    Node<T> *findNodeByIdx(unsigned int index)
    {
        if (_root->getIdx() == index)
        {
            return _root.get();
        }
        Node<T> *found = nullptr;
        traverseDFS(_root.get(), [&found, index](Node<T> *node) {
            if (node->getIdx() == index){
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

    void addNode(std::shared_ptr<Node<T>> node){
        //TODO
    }


private:
    std::shared_ptr<Node<T>> _root;
    std::size_t _size = 0;

    //settings
    int globalIndent = 5;
};


//FORFEDREDIAGRAM_TREE_HPP
