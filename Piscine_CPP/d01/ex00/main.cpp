//clang++ -Wall -Wextra -Werror main.cpp Pony.cpp && ./a.out

#include "Pony.hpp"

void	ponyOnTheStack()
{
	Pony pony(std::string("twilight"));

	std::cout << pony.get_name() << " is reading with zaz\n";
}

void	ponyOnTheHeap()
{
	Pony *pony = new Pony(std::string("pinkie pie"));

	std::cout << pony->get_name() << " broke the fourth wall, again\n";
	delete pony;
}

int	main()
{
	ponyOnTheHeap();
	ponyOnTheStack();
}
