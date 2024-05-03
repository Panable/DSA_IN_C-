//1. Print Contacts (LinkedList)
//2. Print Contacts (BinaryTree)
//3. Sort Contacts (LinkedList)
//4. Search Contacts (HashMap)

#pragma once
#include "ContactList.h"
void RunMenuApplication(ContactList& list);
int GetOptions();
void ParseOptions(const int& choice, ContactList& list);
void SearchMap(ContactList& list);
