#include "ClassContact.hpp"

contact::~contact()
{

}

contact::contact()
{
	_last_name="";
	_first_name="";
	_nickname="";
	_login="";
	_postal_address="";
	_email_address="";
	_phone_number="";
	_birthday_date="";
	_favorite_meal="";
	_underwear_color="";
	_darkest_secret="";
}

int		contact::test_initialisation()
{
	int	out = 0;

	out |= (0 != _first_name.length());
	out |= (0 != _last_name.length()) << 1;
	out |= (0 != _nickname.length()) << 2;
	out |= (0 != _login.length()) << 3;
	out |= (0 != _postal_address.length()) << 4;
	out |= (0 != _email_address.length()) << 5;
	out |= (0 != _phone_number.length()) << 6;
	out |= (0 != _birthday_date.length()) << 7;
	out |= (0 != _favorite_meal.length()) << 8;
	out |= (0 != _underwear_color.length()) << 9;
	out |= (0 != _darkest_secret.length()) << 10;
	return (out);
}

std::string	contact::get_first_name()
{
	return (_first_name);
}

std::string	contact::get_last_name()
{
	return (_last_name);
}

std::string	contact::get_nickname()
{
	return (_nickname);
}

void	contact::_print_data(std::string str)
{
	int	len = str.length();
	str.resize(10);
	for (size_t l = len - 1; l < 10; ++l)
		std::cout << ' ';
	std::cout << str;
}

contact	&contact::print_first_name()
{
	_print_data(_first_name);
	return (*this);
}

contact	&contact::print_last_name()
{
	_print_data(_last_name);
	return (*this);
}

contact	&contact::print_nickname()
{
	_print_data(_nickname);
	return (*this);
}

contact	&contact::print()
{
	print_first_name();
	std::cout << '|';
	print_last_name();
	std::cout << '|';
	print_nickname();
	return (*this);
}

contact	&contact::enter_contact()
{
	std::cout << "Enter first name:\n";
	std::getline(std::cin, _first_name);
	std::cout << "Enter last name:\n";
	std::getline(std::cin, _last_name);
	std::cout << "Enter nickname:\n";
	std::getline(std::cin, _nickname);
	std::cout << "Enter login:\n";
	std::getline(std::cin, _login);
	std::cout << "Enter postal address:\n";
	std::getline(std::cin, _postal_address);
	std::cout << "Enter email address:\n";
	std::getline(std::cin, _email_address);
	std::cout << "Enter phone number:\n";
	std::getline(std::cin, _phone_number);
	std::cout << "Enter birthday date:\n";
	std::getline(std::cin, _birthday_date);
	std::cout << "Enter favorite meal:\n";
	std::getline(std::cin, _favorite_meal);
	std::cout << "Enter underwear color:\n";
	std::getline(std::cin, _underwear_color);
	std::cout << "Enter darkest secret:\n";
	std::getline(std::cin, _darkest_secret);
	std::cout << "Contact added\n";
	return (*this);
}
