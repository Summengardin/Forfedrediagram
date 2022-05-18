#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "atree/ancestor_tree.hpp"
#include "person/person.hpp"

TEST_CASE("Build up int-tree")
{
    ATree::Tree<int> integerTree;
    TreeId.reset(); // Need to reset the indexing for every section

    int root = 1;
    int parent1 = 11;
    int parent2 = 12;
    int grandparent1 = 111;
    int grandparent2 = 112;
    int grandparent3 = 121;
    int grandparent4 = 122;

    auto rootNode = std::make_shared<ATree::Node<int>>(root);
    auto p1Node = std::make_shared<ATree::Node<int>>(parent1);
    auto p2Node = std::make_shared<ATree::Node<int>>(parent2);
    auto gp1Node = std::make_shared<ATree::Node<int>>(grandparent1);
    auto gp2Node = std::make_shared<ATree::Node<int>>(grandparent2);
    auto gp3Node = std::make_shared<ATree::Node<int>>(grandparent3);
    auto gp4Node = std::make_shared<ATree::Node<int>>(grandparent4);


   // std::cout << "Tree getSize: " << integerTree.getSize() << std::endl;
    integerTree.setRoot(rootNode);
    rootNode->addChild(p1Node);
    rootNode->addChild(p2Node);
    p1Node->addChild(gp1Node);
    p1Node->addChild(gp2Node);
    p2Node->addChild(gp3Node);
    p2Node->addChild(gp4Node);
    //std::cout << "Tree getSize: " << integerTree.getSize() << std::endl;

    SECTION("Find node by search term")
    {
        std::vector<ATree::Node<int> *> expected1 = {rootNode.get(), p1Node.get(),  p2Node.get(), gp1Node.get(),
                                                     gp2Node.get(),  gp3Node.get(), gp4Node.get()};
        std::vector<ATree::Node<int> *> expected12 = {p2Node.get(), gp2Node.get(), gp3Node.get(), gp4Node.get()};
        std::vector<ATree::Node<int> *> expected11 = {p1Node.get(), gp1Node.get(), gp2Node.get()};
        std::vector<ATree::Node<int> *> expected112 = {gp2Node.get()};

        REQUIRE(integerTree.findNodeByString("1") == expected1);
        REQUIRE(integerTree.findNodeByString("11") == expected11);
        REQUIRE(integerTree.findNodeByString("12") == expected12);
        REQUIRE(integerTree.findNodeByString("112") == expected112);
    }

    SECTION("Indexing")
    {
        auto expected1 = 1;
        auto expected2 = 2;
        auto expected3 = 3;
        auto expected4 = 4;
        auto expected5 = 5;
        auto expected6 = 6;
        auto expected7 = 7;



        REQUIRE(rootNode->getIndex() == expected1);
        REQUIRE(p1Node->getIndex() == expected2);
        REQUIRE(p2Node->getIndex() == expected3);
        REQUIRE(gp1Node->getIndex() == expected4);
        REQUIRE(gp2Node->getIndex() == expected5);
        REQUIRE(gp3Node->getIndex() == expected6);
        REQUIRE(gp4Node->getIndex() == expected7);


    }

    SECTION("Find node by index")
    {
        auto expected1 = rootNode.get();
        auto expected2 = p1Node.get();
        auto expected3 = p2Node.get();
        auto expected4 = gp1Node.get();
        auto expected5 = gp2Node.get();
        auto expected6 = gp3Node.get();
        auto expected7 = gp4Node.get();

        REQUIRE(integerTree.findNodeByIndex(1) == expected1);
        REQUIRE(integerTree.findNodeByIndex(2) == expected2);
        REQUIRE(integerTree.findNodeByIndex(3) == expected3);
        REQUIRE(integerTree.findNodeByIndex(4) == expected4);
        REQUIRE(integerTree.findNodeByIndex(5) == expected5);
        REQUIRE(integerTree.findNodeByIndex(6) == expected6);
        REQUIRE(integerTree.findNodeByIndex(7) == expected7);
    }
}
