#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "atree/AncestorTree.hpp"
#include "person/Person.hpp"
#include "json/JsonParser.hpp"

TEST_CASE("Parser-functions")
{}

TEST_CASE("Person")
{

    std::string firstName = "For";
    std::string middleName = "Mellom";
    std::string lastName = "Etter";
    Person::GenderType gender = Person::MALE;
    Date birth{22, 06, 1999};
    Date death{22, 06, 2015};

    SECTION("Person to Json")
    {
        Person person{firstName, middleName, lastName, gender, birth, death};
        json expected = {{"firstName", firstName},    {"lastName", lastName},      {"middleName", middleName},
                         {"birth", birth.toString()}, {"death", death.toString()}, {"gender", "male"},
                         {"isAlive", false}};

        REQUIRE(JsonParser::toJson(person) == expected);
    }

    SECTION("Person from json")
    {
        Person jsonPerson;
        json jsonFile = json{{"firstName", firstName},    {"lastName", lastName},      {"middleName", middleName},
                             {"birth", birth.toString()}, {"death", death.toString()}, {"gender", "male"},
                             {"isAlive", false}};

        JsonParser::fromJson(jsonFile, jsonPerson);

        CHECK(firstName == jsonPerson.getFirstName());
        CHECK(middleName == jsonPerson.getMiddleName());
        CHECK(lastName == jsonPerson.getLastName());
        CHECK(gender == jsonPerson.getGender());
        CHECK(birth == jsonPerson.getBirth());
        CHECK(death == jsonPerson.getDeath());
        CHECK(!jsonPerson.isAlive());
    }
}


TEST_CASE("Tree and node to/from json")
{


    SECTION("Tree to json")
    {
        ATree::Tree<int> integerTree;
        TreeId.reset(); // Need to reset the indexing for every section

        int root = 1;
        int parent1 = 11;
        int parent2 = 134;

        auto rootNode = std::make_shared<ATree::Node<int>>(root);
        auto p1Node = std::make_shared<ATree::Node<int>>(parent1);
        auto p2Node = std::make_shared<ATree::Node<int>>(parent2);

        integerTree.setRoot(rootNode);
        rootNode->addChild(p1Node);
        rootNode->addChild(p2Node);
        integerTree.setSettingIndent(4);

        json expectedJson = json(
            {{"nodes",
              {{{"data", {{"value", "1"}}}, {"treeIndex", 1}, {"leftIndex", 2}, {"rightIndex", 3}, {"isRoot", true}},
               {{"data", {{"value", "11"}}},
                {"treeIndex", 2},
                {"leftIndex", -1},
                {"rightIndex", -1},
                {"isRoot", false}},
               {{"data", {{"value", "134"}}},
                {"treeIndex", 3},
                {"leftIndex", -1},
                {"rightIndex", -1},
                {"isRoot", false}}}},
             {"tree", {{"settings", {{"globalIndent", 4}}}}}});

        REQUIRE(JsonParser::toJson(integerTree) == expectedJson);
    }
    SECTION("Tree from json")
    {
        TreeId.reset();
        ATree::Tree<int> jsonTree;
        json jsonExample = json(
            {{"nodes",
              {{{"data", {{"value", "1"}}}, {"treeIndex", 1}, {"leftIndex", 2}, {"rightIndex", 3}, {"isRoot", true}},
               {{"data", {{"value", "11"}}},
                {"treeIndex", 2},
                {"leftIndex", -1},
                {"rightIndex", -1},
                {"isRoot", false}},
               {{"data", {{"value", "134"}}},
                {"treeIndex", 3},
                {"leftIndex", -1},
                {"rightIndex", -1},
                {"isRoot", false}}}},
             {"tree", {{"settings", {{"globalIndent", 4}}}}}});

        JsonParser::fromJson(jsonExample, jsonTree);

        REQUIRE(*jsonTree.findNodeByIndex(1)->getData() == 1);
        REQUIRE(*jsonTree.findNodeByIndex(2)->getData() == 11);
        REQUIRE(*jsonTree.findNodeByIndex(3)->getData() == 134);

        REQUIRE(jsonTree.findNodeByIndex(1)->leftChild() == jsonTree.findNodeByIndex(2));
        REQUIRE(jsonTree.findNodeByIndex(1)->rightChild() == jsonTree.findNodeByIndex(3));
        REQUIRE(jsonTree.findNodeByIndex(2)->leftChild() == nullptr);
        REQUIRE(jsonTree.findNodeByIndex(2)->rightChild() == nullptr);
        REQUIRE(jsonTree.findNodeByIndex(3)->leftChild() == nullptr);
        REQUIRE(jsonTree.findNodeByIndex(3)->rightChild() == nullptr);

        CHECK(jsonTree.getSettingIndent() == 4);
    }
}


TEST_CASE("Person to/from json")
{}
