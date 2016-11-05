OBJECTS =	srcs/ft_putchar.o \
			srcs/ft_putstr.o \
			srcs/ft_strcmp.o \
			srcs/ft_strlen.o \
			srcs/ft_swap.o

libft.a: $(OBJECTS)
	ar -rcs libft.a $(OBJECTS)

%.o : %.c
	gcc -Wall -Wextra -Werror -I./includes/ -o $@ -c $<

.PHONY: all clean fclean re

all: libft.a

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f libft.a

re: fclean all
