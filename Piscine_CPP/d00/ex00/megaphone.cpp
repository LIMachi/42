#include <iostream>

int main(const int argc, char *argv[])
{
	if (argc <= 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	else
	{
		for (int i = 1; argv[i] != NULL; ++i)
			for (int j = 0; argv[i][j] != '\0'; ++j)
				std::cout << (char)toupper(argv[i][j]);
		std::cout << '\n';
	}
	return 0;
}
