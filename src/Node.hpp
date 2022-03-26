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
        data = std::make_shared<Person>(j["data"]);
        data->fromJson(j["data"]);
        if(j["treeIdx"] != nullptr)
            treeIdx = j["treeIdx"];
    }


    explicit Node(const Person& p){
        data = std::make_shared<Person>(p);
    }

    void addData(const Person& p){
        data = std::make_shared<Person>(p);
    }

    void addParent(const std::shared_ptr<Node>& n){
        if(!_left){
            _left = n; //std::move(n);
        } else if(!_right){
            _right = n; //std::move(n);
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

    void traverseDFS(const std::function<void(std::shared_ptr<Node>)>& f){
        // DepthFirst - PreOrder
        f(std::shared_ptr<Node>(this));
        if(_left)
            _left->traverseDFS(f);
        if(_right)
            _right->traverseDFS(f);
    }

    void traverseDFSPrint(const std::function<void(std::shared_ptr<Node>, int)>& f, int depth = 0){
        // DepthFirst - PreOrder. Used for printing with depth information
        f(std::shared_ptr<Node>(this), depth);
        if(_left)
            _left->traverseDFSPrint(f, depth+1);
        if(_right)
            _right->traverseDFSPrint(f, depth+1);
    }


    void setLeft(std::shared_ptr<Node>& node){
        _left = node;
    }

    void setRight(std::shared_ptr<Node>& node){
        _right = node;
    }

    void setIdx(unsigned int index){
        treeIdx = index;
    }

    [[nodiscard]] unsigned int getIdx() const{
        return treeIdx;
    }

    [[nodiscard]]const Person& viewData() const{
        return *data;
    }

    [[nodiscard]]Person& getData(){
        return *data;
    }

    [[nodiscard]]Node& getLeft(){
        return *_left;
    }

    [[nodiscard]]const Node& viewLeft() const {
        return *_left;
    }

    [[nodiscard]] Node& getRight(){
        return *_right;
    }

    [[nodiscard]]const Node& viewRight() const{
        return *_right;
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getParents(){
        return {_left, _right};
    };

    friend std::ostream &operator<<(std::ostream &os, Node &n);

private:
    unsigned int treeIdx = -1;
    std::shared_ptr<Person> data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};

std::ostream &operator<<(std::ostream &os, Node &n)
{
    os << "[Node] Idx: " << n.getIdx() << ", contains: " << n.viewData();

    return os;
}



#endif //FORFEDREDIAGRAM_NODE_HPP
