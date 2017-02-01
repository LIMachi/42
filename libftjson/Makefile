#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftjson.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = \
		ft_json_check_array_types \
		ft_json_check_string \
		ft_json_evaluate_array_size \
		ft_json_evaluate_object_size \
		ft_json_evaluate_value_type \
		ft_json_free \
		ft_json_new_array \
		ft_json_new_number \
		ft_json_new_object \
		ft_json_new_pair \
		ft_json_new_string \
		ft_json_new_value \
		ft_json_pack_value \
		ft_json_parse_src \
		ft_json_print_type \
		ft_json_search_pair_in_object \
		ft_json_string \
		ft_json_print_path

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -g -O3
#path to external includes
PINC = ../libft/inc
#path to libs to compile
CLIB = ../libft
#exact path of lib files to add in source
LIB = ../libft/libft.a
#args passed to gcc depending on the os
ARGS =

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -g
#path to external includes
PINC = ../libft/inc
#path to libs to compile
CLIB = ../libft
#exact path of lib files to add in source
LIB = ../libft/libft.a
#args passed to gcc depending on the os
ARGS =

endif

################################################################################
################################################################################
################                                                ################
################   don't change anything past this commentary   ################
################                                                ################
################################################################################
################################################################################

DATE = $(shell date +'%G-%m-%d-%Hh%Mm%Ss')

DOTC = $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))
DOTO = $(patsubst %, $(OBJDIR)/%.o, $(ITEMS))

INCLUDES = $(patsubst %, -I%, $(INCDIR)) $(patsubst %, -I%, $(PINC))

SUBDIRS = $(patsubst %, $(OBJDIR)/%, $(notdir $(shell find $(SRCDIR) -type d -not -path $(SRCDIR))))

.PHONY: all libs clean fclean re norm relibs fcleanlibs items test hell grind

all: dirs auteur libs $(NAME)

libs:
	$(foreach V, $(CLIB), make -C $(V);)

relibs:
	$(foreach V, $(CLIB), make re -C $(V);)
	make re

fcleanlibs:
	$(foreach V, $(CLIB), make clean -C $(V);)
	$(foreach V, $(CLIB), make fclean -C $(V);)
	make fclean

dirs:
	@mkdir -p $(OBJDIR) $(SUBDIRS)

ifeq ($(suffix $(NAME)), .a)
$(NAME): $(DOTO) $(LIB)
	ar -rc $(NAME) $(DOTO) $(LIB)
	ranlib $(NAME)
else
$(NAME): $(DOTO) $(LIB)
	gcc $(CFLAGS) $(ARGS) $(INCLUDES) $(DOTO) $(LIB) -o $(NAME)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f items
	rm -f `find . -type f | grep "$(OBJDIR)" | grep ".o"`
	rm -rf `find . -depth -empty | grep "$(OBJDIR)"`
	rm -rf `find . -depth -empty | grep "$(OBJDIR)"`

fclean: clean
	rm -f $(NAME)

re: fclean all

auteur:
	@echo $(AUTHOR) > auteur

norm:
	norminette $(DOTC)
	norminette $(INCDIR)
	$(foreach V, $(CLIB), make norm -C $(V);)

items:
	@echo "ITEMS = \\" > items;
	@$(foreach V, $(shell find $(SRCDIR) -type f | cut -f3- -d/ | rev | cut -f2- -d. | rev), echo "		$(V) \\" >> items;)
	@less items

test: all
	./$(NAME) $(EXEARGS)

valgrind_logs:
	mkdir -p valgrind_logs

grind: valgrind_logs all
	clear
	@echo "`valgrind --log-fd=1 --leak-check=full --show-leak-kinds=definite,indirect ./$(NAME) $(EXEARGS)`" > ./valgrind_logs/valgrind_$(DATE).log
	less ./valgrind_logs/valgrind_$(DATE).log

hell: valgrind_logs all
	clear
	@echo "hell has come to earth..."
	@echo "`valgrind -v --log-fd=1 --track-fds=yes --read-inline-info=yes --read-var-info=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(EXEARGS)`" > ./valgrind_logs/hellgrind_$(DATE).log
	@echo "time to look your fate"
	@sleep 2
	less ./valgrind_logs/hellgrind_$(DATE).log
