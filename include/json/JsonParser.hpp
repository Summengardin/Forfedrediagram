#pragma once // ANCESTORTREE_JSONPARSER_HPP

#include <filesystem>

#include "atree/AncestorTree.hpp"
#include "person/Person.hpp"

#include "json.hpp"
using json = nlohmann::json;

class JsonParser
{
  private:
    static std::filesystem::path validate(const std::filesystem::path &path)
    {
        if (path.extension() != "json")
            throw std::invalid_argument("Not a .json-file");
        else
            return path;
    }

  public:
    JsonParser() = default;
    JsonParser(const std::filesystem::path &path)
        : _filepath(validate(path)){};


    static json toJson(const Person &);

    template <class T> static json toJson(const ATree::Node<T> &);

    template <class T> static json toJson(ATree::Tree<T> &);

    template <class T> static json toJson(const T &);

    static void fromJson(const json &, Person &);

    template <class T> static void fromJson(const json &, ATree::Node<T> &);

    template <class T> static void fromJson(const json &, ATree::Tree<T> &);

    template <class T> static void fromJson(const json &, T &);

    void jsonToFile(const json &);

    json jsonFromFile();

    static json jsonFromFile(const std::filesystem::path &);

    static bool isJson(const std::filesystem::path &);

    static void validateJsonNode(const json &jsonFile);

  private:
    std::filesystem::path _filepath{};
};


json JsonParser::toJson(const Person &person)
{
    // clang-format off
    json j = json{
        {"firstName", person.getFirstName()},
        {"lastName", person.getLastName()},
        {"middleName", person.getMiddleName()},
        {"birth", person.getBirth().toString()},
        {"death", person.getDeath().toString()},
        {"gender", person.getGenderString()},
        {"isAlive", person.isAlive()}
    };
    // clang-format on
    return j;
}

template <class T> json JsonParser::toJson(const T &value)
{
    std::stringstream ssValue;
    ssValue << value;

    json j = json{
        {"value", ssValue.str()},
    };

    return j;
}

template <class T> json JsonParser::toJson(const ATree::Node<T> &node)
{
    int leftIndex, rightIndex;
    if (node.leftChild())
        leftIndex = node.leftChild()->getIndex();
    else
        leftIndex = -1;

    if (node.rightChild())
        rightIndex = node.rightChild()->getIndex();
    else
        rightIndex = -1;

    json j = json{{"data", toJson(*node.getData())},
                  {"treeIndex", node.getIndex()},
                  {"leftIndex", leftIndex},
                  {"rightIndex", rightIndex},
                  {"isRoot", node.isRoot()}};
    return j;
}

template <class T> json JsonParser::toJson(ATree::Tree<T> &tree)
{
    json nodes;
    tree.traverseDFS(tree.getRoot(), [&nodes](ATree::Node<T> *node) { nodes.push_back(toJson(*node)); });

    // clang-format off
        json j = json{
                    {"nodes",
                        nodes},
                    {"tree", {
                        {"settings", {
                            {"globalIndent", tree.getSettingIndent()}
                                    }}}}};
    // clang-format on
    return j;
}


void JsonParser::fromJson(const json &jsonFile, Person &person)
{
    Person newPerson;

    if (jsonFile.contains("firstName") && jsonFile.at("firstName").is_string())
    {
        std::string firstName = jsonFile.at("firstName");
        newPerson.setFirstName(firstName);
    }

    if (jsonFile.contains("middleName") && jsonFile.at("middleName").is_string())
    {
        std::string middleName = jsonFile.at("middleName");
        newPerson.setMiddleName(middleName);
    }

    if (jsonFile.contains("lastName") && jsonFile.at("lastName").is_string())
    {
        std::string lastName = jsonFile.at("lastName");
        newPerson.setLastName(lastName);
    }

    if (jsonFile.contains("gender") && jsonFile.at("gender").is_string())
    {
        std::string genderStr = jsonFile.at("gender");
        newPerson.setGender(genderStr);
    }

    if (jsonFile.contains("birth") && jsonFile.at("birth").is_string())
    {
        std::string birthStr = jsonFile["birth"];
        newPerson.setBirth(birthStr);
    }

    if (jsonFile.contains("death") && jsonFile.at("death").is_string())
    {
        std::string deathStr = jsonFile["death"];
        newPerson.setDeath(deathStr);
    }

    if (jsonFile.contains("isAlive") && jsonFile.at("isAlive").is_boolean())
    {
        bool isAlive = jsonFile.at("isAlive");
        newPerson.setAliveFlag(isAlive);
    }

    person = newPerson;
}


template <class T> void JsonParser::fromJson(const json &jsonFile, T &value)
{
    if (jsonFile.contains("value"))
    {
        try
        {
            value = COM::convert<T>(jsonFile.at("value"));
        }
        catch (...)
        {
            std::cerr << "Invalid type when trying to parse from json.";
        }
    }

}

template <class T> void JsonParser::fromJson(const json &jsonFile, ATree::Node<T> &node)
{
    T data{};
    if (jsonFile.contains("data"))
        fromJson(jsonFile.at("data"), data);

    node.setData(std::move(data));
}

template <class T> void JsonParser::fromJson(const json &jsonFile, ATree::Tree<T> &tree)
{

    // Fill tree from json-file. Must be compatible, preferably exported from tree
    // It is done by first extracting all nodes from the tree into a map.
    // Then looping through the indexes and assigning children based on their indexes

    ATree::Tree<T> newTree;
    ATree::TreeId.reset();

    // Tree settings
    if (jsonFile.contains("tree") && jsonFile["tree"].contains("settings") &&
        jsonFile["tree"]["settings"].contains("globalIndent") &&
        jsonFile["tree"]["settings"]["globalIndent"] != nullptr)
    {
        int globalIndent = jsonFile["tree"]["settings"]["globalIndent"];
        newTree.setSettingIndent(globalIndent);
    }

    std::unordered_map<int, std::shared_ptr<ATree::Node<T>>> nodes;

    struct childrenIndex
    {
        int left, right;
    };


    std::unordered_map<int, childrenIndex> childrenIndexes;
    if (jsonFile.contains("nodes"))
    {
        for (auto &nodeData : jsonFile["nodes"])
        {
            validateJsonNode(nodeData);

            std::shared_ptr<ATree::Node<T>> newNode = std::make_shared<ATree::Node<T>>();

            fromJson(nodeData, *newNode);

            if (nodeData.contains("isRoot") && nodeData.at("isRoot").is_boolean() && nodeData.at("isRoot"))
                newTree.setRoot(newNode);

            nodes[nodeData["treeIndex"]] = newNode;

            // Store index of parents. If no parent, index is -1
            if (nodeData.contains("leftIndex") && nodeData["leftIndex"].is_number_integer())
                childrenIndexes[nodeData["treeIndex"]].left = nodeData["leftIndex"];
            else
                childrenIndexes[nodeData["treeIndex"]].left = -1;

            if (nodeData.contains("rightIndex") && nodeData["rightIndex"].is_number_integer())
                childrenIndexes[nodeData["treeIndex"]].right = nodeData["rightIndex"];
            else
                childrenIndexes[nodeData["treeIndex"]].right = -1;
        }
        if(!newTree.getRoot())
            throw std::invalid_argument("Could not find root node among json-nodes");
    }

    for (auto [index, node] : nodes)
    {

        // Get index of parents
        int leftChildIndex = childrenIndexes[index].left;
        int rightChildIndex = childrenIndexes[index].right;

        // Add parents if they exist
        if (leftChildIndex != -1)
            node->setLeft(nodes.at(leftChildIndex));
        if (rightChildIndex != -1)
            node->setRight(nodes.at(rightChildIndex));
    }

    tree = newTree;
}

void JsonParser::jsonToFile(const json &jsonFile)
{
    std::fstream{_filepath} << jsonFile.dump(4);
}


json JsonParser::jsonFromFile()
{
    return jsonFromFile(_filepath);
}

json JsonParser::jsonFromFile(const std::filesystem::path &path)
{
    if (!isJson(path))
        throw std::filesystem::filesystem_error("File is not a .json-file", std::error_code());

    json jsonObject;
    std::fstream{path} >> jsonObject;

    return jsonObject;
}

bool JsonParser::isJson(const std::filesystem::path &file)
{
    return file.extension() == ".json";
}

void JsonParser::validateJsonNode(const json &jsonFile)
{
    if ((jsonFile.contains("treeIndex")) && jsonFile.contains("leftIndex") &&
         jsonFile.contains("rightIndex") && jsonFile.contains("data"))
    {
        return;
    }
    throw std::invalid_argument("Invalid json-object");
}


// ANCESTORTREE_JSONPARSER_HPP
