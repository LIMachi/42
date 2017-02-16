#include "Zombie.hpp"

class ZombieEvent
{
	public:
		ZombieEvent(const std::string &type);
		void setZombieType(const std::string &type);
		Zombie *newZombie(std::string name);
	private:
		std::string	_type;
};
