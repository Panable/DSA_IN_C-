#include "Contact.h"

Contact::Contact() { }
Contact::Contact(const std::string& name, const int& age, const int& height)
	: name(name)
	, age(age)
	, height(height)
{ }
Contact::~Contact() { }

//GETTERS AND SETTERS FOR CONTACT
void Contact::SetName(const std::string& name)
{
	this->name = name;
}
void Contact::SetAge(const int& age)
{
	this->age = age;
}
void Contact::SetHeight(const int& height)
{
	this->height = height;
}

std::string Contact::GetName() const
{
	return name;
}
int Contact::GetAge() const
{
	return age;
}
int Contact::GetHeight() const
{
	return height;
}
