#pragma once // FORFEDREDIAGRAM_TREE_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Helpers.hpp"

#include "json/json.hpp"
using json = nlohmann::json;


namespace ATree
{
class UUID
{
  private:
    unsigned int nextFreeIdx = 0;

  public:
    unsigned int operator()() { return ++nextFreeIdx; }

    void update(unsigned int otherIdx)
    {
        if (otherIdx > nextFreeIdx)
        {
            nextFreeIdx = otherIdx;
        }
    }

    void reset() { nextFreeIdx = 0; }
};

UUID TreeId;


/********************************\
 *                              *
 *             NODE             *
 *                              *
\********************************/


template <class T> class Node
{
  public:
    explicit Node();
    explicit Node(const T &data);

    void setData(const T &data);

    bool addChild(std::shared_ptr<Node> childPtr);

    bool addChild(const T &childData);

    void setRootFlag(bool rootFlag);

    void setLeft(std::shared_ptr<Node> node);

    void setRight(std::shared_ptr<Node> node);

    void updateIndex();

    [[nodiscard]] unsigned int getIndex() const;

    [[nodiscard]] const T *getData() const;

    [[nodiscard]] T *getData();

    [[nodiscard]] const Node *leftChild() const;

    [[nodiscard]] Node *leftChild();

    [[nodiscard]] const Node *rightChild() const;

    [[nodiscard]] Node *rightChild();

    [[nodiscard]] std::shared_ptr<Node> leftChildOwnership();

    [[nodiscard]] std::shared_ptr<Node> rightChildOwnership();

    [[nodiscard]] bool isLeaf() const;

    [[nodiscard]] bool isRoot() const;

    [[nodiscard]] bool contains(const std::string &str) const;

    friend std::ostream &operator<<(std::ostream &os, Node &n)
    {
        os << "[Node] Idx: " << n.getIndex() << ", contains: " << *n.getData();
        return os;
    }

  private:
    bool _isRoot{false};
    unsigned int _treeIndex;
    std::shared_ptr<T> _data{};
    std::shared_ptr<Node> _leftChild;
    std::shared_ptr<Node> _rightChild;
};


template <class T>
Node<T>::Node()
    : _treeIndex(TreeId())
{}

template <class T>
Node<T>::Node(const T &data)
    : _data(std::make_shared<T>(data))
    , _treeIndex(TreeId())
{}


template <class T> bool Node<T>::contains(const std::string &str) const
{
    std::ostringstream nodeData;
    nodeData << *getData();

    return nodeData.str().find(str) != std::string::npos;
}


template <class T> bool Node<T>::isRoot() const
{
    return _isRoot;
}


template <class T> bool Node<T>::isLeaf() const
{
    return (!_leftChild && !_rightChild);
}


template <class T> unsigned int Node<T>::getIndex() const
{
    return _treeIndex;
}


template <class T> const T *Node<T>::getData() const
{
    return _data.get();
}


template <class T> T *Node<T>::getData()
{
    return _data.get();
}


template <class T> const Node<T> *Node<T>::leftChild() const
{
    return _leftChild.get();
}


template <class T> Node<T> *Node<T>::leftChild()
{
    return _leftChild.get();
}


template <class T> const Node<T> *Node<T>::rightChild() const
{
    return _rightChild.get();
}


template <class T> Node<T> *Node<T>::rightChild()
{
    return _rightChild.get();
}


template <class T> std::shared_ptr<Node<T>> Node<T>::leftChildOwnership()
{
    return _leftChild;
}


template <class T> std::shared_ptr<Node<T>> Node<T>::rightChildOwnership()
{
    return _rightChild;
}


template <class T> void Node<T>::updateIndex()
{
    _treeIndex = TreeId();
}


template <class T> void Node<T>::setRootFlag(bool rootFlag)
{
    _isRoot = rootFlag;
}


template <class T> void Node<T>::setData(const T &data)
{
    _data = std::make_shared<T>(data);
}


template <class T> bool Node<T>::addChild(std::shared_ptr<Node> childPtr)
{
    // Returns true if successfully added child, false if not.

    if (!_leftChild)
        _leftChild = childPtr;
    else if (!_rightChild)
        _rightChild = childPtr;
    else
        return false;
    return true;
}


template <class T> bool Node<T>::addChild(const T &childData)
{
    // Returns true if successfully added child, false if not.
    auto child = std::make_shared<Node>(Node(childData));
    return addChild(child);
}


template <class T> void Node<T>::setLeft(std::shared_ptr<Node> node)
{
    _leftChild = node;
}


template <class T> void Node<T>::setRight(std::shared_ptr<Node> node)
{
    _rightChild = node;
}


/*******************************\
 *                             *
 *             TREE            *
 *                             *
\*******************************/

enum DFSOrder
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
};

template <class T> class Tree
{
  public:
    Tree() = default;

    void setRoot(std::shared_ptr<Node<T>> n);

    T removeNode(size_t index);

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] Node<T> *getRoot();

    [[nodiscard]] std::shared_ptr<Node<T>> accessRootOwnership();

    void traverseDFS(Node<T> *node, const std::function<void(Node<T> *)> &func, DFSOrder order = DFSOrder::PRE_ORDER);

    void traverseDFSWithDepth(Node<T> *node, const std::function<void(Node<T> *, int)> &func,
                              DFSOrder order = DFSOrder::PRE_ORDER, int depth = 0);

    void traverseBFS(const std::function<void(Node<T> *)> &func);

    [[nodiscard]] int getSettingIndent() const;

    void setSettingIndent(int indent);

    std::vector<Node<T> *> listAllNodes();

    Node<T> *findNodeByIndex(unsigned int index);

    std::vector<Node<T> *> findNodeByString(const std::string &str);

    [[nodiscard]] size_t getSize();

    void addChild(int nodeIndex, std::shared_ptr<Node<T>> node);

  private:
    std::shared_ptr<Node<T>> _root;
    std::size_t _size = 0;

    // settings
    int globalIndent = 5;
};


template <class T> void Tree<T>::setRoot(std::shared_ptr<Node<T>> n)
{
    if(n == nullptr)
    {
        _root = n;
        return;
    }

    if (_root)
        _root->setRootFlag(false);

    _root = n;
    _root->setRootFlag(true);
}


template <class T> bool Tree<T>::isEmpty() const
{
    return !_root;
}


template <class T> size_t Tree<T>::getSize()
{
    int size = 0;
    traverseDFS(getRoot(), [&size](Node<T> *node) { size++; });
    return size;
}


template <class T> Node<T> *Tree<T>::getRoot()
{
    return _root.get();
}


template <class T> std::shared_ptr<Node<T>> Tree<T>::accessRootOwnership()
{
    return _root;
}


template <class T> int Tree<T>::getSettingIndent() const
{
    return globalIndent;
}


template <class T> std::vector<Node<T> *> Tree<T>::listAllNodes()
{
    std::vector<Node<T> *> allNodes;

    if (_root)
        traverseDFS(getRoot(), [&allNodes](Node<T> *node) { allNodes.push_back(node); });

    return allNodes;
}


template <class T> Node<T> *Tree<T>::findNodeByIndex(unsigned int index)
{
    if (_root->getIndex() == index)
    {
        return _root.get();
    }
    Node<T> *found = nullptr;
    traverseDFS(getRoot(), [&found, index](Node<T> *node) {
        if (node->getIndex() == index)
        {
            found = node;
            return;
        }
    });

    return found;
}


template <class T> std::vector<Node<T> *> Tree<T>::findNodeByString(const std::string &str)
{
    // Will return a vector with pointers to all nodes containing str

    std::vector<Node<T> *> nodes;
    if (!_root)
    {
        if (_root->isLeaf())
            nodes.push_back(_root.get());
        return nodes;
    }

    traverseBFS([str, &nodes](Node<T> *node) {
        if (node->contains(str))
            nodes.push_back(node);
    });

    return nodes;
}


template <class T> void Tree<T>::setSettingIndent(int indent)
{
    globalIndent = indent;
}


template <class T> void Tree<T>::addChild(int nodeIndex, std::shared_ptr<Node<T>> node)
{
    Node<T> *childNode = findNodeByIndex(nodeIndex);
    childNode->addChild(std::shared_ptr<Node<T>>(node));
}


template <class T> void Tree<T>::traverseDFS(Node<T> *node, const std::function<void(Node<T> *)> &func, DFSOrder order)
{
    if (!node)
        return;

    if (order == DFSOrder::PRE_ORDER)
        func(node);

    traverseDFS(node->leftChild(), func, order);

    if (order == DFSOrder::IN_ORDER)
        func(node);

    traverseDFS(node->rightChild(), func, order);

    if (order == DFSOrder::POST_ORDER)
        func(node);
}


template <class T>
void Tree<T>::traverseDFSWithDepth(Node<T> *node, const std::function<void(Node<T> *, int)> &func, DFSOrder order,
                                   int depth)
{
    if (!node)
        return;

    if (order == DFSOrder::PRE_ORDER)
        func(node, depth);

    traverseDFSWithDepth(node->leftChild(), func, order, depth + 1);

    if (order == DFSOrder::IN_ORDER)
        func(node, depth);

    traverseDFSWithDepth(node->rightChild(), func, order, depth + 1);

    if (order == DFSOrder::POST_ORDER)
        func(node, depth);
}


template <class T> void Tree<T>::traverseBFS(const std::function<void(Node<T> *)> &func)
{
    std::queue<Node<T> *> Q;

    if (_root)
        Q.push(_root.get());

    while (!Q.empty())
    {
        Node<T> *currentNode = Q.front();

        if (currentNode->leftChild())
            Q.push(currentNode->leftChild());
        if (currentNode->rightChild())
            Q.push(currentNode->rightChild());

        func(currentNode);

        Q.pop();
    }
}


template <class T> T Tree<T>::removeNode(size_t index)
{
    T removedData;

    size_t prevIndex = _root->getIndex();

    if (prevIndex == index)
    {
        // If root has the index searched for

        removedData = *_root->getData();
        if (_root->isLeaf())
        {
            setRoot(nullptr);
        }
        else
        {
            T dummy{};
            _root->setData(dummy);
        }
    }
    else
    {
        traverseDFS(_root.get(), [index, &prevIndex, &removedData](Node<T> *node) {
            if (node->leftChild() && node->leftChild()->getIndex() == index)
            {
                removedData = *node->leftChild()->getData();
                if (node->leftChild()->isLeaf())
                {
                    node->setLeft(nullptr);
                }
                else
                {
                    T dummy{};
                    node->leftChild()->setData(dummy);
                }
                return;
            }

            if (node->rightChild() && node->rightChild()->getIndex() == index)
            {

                removedData = *node->rightChild()->getData();
                if (node->rightChild()->isLeaf())
                {
                    node->setRight(nullptr);
                }
                else
                {
                    T dummy{};
                    node->rightChild()->setData(dummy);
                }
                return;
            }
        });
    }

    return removedData;
}

} // namespace ATree

// FORFEDREDIAGRAM_TREE_HPP
