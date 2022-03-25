//
// Created by Martin on 15.03.2022.
//

#ifndef FORFEDREDIAGRAM_NODE_HPP
#define FORFEDREDIAGRAM_NODE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <memory>

#include "Person.hpp"
#include "../include/json.hpp"
using json = nlohmann::json;

class Node{
public:
    Node() = default;

    explicit Node(const json& j){
        data.fromJson(j["data"]);
        if(j["treeIdx"] != nullptr)
            treeIdx = j["treeIdx"];
    }


    explicit Node(const Person& p){
        data = p;
    }

    void addData(Person& p){
        data = p;
    }

    void addParent(Node* n){
        if(!_left){
            _left = std::unique_ptr<Node>(n);
        } else if(!_right){
            _right = std::unique_ptr<Node>(n);
        } else{
            std::cout << "Person har allerede to foreldre" << std::endl;
        }
    }

    void addParent(const Person& p){

        if(!_left){
            *_left = Node(p);
        } else if(!_right){
            _right = std::make_unique<Node>(Node(p));
        } else{
            std::cout << "Person har allerede to foreldre" << std::endl;
        }
    }

    void traverseDFS(const std::function<void(Node*)>& f){
        // DepthFirst - PreOrder
        f(this);
        if(_left)
            _left->traverseDFS(f);
        if(_right)
            _right->traverseDFS(f);
    }

    void traverseDFSPrint(const std::function<void(Node*, int)>& f, int depth = 0){
        // DepthFirst - PreOrder. Used for printing with depth information
        f(this, depth);
        if(_left)
            _left->traverseDFSPrint(f, depth+1);
        if(_right)
            _right->traverseDFSPrint(f, depth+1);
    }


    void setLeft(Node* node){
        _left = std::unique_ptr<Node>(node);
    }

    void setRight(Node* node){
        _right = std::unique_ptr<Node>(node);
    }

    void setIdx(unsigned int index){
        treeIdx = index;
    }

    [[nodiscard]] unsigned int getIdx() const{
        return treeIdx;
    }

    Person& getData() {
        return data;
    }

    Node& getLeft(){
        return *_left;
    }

    Node& getRight(){
        return *_right;
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getParents(){
        return {_left, _right};
    };

    friend std::ostream &operator<<(std::ostream &os, Node &n);

private:
    unsigned int treeIdx = -1;
    Person data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};

std::ostream &operator<<(std::ostream &os, Node &n)
{
    os << "[Node] Idx: " << n.getIdx() << ", contains: " << n.getData();

    return os;
}



#endif //FORFEDREDIAGRAM_NODE_HPP
