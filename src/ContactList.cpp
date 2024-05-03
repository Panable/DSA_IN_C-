#include "ContactList.h"
#include <iostream>
#include <vector>

ContactList::~ContactList()
{
	delete hashTable;
}

ContactList::ContactList(const std::initializer_list<Contact>& values)
	: linkedList(values)
	, binaryTree(values)
{
	std::vector<std::string> keys;

	for(int i = 0; i < values.size(); i++)
	{
		Contact curContact = *(values.begin() + i);
		keys.push_back(curContact.GetName());
	}

	hashTable = new HashTable<std::string, Contact>(keys, values);
}

//My head is pounding right now
//so the code I'm writing might not be the best
//time to write my first bubble sort algo
//Edit: too easy for me im the freaking best
void ContactList::SortByAge()
{
	//we start at the head of the linkedList
	Node<Contact>* currentNode = this->linkedList.head;

	//if we've sorted this pass, then we know to sort on next pass
	bool keepSorting = true;

	while(keepSorting)
	{
		Node<Contact>* currentNode = this->linkedList.head;
		keepSorting = false;
		while(currentNode->next)
		{
			Node<Contact>* first = currentNode;
			Node<Contact>* second = currentNode->next;

			//swap elements if age is higher, and sort on nextPass
			if(first->data.GetAge() > second->data.GetAge())
			{
				keepSorting = true;
				Node<Contact>::swap_elements(first, second);

				//next node is ahead of us now, so just go to next cycle
				continue;
			}

			currentNode = currentNode->next;
		}
	}
}

void ContactList::PrintContactsList()
{
	this->linkedList.process([](const Contact& contact) {
		std::cout << "Name: " << contact.GetName() << ", Age: " << contact.GetAge() << std::endl;
	});
}

void ContactList::PrintContactsTree()
{
    std::function<std::string(Contact)> func = [](Contact contact) {
        return contact.GetName();
    };

    this->binaryTree.PrintTreeFull(func);
}

Contact* ContactList::SearchContacts(std::string name)
{
	return hashTable->GetValue(name);
}
