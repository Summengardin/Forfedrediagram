#ifndef FORFEDREDIAGRAM_TREE_HPP
#define FORFEDREDIAGRAM_TREE_HPP

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
#include "../include/commonFunctions.hpp"

using json = nlohmann::json;

class Tree{

public:

    void fillFromJson(const json& treeJson){
        // Fill tree from json-file. Must be compatible, preferably exported from tree

        // Tree settings
        if (treeJson["tree"]["settings"]["globalIndent"] != nullptr)
            globalIndent = treeJson["tree"]["settings"]["globalIndent"];


        COM::debug("Start filling");

        std::unordered_map<int, std::shared_ptr<Node>> nodes;
        std::unordered_map<int, std::pair<int, int>> parentIdxs; // pair.first = leftIdx, pair.second = rightIdx
        for(auto& nodeData : treeJson["nodes"]){
            std::unique_ptr<Node> newNode(std::make_unique<Node>(nodeData));

            nodes[nodeData["treeIdx"]] = std::move(newNode);

            COM::debug("Node created");
            // Store index of parents. If no parent, index is -1
            if(nodeData.contains("leftIdx") and nodeData["leftIdx"].is_number_integer()){
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
        COM::debug("Done with filling map\n");

        // Setting root node - index 1 from tree;
        _root = nodes[1];
        ++_size;

        for(auto [key, value] : nodes){

            COM::debug("Adding node to tree");
            std::cout << *value << std::endl;

            // Get index of parents
            int leftIdx = parentIdxs[key].first;
            int rightIdx = parentIdxs[key].second;

            // Add parents if they exist
            if(leftIdx != -1){
                value->setLeft(nodes.at(leftIdx));
                ++_size;
            }
            if(rightIdx != -1){
                value->setRight(nodes.at(rightIdx));
                ++_size;
            }
        }

        COM::debug("Done with filling tree");

        std::cout << "Root is " << *_root << std::endl;

        COM::debug("Before show\n");
        show();
        COM::debug("\nAfter show");

    }


    [[nodiscard]] json toJson() const
    {
        json nodes;
        _root->traverseDFS([&nodes](Node* node){
            nodes.push_back(node->toJson());
        });

        json j = json{
                {"nodes", nodes,},
                {
                    "tree", {
                        {"settings",{
                            {"globalIndent", globalIndent}
                            }
                        }
                    }
                }
        };
        return j;
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
        _root->traverseDFS([](Node* node){
            std::cout << node->viewData() << std::endl;
        });
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
            std::cout << node->viewData() << std::endl;
            depth++;
        });
    }

    Node& findNodeByIdx(unsigned int index) {
        if(_root->getIdx() == index){
            return *_root;
        }
       Node* found = nullptr;
        _root->traverseDFS([&found, index](Node* node){
            if(node->getIdx() == index)
                found = node;
        });

        if(found == nullptr){
            throw std::runtime_error("In function 'findByIndex': could not find index " + std::to_string(index));
        }
        return *found;
    }


    std::vector<Node*> findNodeByString(const std::string& str) {
        // Will return a vector with pointers to all nodes containing a string = str
        std::vector<Node*> nodes;
        if(!_root){
            return nodes;
        }

        Node* found = nullptr;
        _root->traverseDFS([&found, str, &nodes](Node* node){
            if(node->getData().contains(str))
                nodes.push_back(node);
        });

        return nodes;
    }


    void addParent(int childIndex,  Node* node){
        Node& childNode = findNodeByIdx(childIndex);
        if(childNode.addParent(std::shared_ptr<Node>(node)))
            ++_size;
    }

private:
    std::shared_ptr<Node> _root;
    std::size_t _size = 0;

    //settings
    int globalIndent = 5;
};


#endif //FORFEDREDIAGRAM_TREE_HPP
