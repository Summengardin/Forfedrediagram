//
// Created by Martin on 24.03.2022.
//

#ifndef FORFEDREDIAGRAM_NEWTREE_HPP
#define FORFEDREDIAGRAM_NEWTREE_HPP

#include <iostream>
#include <memory>
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
#include "../include/UsefulFunctions.hpp"

using json = nlohmann::json;


class NewTree{

public:

    void fillFromJson(const json& treeJson){
        MM::debug("Start filling");
        std::unordered_map<int, Node> nodes;
        std::unordered_map<int, std::pair<int, int>> parentIdxs; // pair.first = leftIdx, pair.second = rightIdx
        for(auto& nodeData : treeJson["nodes"]){
            std::unique_ptr<Node> newNode = std::make_unique<Node>(nodeData);
            nodes[nodeData["treeIdx"]] = Node(nodeData);
            if(nodeData["leftIdx"] != nullptr){
                parentIdxs[nodeData["treeIdx"]].first = nodeData["leftIdx"];
            } else
            {
                parentIdxs[nodeData["treeIdx"]].first = -1;
            }

            // Store index of parents. If no parent, index is -1
            if(nodeData["rightIdx"] != nullptr){
                parentIdxs[nodeData["treeIdx"]].second = nodeData["rightIdx"];
            } else
            {
                parentIdxs[nodeData["treeIdx"]].second = -1;
            }
            std::cout << nodeData["treeIdx"] << std::endl;
        }
        MM::debug("Done with filling map");

        std::unique_ptr<Node> newRoot = std::make_unique<Node>(nodes[1]);
        setRoot(newRoot);

        for(const auto& [key, value] : nodes){
            // Add parents if they exist

            MM::debug("Add");

            int leftIdx = parentIdxs[key].first;
            int rightIdx = parentIdxs[key].second;

            if(leftIdx != -1){
                value.setLeft(&nodes.at(leftIdx));
            }
            if(rightIdx != -1){
                value.setRight(&nodes.at(rightIdx));
            }
        }

        std::cout << *_root << std::endl;

        MM::debug("Done with filling tree");

        show();
    }

    void setRoot(std::unique_ptr<Node>& n){
        _root = std::move(n);
    }

    Node& getNode(unsigned int index){
        return *_root;
    }

    Person& getDataAt(unsigned int index){
        return _root->getData();
    }

    Node& getRoot(){
        return *_root;
    }

    void listNodes(){
        if(!_root)
            return;
        int turns = 0;
        _root->traverseDFS([&turns](Node* node){
            std::cout << *node << std::endl;
            turns++;
        });
        std::cout << "Turns: " << turns << std::endl;
    }

    void show(){
        if(!_root)
            return;
        int depth = 0;
        int indent = globalIndent;
        _root->traverseDFSPrint([indent](Node* node, int depth){
            for (int i = 0; i < depth-1; ++i){
                for (int space = 0; space < indent ; ++space){
                    std::cout << " ";
                }
            }
            if (depth != 0){
                for (int space = 0; space < indent - 4 ; ++space){
                    std::cout << " ";
                }
                std::cout << "----";
            }
            std::cout << node->getData() << std::endl;
            depth++;
        });
    }

   Node* findByIdx(unsigned int index){
        if(_root->getIdx() == index){
            return _root.get();
        }
        Node* found;
        _root->traverseDFS([&found, index](Node* node){
            if(node->getIdx() == index)
                found = node;
        });

        return found;
    }

    void traverse(){

    };

    void addParent(int childIndex){

    }
private:
    std::unique_ptr<Node> _root;
    std::size_t _size = 0;

    //settings
    int globalIndent = 5;
};


#endif //FORFEDREDIAGRAM_NEWTREE_HPP
