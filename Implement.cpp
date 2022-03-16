#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <functional>
#include <queue>

#define GLOBAL_SPACE 10
struct basicPerson{
    std::string name;
    
    basicPerson(std::string _name): name(_name){};
    
    friend std::ostream& operator << (std::ostream& os, basicPerson& pers);
};

std::ostream& operator << (std::ostream& os, basicPerson& pers){
    os << "[Person] Name: " << pers.name;
    return os;
}

struct Node{
    basicPerson* data = nullptr;  
    Node* left = nullptr;
    Node* right = nullptr;
    
    Node(basicPerson* _data): data(_data){};
    
    ~Node(){
        delete data;
        std::cout << "Node with " << *data << ", is deleted" << std::endl;
    }
};

void traverseDFS(Node* n, int depth, std::function<void (Node*, int)> func){
    // Depth-First search - PreOrder
    if(n == nullptr){
        return;
    }
    func(n, depth);
    traverseDFS(n->left, depth+1, func);
    traverseDFS(n->right, depth+1, func);
}

void traverseBFS(Node* n, int depth, std::function<void (Node*, int)> func){
    // Breadth-First search
    // TODO BFS
    
}


int main(){
    
    Node* n1 = new Node(new basicPerson("Martin Simengård"));
    Node* n2 = new Node(new basicPerson("Astrid Simengård"));
    Node* n3 = new Node(new basicPerson("Per Kristian Simengård"));
    Node* n4 = new Node(new basicPerson("Else Marie Simengård"));
    Node* n5 = new Node(new basicPerson("Sigurd Simengård"));
    Node* n6 = new Node(new basicPerson("Liv"));
    Node* n7 = new Node(new basicPerson("Per Tollersrud"));
    
    std::cout << *n1->data << std::endl;
    std::cout << *n2->data << std::endl;
    std::cout << *n3->data << std::endl;
    std::cout << *n4->data << std::endl;
    std::cout << *n5->data << std::endl;
    std::cout << *n6->data << std::endl;
    std::cout << *n7->data << std::endl;
    
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->left = n6;
    n3->right = n7;
    
    
    std::cout << "\nStarting traversal...\n" << std::endl;
    
    traverseDFS(n1, 0, [](Node* n, int depth){
        for (int i = 0; i < depth-1; ++i){
            for (int space = 0; space < GLOBAL_SPACE ; ++space){
            std::cout << " ";
            }
        }
        if (depth != 0){
            for (int space = 0; space < GLOBAL_SPACE ; ++space){
                std::cout << " ";
            }
            std::cout << "";
        }
        std::cout << *n->data << std::endl; 
    });
    
    std::cout << "\n...Finished traversal" << std::endl;
    
    return 0;
}
