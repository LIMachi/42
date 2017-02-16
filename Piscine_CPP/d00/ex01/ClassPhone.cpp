#include "ClassPhone.hpp"

phone::phone()
{
}

phone::~phone()
{
}

contact	&phone::get_contact(int index)
{
	if (index >= 8)
	{
		std::cerr << "Invalid id: " << index << " passed to get_contact\n";
		exit(-1);
	}
	return (_contacts[index]);
}

phone	&phone::add_contact(int index, contact new_contact)
{
	if (index >= 8)
	{
		std::cerr << "Invalid id: " << index << " passed to add_contact\n";
		exit(-1);
	}
	if ((new_contact.test_initialisation() & 0b111) != 0b111)
		std::cerr << "Invalid contact passed to add_contact\n";
	else
		_contacts[index] = new_contact;
	return (*this);
}

phone	&phone::add_contact(contact new_contact)
{
	int id;
	for (id = 0; id < 8 && get_contact(id).test_initialisation() & 0b111; ++id);
	return (add_contact(id, new_contact));
}

phone	&phone::print_contacts()
{
	for(int i = 0; i < 7; ++i)
		if (_contacts[i].test_initialisation() & 0b111)
		{
			std::cout << "|         " << i << '|';
			_contacts[i].print();
			std::cout << "|\n";
		}
	return *this;
}
