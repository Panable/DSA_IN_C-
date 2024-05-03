#pragma once
#include <iostream>

class Contact
{
public:
	//default Constructor
	Contact();

	//Constructs the contact with values
	Contact(const std::string& name, const int& age, const int& height);

	//Destroys the Contact
	virtual ~Contact();

	//Sets the name of the contact
	void SetName(const std::string& name);
	//Sets the age of the contact
	void SetAge(const int& age);
	//Sets the height of the contact
	void SetHeight(const int& height);

	//Gets the name of the contact
	std::string GetName() const;
	//Gets the age of the contact
	int GetAge() const;
	//Gets the height of the contact
	int GetHeight() const;

protected:
private:
	std::string name;
	int age;
	int height;
};
