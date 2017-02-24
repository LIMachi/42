NAME := phone
CC := clang++
FLAGS := -Wall -Wextra -Werror
OBJ :=	main.o \
		ClassPhone.o \
		ClassContact.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
