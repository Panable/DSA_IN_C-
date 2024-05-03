#pragma once
#include "Node.h"
#include <initializer_list>
#include <iostream>

//This class is used for constructing and using
//A linked list with the Node Class

template <typename T>
class LinkedList
{
public:
	//start and end of the linked list
	Node<T>* head;
	Node<T>* tail;

	//Default Constructor
	LinkedList()
		: head(nullptr)
		, tail(nullptr)
	{ }

	//Initialize linked list with values
	LinkedList(const std::initializer_list<T>& values)
	{
		//keep track of the previous node so we can link back to it
		Node<T>* prev = nullptr;

		//loop over every value
		for(int i = 0; i < values.size(); i++)
		{
			//initialize node with value
			T value = *(values.begin() + i);
			Node<T>* node = new Node<T>(value);

			//if the loop has just begun we are at the start of the linkedlist(head)
			//therefore we must set it as so
			if(i == 0)
				head = node;

			//link the current node and previous nodes
			Node<T>::link_nodes(prev, node);

			//set the prev node as the current node
			//because the loop is terminating
			prev = node;
		}

		//once the loop is over the previous node
		//has to be the tail
		tail = prev;
	}

	//destructor for cleaning up memory
	~LinkedList()
	{
		//begin with the start of linkedList
		Node<T>* curNode = head;

		//while the curNode is not null
		while(curNode)
		{

			//store the next node because curNode is about to be
			//deleted.
			Node<T>* nextNode = curNode->next;

			//delete the node and init the nextNode
			delete curNode;
			curNode = nextNode;
		}
	}


	//print all values in linkedList
	//note this only really works for primitives
	//if you want more control use the process function
	void print()
	{
		//begin with start of linkedList
		Node<T>* curNode = head;

		//while the curNode is not null
		while(curNode)
		{
			//print node data and init next node
			std::cout << curNode->data << std::endl;
			curNode = curNode->next;
		}
	}

	//Loops over whole linked list
	//takes in a lambda function to be processed with the curNode->data
	//Can be used for printing and other nefarious things :)
	//EX:
	//contacts.process([](const Contact& contact) {
	//    std::cout << "Name: " << contact.GetName() << ", Age: " << contact.GetAge() << std::endl;
	//});
	template <typename Lambda>
	void process(Lambda func) const
	{
		Node<T>* curNode = head;

		while(curNode)
		{
			func(curNode->data);
			curNode = curNode->next;
		}
	}

	//Searches the linked list for a particular attribute
	//returns the whole data back
	//return the boolean you want to search against in the lambda
	template <typename Lambda>
	T* Search(Lambda func) const
	{
		Node<T>* curNode = head;

		while(curNode)
		{
			if(func(curNode->data))
			{
				return &curNode->data;
			}
			curNode = curNode->next;
		}
		return nullptr;
	}

	//add a value to the tail of the linkedList
	void add(const T& x)
	{
		//if there is no head
		//i,e linked list is empty
		//then we must add the new node as the tail and the head
		if(!head)
		{
			Node<T>* newNode = new Node<T>(x);
			head = newNode;
			tail = newNode;
			return;
		}

		//initialize the new node
		Node<T>* newNode = new Node<T>(x);

		//save the current tail of the linkedList
		//so we can link the new tail with it
		Node<T>* prevTail = tail;

		//link the previous node and the new node we just added
		Node<T>::link_nodes(prevTail, newNode);

		//we're adding to the end of list
		//so we must set the new tail as the node
		//we just added
		tail = newNode;
	}

	//delete the first value match
	//in the linked list
	void deleteVal(const T& val)
	{
		//begin the search at the start
		//of the linked list
		Node<T>* curNode = head;

		//whlie curNode is not null
		while(curNode)
		{
			//we found the value, therefore we must
			//perform the delete
			if(curNode->data == val)
			{
				//store the curNodes'
				//prev and next node for linking
				//later
				Node<T>* prev = curNode->prev;
				Node<T>* next = curNode->next;

				//bools to check if the curNode was the head/tail
				//so we can set the new head/tail later
				bool isHead = (curNode == head);
				bool isTail = (curNode == tail);

				//Attach correct nodes
				//note curNode->next can be null
				//linkNodes performs these checks as it links
				Node<T>::link_nodes(prev, next);

				//no values in list, can't set head/tail
				if(isHead && isTail)
					return;

				//If it was the head/tail set it to the new head/tail
				if(isHead)
					head = next;
				if(isTail)
					tail = prev;

				//delete the node and return
				delete curNode;
				return;
			}

			//go to next iteration
			curNode = curNode->next;
		}
	}
};
