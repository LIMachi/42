void	ZombieEvent(const std::string &type)
{
	_type = type;
}

void	ZombieEvent::setZombieType(const std::string &type)
{
	_type = type;
}

Zombie *ZombieEvent::newZombie(std::string name)
{
	return new Zombie(_type, name);
}
