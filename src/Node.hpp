//
// Created by Martin on 15.03.2022.
//

#ifndef FORFEDREDIAGRAM_NODE_HPP
#define FORFEDREDIAGRAM_NODE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <memory>


class Data{
public:
    virtual void print(){};
};

template <class T>
class Node {
public:
    Node(std::shared_ptr<T> data): _data(std::move(data)){};

    [[nodiscard]] std::shared_ptr<T> getData() const{
        return _data;
    };

    bool isLeaf(){
        return !_left and !_right;
    }



private:
    std::shared_ptr<T> _data;
    std::unique_ptr<Node> _left;
    std::unique_ptr<Node> _right;
};



#endif //FORFEDREDIAGRAM_NODE_HPP
