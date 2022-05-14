//#include <memory>


#include "person/person.hpp"
#include "helpers.hpp"
#include "atree/ancestor_tree.hpp"

int main() {
    ATree::Tree<Person> familyTree;

    Person rootPerson("Per", "Lillegutt");
    rootPerson.setBirth("23-04-2003");

    Person mom;
    mom.setFirstName("Kari");
    mom.setLastName("Nordmann");
    mom.setBirth("23-04-1967");

    Person dad;
    dad.setFirstName("Ola");
    dad.setLastName("Nordmann");
    dad.setBirth("13-07-1961");

    rootPerson.setLastName("Nordmann");

    ATree::Node<Person> root = ATree::Node(rootPerson);
    ATree::Node<Person> momNode = ATree::Node(mom);

    familyTree.addNode(std::make_shared<ATree::Node<Person>>(root));
    familyTree.addChild(1, std::make_shared<ATree::Node<Person>>(momNode));
    familyTree.addNode(std::make_shared<ATree::Node<Person>>(dad));

}
