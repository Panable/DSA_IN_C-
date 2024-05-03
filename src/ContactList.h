#pragma once
#include "BinaryTree.h"
#include "Contact.h"
#include "HashTable.h"
#include "LinkedList.h"
class ContactList
{
public:
    BinaryTree<Contact> binaryTree;
    LinkedList<Contact> linkedList;
    HashTable<std::string, Contact>* hashTable;
	ContactList(const std::initializer_list<Contact>& values);
    void SortByAge();
    void PrintContactsList();
    void PrintContactsTree();
    Contact* SearchContacts(std::string name);
	virtual ~ContactList();

protected:
private:
};

