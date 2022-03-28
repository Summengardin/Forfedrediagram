#ifndef FORFEDREDIAGRAM_NODE_HPP
#define FORFEDREDIAGRAM_NODE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <memory>

#include "globals.hpp"
#include "Person.hpp"
#include "../include/json.hpp"
using json = nlohmann::json;

class Node{
public:
    explicit Node(const json& j){
        data = std::make_shared<Person>(j["data"]);
        //data->fromJson(j["data"]);
//        if(j.contains("treeIdx") and j["treeIdx"] != nullptr)
//            _treeIdx = j["treeIdx"];
        if(j.contains("treeIndex") and j["treeIndex"].is_string())
        {
            _treeIdx = j["treeIndex"];
            TreeId.update(_treeIdx);
        }
        else
            _treeIdx = TreeId();
    }


    explicit Node(const Person& p){
        data = std::make_shared<Person>(p);
        _treeIdx = TreeId();
    }


    [[nodiscard]] json toJson() const
    {
        int leftIndex, rightIndex;
        if(_left)
            leftIndex = _left->_treeIdx;
        else
            leftIndex = -1;

        if(_right)
            rightIndex = _right->_treeIdx;
        else
            rightIndex = -1;


        json j = json{
                {"data",     data->toJson()},
                {"treeIdx", _treeIdx},
                {"leftIdx",  leftIndex},
                {"rightIdx",  rightIndex},
        };
        return j;
    }


    void setData(const Person& p){
        data = std::make_shared<Person>(p);
    }


    bool addParent(const std::shared_ptr<Node>& n){
        // Returns true if successfully added parent, false if not.
        if(!_left){
            _left = n; //std::move(n);
        } else if(!_right){
            _right = n; //std::move(n);
        } else{
            std::cout << "Node already has to links" << std::endl;
            return false;
        }
        return true;
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


    void traverseDFS(const std::function<void(Node*)>& f) {
        // DepthFirst - PreOrder
        f(this);
        
        if (_left)
            _left->traverseDFS(f);

        if (_right)
            _right->traverseDFS(f);
    }


    void traverseDFSPrint(const std::function<void(Node*, int)>& f, int depth = 0){
        // DepthFirst - InOrder. Used for printing with depth information

        if(_left)
            _left->traverseDFSPrint(f, depth+1);
        f(this, depth);
        if(_right)
            _right->traverseDFSPrint(f, depth+1);
    }


    void traverseBFS(const std::function<void(Node*)>& f){


    }


    void setLeft(std::shared_ptr<Node>& node){
        _left = node;
    }


    void setRight(std::shared_ptr<Node>& node){
        _right = node;
    }


    void setIdx(unsigned int index){
        _treeIdx = index;
    }


    [[nodiscard]] unsigned int getIdx() const{
        return _treeIdx;
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

    [[nodiscard]] Node* leftPtr() const {
        return _left.get();
    }


    [[nodiscard]] Node& getRight(){
        return *_right;
    }

    [[nodiscard]]const Node& viewRight() const{
        return *_right;
    }

    [[nodiscard]] Node* rightPtr() const {
        return _right.get();
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getParents(){
        return {_left, _right};
    };

    friend std::ostream &operator<<(std::ostream &os, Node &n);

private:
    unsigned int _treeIdx;
    unsigned int id;
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
