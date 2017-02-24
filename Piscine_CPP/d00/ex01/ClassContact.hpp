#ifndef CLASS_CONTACT_HPP
#define CLASS_CONTACT_HPP

#include <iostream>

class contact
{
	public:
		contact();
		~contact();
		std::string	get_first_name();
		std::string	get_last_name();
		std::string	get_nickname();
		int		test_initialisation();
		contact	&print();
		contact	&print_first_name();
		contact	&print_last_name();
		contact	&print_nickname();
		contact	&enter_contact();

	private:
		void		_print_data(std::string str);
		std::string	_first_name;		//0
		std::string	_last_name;			//1
		std::string	_nickname;			//2
		std::string	_login;				//3
		std::string	_postal_address;	//4
		std::string	_email_address;		//5
		std::string	_phone_number;		//6
		std::string	_birthday_date;		//7
		std::string	_favorite_meal;		//8
		std::string	_underwear_color;	//9
		std::string	_darkest_secret;	//10
};

#endif //CLASS_CONTACT_HPP
