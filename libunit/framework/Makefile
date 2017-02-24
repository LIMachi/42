AUTHORS := glouyot\nhmartzol

NAME := libunit.a

FLAGS := -Wall -Wextra -Werror

OBJECTS := launch_test.o \
			load_test.o \
			call_test.o \
			create_signal_code.o \
			global_fd_log.o \
			print.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS) auteur
	ar -rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

auteur:
	@echo $(AUTHORS) > auteur

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
