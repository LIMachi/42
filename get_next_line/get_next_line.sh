#gcc -Wall -Wextra -Werror -o get_next_line.o -c get_next_line.c
#gcc -Wall -Wextra -Werror -o main.o -c main.c
gcc -Wall -Wextra -o get_next_line.o -c get_next_line.c
gcc -Wall -Wextra -o main.o -c main.c
gcc -o test_gnl main.o get_next_line.o
./test_gnl $1
