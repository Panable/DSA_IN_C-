#include "ContactList.h"
#include "console_menu.h"
#include <string>
int main()
{
	auto contactData = std::initializer_list<Contact>{Contact("Jeffrey", 12, 200),
													  Contact("Jill", 18, 600),
													  Contact("Jack", 11, 12),
													  Contact("Chelton", 1000000, 1),
													  Contact("Mason", 20, 185),
													  Contact("Stormeous", 8, 3),
													  Contact("wolfman", 0, 0)};

	ContactList contactList(contactData);
	RunMenuApplication(contactList);
	return 0;
}
