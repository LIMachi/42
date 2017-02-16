#ifndef CLASS_PHONE_HPP
#define CLASS_PHONE_HPP

#include "ClassContact.hpp"

class phone
{
	public:
		phone();
		~phone();
		contact	&get_contact(int index);
		phone	&add_contact(contact new_contact);
		phone	&add_contact(int index, contact new_contact);
		phone	&print_contacts();
	private:
		contact	_contacts[8];
};

#endif //CLASS_PHONE_HPP
