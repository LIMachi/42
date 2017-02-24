AUTHORS := glouyot\nhmartzol

NAME := test.bin

INCLUDES := -I../framework/ -I. -I../../libft/inc

FRAMEWORK_PATH := ../framework
FRAMEWORK_NAME := libunit.a

FLAGS := -Wall -Wextra -Werror

ARGS := ../../libft/libft.a

OBJECTS := main.o\
			strlen/00_launcher.o\
			strlen/01_basic_test.o\
			strlen/02_null_test.o

ifneq ($(shell make -q -C $(FRAMEWORK_PATH); echo $$?), 0)
.PHONY: $(FRAMEWORK_PATH)/$(FRAMEWORK_NAME)
endif

.PHONY: all test clean fclean re

all: $(NAME)

$(FRAMEWORK_PATH)/$(FRAMEWORK_NAME):
	make -C $(FRAMEWORK_PATH)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

test: $(NAME)
	./$(NAME)

$(NAME): $(FRAMEWORK_PATH)/$(FRAMEWORK_NAME) $(OBJECTS)
	gcc $(OBJECTS) $(FRAMEWORK_PATH)/$(FRAMEWORK_NAME) $(ARGS) -o $(NAME)

auteur:
	@echo $(AUTHORS) > auteur

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
