#include "ClassPhone.hpp"

int	get_command()
{
	std::string	buff;

	std::cout << "enter a command (ADD, SEARCH, EXIT)\n";
	std::getline(std::cin, buff);
	if (buff == "ADD")
		return 1;
	if (buff == "SEARCH")
		return 2;
	if (buff == "EXIT")
		return 3;
	return 0;
}

int	main()
{
	std::string	str = "";
	std::cout << str.length() << '\n';
	int	_exit = 0;
	phone	_phone;
	contact	_contact;

	while (!_exit)
		switch (get_command())
		{
			case 3:
				_exit = 1;
			break;

			case 2:
				_phone.print_contacts();
			break;

			case 1:
				_phone.add_contact(_contact.enter_contact());
			break;
		}
}
