//#include <memory>


#include "atree/ancestor_tree.hpp"
#include "helpers.hpp"
#include "person/person.hpp"

int main()
{
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

    familyTree.addChild(1, std::make_shared<ATree::Node<Person>>(momNode));
}
