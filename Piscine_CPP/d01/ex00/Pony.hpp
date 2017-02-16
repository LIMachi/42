#include <iostream>

class Pony
{
	public:
		Pony();
		Pony(const std::string &name);
		~Pony();
		std::string get_name();

	private:
		std::string _name;
};
