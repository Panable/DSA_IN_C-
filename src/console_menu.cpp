#include "console_menu.h"

void RunMenuApplication(ContactList& list)
{
	int choice = GetOptions();
	ParseOptions(choice, list);
}

int GetOptions()
{
	int choice = 0;
	std::cout << "1 - Print Contacts (LinkedList)" << std::endl;
	std::cout << "2 - Sort Contacts (LinkedList)" << std::endl;
	std::cout << "3 - Search Contacts (Hashmap)" << std::endl;
	std::cout << "4 - Print Contacts (Tree)" << std::endl;
	std::cout << "5 - EXIT" << std::endl;
	std::cin >> choice;
	std::cin.ignore();
	return choice;
}

void ParseOptions(const int& choice, ContactList& list)
{
	switch(choice)
	{
	case 0:
		exit(0);
	case 1:
		list.PrintContactsList();
		RunMenuApplication(list);
        break;
	case 2:
		list.SortByAge();
		std::cout << "SORTED!" << std::endl;
		RunMenuApplication(list);
        break;
	case 3:
		SearchMap(list);
		RunMenuApplication(list);
        break;
	case 4:
		list.PrintContactsTree();
        std::cout<<"\n";
		RunMenuApplication(list);
        break;
	case 5:
		exit(0);
	default:
		exit(0);
		break;
	}
}

void SearchMap(ContactList& list)
{
	std::string name;
	std::cout << "Enter name: " << std::endl;
	std::cin >> name;
	Contact* contact = list.SearchContacts(name);
	if(!contact)
	{
		std::cout << "Contact not found! returning..." << std::endl;
		return;
	}
	std::cout << "Contact Found!" << std::endl;
	std::cout << "Name: " << contact->GetName() << " Age: " << contact->GetAge()
			  << " Height: " << contact->GetHeight() << std::endl;
}
