void	memoryLeak()
{
	std::string*	panthere = new std::string("String pathere");

	std::cout << *pathere << std::endl;
	delete panthere;
}
