#pragma once

//nodes that can link with each other
//used in numList to construct a doubly-linked list
template <typename T>
class Node
{
public:
	Node* next;
	Node* prev;
	T data;

	//links the previous and next node
	//with eachother
	//will check if the node is null before
	//performing link :)
	static void link_nodes(Node* const prev, Node* const next)
	{
		if(prev)
			prev->next = next;
		if(next)
			next->prev = prev;
	}

	static void swap_elements(Node<T>* first, Node<T>* second)
	{
		if(!first || !second)
			return;

        auto firstP = first->data;
        first->data = second->data;
        second->data = firstP;
	}

	Node(Node* next, Node* prev, const T& data)
		: next(next)
		, data(data)
		, prev(prev)
	{ }

	Node(const T& data)
		: next(nullptr)
		, prev(nullptr)
		, data(data)
	{ }
	virtual ~Node() { }
};
