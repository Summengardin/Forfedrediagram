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
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class Tree{
public:
    void toJson(std::string filepath){
        std::ofstream file(filepath);
        file << _data;
    }

    void fromJson(std::string filepath){
        std::ifstream file(filepath);
        file >> _data;
    }

    void traverseDFS(const std::unique_ptr<Node<Person>>& n, const std::function< void(const std::unique_ptr<Node<Person>>&, int ) >& func, int depth = 0 ){
        // Depth-First Search - PreOrder
        if(!n){
            return;
        }
        func(n, depth);
        traverseDFS(n->getLeft(), func, depth + 1);
        traverseDFS(n->getRight(), func, depth + 1);
    }

    void show(){
        traverseDFS(_root, [this](const std::unique_ptr<Node<Person>>& n, int depth){
            for (int i = 0; i < depth-1; ++i){
                for (int space = 0; space < getSettingGlobalSpace(); ++space){
                    std::cout << " ";
                }
            }
            if (depth != 0){
                for (int space = 0; space < getSettingGlobalSpace() - 4 ; ++space){
                    std::cout << " ";
                }
                std::cout << "----";
            }
            std::cout << n->getData() << std::endl;
        })
    }


    int getSettingGlobalSpace() const {
        return _data["GLOBAL_SPACE"];
    }

private:
    std::unique_ptr<Node<Person>> _root;
    json _data{
            {"GLOBAL_SPACE",  50}
    };

};



#endif //FORFEDREDIAGRAM_TREE_HPP
