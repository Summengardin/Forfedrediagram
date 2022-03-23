//
// Created by Martin on 17.03.2022.
//

#ifndef FORFEDREDIAGRAM_TREE_HPP
#define FORFEDREDIAGRAM_TREE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <fstream>

#include "Node.hpp"
#include "Person.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

template<class T>
class Tree{
public:


    T& at(unsigned int index){
        if(index > _size){
            throw std::runtime_error("Function ´.at()`, index out of range");
        }


        std::unique_ptr<Node>& currentNode = _root;
        // Depth-First Search - PreOrder
        findNode(index, _root, currentNode);

        return currentNode->_data;
    }

    json toJSON(std::string& filepath){
        //TODO toJSON
        std::ofstream file(filepath);

        json j = json{"tree", {
                {"globalIndent", 4},
        }};

        file << j << std::endl;
    }

    void fromJSON(std::string& filepath){
        //TODO fromJSON()
        std::ifstream file(filepath);
        json import;
        file >> import;

        // Set tree settings
        _globalIndent = import["tree"]["settings"]["globalIndent"];

        // Generate people
        std::vector<size_t> treeIdxs;
        treeIdxs.reserve(import["nodes"].size());

        for(auto& nodeData : import["nodes"]){
            addNode(nodeData);
        }
    }


    void addNode(json& nodeData){
        //TODO addNode()
        std::unique_ptr<Node> newNode = std::unique_ptr<Node>(new Node(this, nodeData));
        if(!_root)
            _root = std::move(newNode);
        else{

        }



        _size++;
    }

    void removeNode(unsigned int index){
        //TODO removeNode()
    }


//    void traverseDFS(const std::unique_ptr<Node>& n, const std::function< void(const std::unique_ptr<Node>&, int ) >& func, int depth = 0 ){
//        // Depth-First Search - PreOrder
//        if(!n){
//            return;
//        }
//        func(n, depth);
//        traverseDFS(n->getLeft(), func, depth + 1);
//        traverseDFS(n->getRight(), func, depth + 1);
//    }

    void show(){

    }


private:
    struct Node {
        Node(Tree* t, json& nodeData):
            _data(T(nodeData["data"])),
            _treeIdx(nodeData["treeIdx"])
        {
            //_left = t->at(nodeData["left"]);
            //_right = t->at(nodeData["right"]);
        };
        // TODO - Node(std::string& parseNode)
        // Make Node from a string of relations

        friend std::ostream& operator<<(std::ostream& os, Node& n);

        size_t _treeIdx = 0;
        T _data;
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
    };

    friend std::ostream& operator<<(std::ostream& os, Node& n){
       os << "[Node] idx: " << n._treeIdx << "constains data: " << n._data;
       return os;
    }

    bool findNode(unsigned int index, std::unique_ptr<Node>& node, std::unique_ptr<Node>& foundNode){
        if (!node){
            return false;
        }

        if(index == node->_treeIdx) {
            foundNode = std::move(node);
            return true;
        }
        else if (findNode(index, node->_left, foundNode))
            return true;
        else if (findNode(index, node->_right, foundNode))
            return true;
        else
            return false;

    }

    std::unique_ptr<Node> _root;

    // Settings
    int _globalIndent = 50;
    size_t _size = 0;
    size_t nextFreeIdx = 1;
};



#endif //FORFEDREDIAGRAM_TREE_HPP
