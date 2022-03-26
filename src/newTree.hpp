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
        std::unordered_map<int, std::shared_ptr<Node>> nodes;
        std::unordered_map<int, std::pair<int, int>> parentIdxs; // pair.first = leftIdx, pair.second = rightIdx
        for(auto& nodeData : treeJson["nodes"]){
            std::unique_ptr<Node> newNode(std::make_unique<Node>(nodeData));

            nodes[nodeData["treeIdx"]] = std::move(newNode);

            MM::debug("Node created");
            // Store index of parents. If no parent, index is -1
            if(nodeData["leftIdx"] != nullptr){
                parentIdxs[nodeData["treeIdx"]].first = nodeData["leftIdx"];
            } else
            {
                parentIdxs[nodeData["treeIdx"]].first = -1;
            }

            if(nodeData["rightIdx"] != nullptr){
                parentIdxs[nodeData["treeIdx"]].second = nodeData["rightIdx"];
            } else
            {
                parentIdxs[nodeData["treeIdx"]].second = -1;
            }
        }
        MM::debug("Done with filling map\n");

        // Setting root node - index 1 from tree;
        _root = nodes[1];

        for(auto [key, value] : nodes){

            MM::debug("Adding node to tree");
            std::cout << *value << std::endl;

            // Get index of parents
            int leftIdx = parentIdxs[key].first;
            int rightIdx = parentIdxs[key].second;

            // Add parents if they exist
            if(leftIdx != -1){
                value->setLeft(nodes.at(leftIdx));
            }
            if(rightIdx != -1){
                value->setRight(nodes.at(rightIdx));
            }
        }
        MM::debug("Done with filling tree");

        std::cout << "Root is " << *_root << std::endl;

        MM::debug("Before show\n");
 //       show();
        MM::debug("\nAfter show");
    }

    void setRoot(std::shared_ptr<Node> n){
        _root = std::move(n);
    }

    [[nodiscard]]Node& getNode(unsigned int index) {
        //TODO
        return *_root;
    }

    [[nodiscard]]const Node& viewNode(unsigned int index) const {
        //TODO
        return *_root;
    }

    [[nodiscard]] Person& getDataAt(unsigned int index) {
        //TODO
        return _root->getData();
    }

    [[nodiscard]] const Person& viewDataAt(unsigned int index) const {
        //TODO
        return _root->getData();
    }

    [[nodiscard]] Node& viewRoot() {
        return *_root;
    }

    [[nodiscard]] Node& getRoot() {
        return *_root;
    }

    [[nodiscard]] const Node& viewRoot() const{
        return *_root;
    }

    void listNodes(){
        if(!_root)
            return;
        int turns = 0;
        _root->traverseDFS([&turns](const std::shared_ptr<Node>& node){
            std::cout << node->viewData() << std::endl;
            turns++;
        });
        std::cout << "Turns: " << turns << std::endl;
    }

    void show(){
        if(!_root)
            return;
        int depth = 0;
        int indent = globalIndent;
        _root->traverseDFSPrint([indent](std::shared_ptr<Node> node, int depth){
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
            std::cout << node->viewData() << std::endl;
            depth++;
        });
    }

    std::shared_ptr<Node> findByIdx(unsigned int index){
        if(_root->getIdx() == index){
            return _root;
        }
       std::shared_ptr<Node> found;
        _root->traverseDFS([found, index](const std::shared_ptr<Node>& node){
            if(node->getIdx() == index){}
                //found = node;
        });

        return found;
    }

    void traverse(){

    };

    void addParent(int childIndex){

    }
private:
    std::shared_ptr<Node> _root;
    std::size_t _size = 0;

    //settings
    int globalIndent = 5;
};


#endif //FORFEDREDIAGRAM_NEWTREE_HPP
