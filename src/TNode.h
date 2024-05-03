#pragma once
#include <iostream>

//Binary Tree Node
template <typename T>
class TNode
{
public:
    //Tree Node Connections
    TNode* parent;
    TNode* left;
    TNode* right;
    T data;

    //construct with value
    TNode(const T& value) : left(nullptr), right(nullptr), parent(nullptr), data(value) {}

    //construct with parent
    TNode(TNode* parent): left(nullptr), right(nullptr), parent(parent) {}

    //default constructor
    TNode() : left(nullptr), right(nullptr), parent(nullptr) {}

    //Cleans leftover nodes
    //TODO
    virtual ~TNode(){}

protected:
private:
};

