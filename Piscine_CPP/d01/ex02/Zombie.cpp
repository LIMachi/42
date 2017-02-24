#include "Zombie.hpp"

Zombie::Zombie(const std::string &type, const std::string &name)
{
	_type = type;
	_name = name;
}

Zombie::~Zombie()
{

}

void	Zombie::announce()
{
	std::cout << "<" << _name << " (" << _type << ")> Braiiiiiinnnnsss....\n";
}
