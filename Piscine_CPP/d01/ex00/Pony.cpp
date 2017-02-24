#include "Pony.hpp"

Pony::Pony()
{
	_name = "Unnamed";
	std::cout << "A new unnamed pony joined the herd\n";
}

Pony::Pony(const std::string &name)
{
	_name = name;
	std::cout << "The pony \"" << name << "\" joined the herd\n";
}

Pony::~Pony()
{
	std::cout << "The pony \"" << _name << "\" left the herd\n";
}

std::string Pony::get_name()
{
	return (_name);
}
