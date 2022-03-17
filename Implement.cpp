#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <functional>

#define GLOBAL_SPACE 10
struct basicPerson{
    std::string name;

    basicPerson(std::string _name): name(std::move(_name)){};

    friend std::ostream& operator << (std::ostream& os, basicPerson& pers);
};

std::ostream& operator << (std::ostream& os, basicPerson& pers){
    os << "[Person] Name: " << pers.name;
    return os;
}

struct Node{
    std::unique_ptr<basicPerson> data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(std::unique_ptr<basicPerson> _data): data(std::move(_data)){};
    Node(std::string _name): data(std::make_unique<basicPerson>(basicPerson(std::move(_name)))){};

    ~Node(){
        std::cout << "Node with " << *data << ", is deleted" << std::endl;
    }
};

void traverseDFS(const std::unique_ptr<Node>& n, int depth, const std::function<void (const std::unique_ptr<Node>&, int)>& func){
    // Depth-First search - PreOrder
    if(!n){
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

    std::unique_ptr<Node> n1(new Node("Martin Simengård"));
    std::unique_ptr<Node> n2(new Node("Astrid Simengård"));
    std::unique_ptr<Node> n3(new Node("Per Kristian Simengård"));
    std::unique_ptr<Node> n4(new Node("Else Marie Simengård"));
    std::unique_ptr<Node> n5(new Node("Sigurd Simengård"));
    std::unique_ptr<Node> n6(new Node("Liv"));
    std::unique_ptr<Node> n7(new Node("Per Tollersrud"));

    std::cout << *n1->data << std::endl;
    std::cout << *n2->data << std::endl;
    std::cout << *n3->data << std::endl;
    std::cout << *n4->data << std::endl;
    std::cout << *n5->data << std::endl;
    std::cout << *n6->data << std::endl;
    std::cout << *n7->data << std::endl;

    n3->left = std::move(n6);
    n3->right = std::move(n7);
    n2->left = std::move(n4);
    n2->right = std::move(n5);
    n1->left = std::move(n2);
    n1->right = std::move(n3);

    std::cout << "\nStarting traversal...\n" << std::endl;

    traverseDFS(n1, 0, [](const std::unique_ptr<Node>& n, int depth){
        for (int i = 0; i < depth-1; ++i){
            for (int space = 0; space < GLOBAL_SPACE ; ++space){
            std::cout << " ";
            }
        }
        if (depth != 0){
            for (int space = 0; space < GLOBAL_SPACE - 4 ; ++space){
                std::cout << " ";
            }
            std::cout << "----";
        }
        std::cout << *n->data << std::endl;
    });

    std::cout << "\n...Finished traversal\n" << std::endl;

    return 0;
}
