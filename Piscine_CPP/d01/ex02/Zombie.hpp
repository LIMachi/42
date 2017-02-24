#include <iostream>

class Zombie
{
	public:
		Zombie(const std::string &type, const std::string &name);
		~Zombie();
		void	announce();
	private:
		std::string _type;
		std::string _name;
};
