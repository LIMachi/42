#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftprintf.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = \
mini_lib_c \
printf_flag \
mini_lib \
printf_conv_d \
printf_conv_b \
printf_conv \
printf_flag_a \
mini_lib_b \
printf_modif \
printf_arg \
printf_conv_c \
printf_pre_field \
printf_main \
printf_init

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror
#path to external includes
PINC =
#path to libs to compile
CLIB =
#exact path of lib files to add in source
LIB =
#args passed to gcc depending on the os
ARGS =

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror
#path to external includes
PINC =
#path to libs to compile
CLIB =
#exact path of lib files to add in source
LIB =
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

DOTC = $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))
DOTO = $(patsubst %, $(OBJDIR)/%.o, $(ITEMS))

INCLUDES = $(patsubst %, -I%, $(INCDIR)) $(patsubst %, -I%, $(PINC))

SUBDIRS = $(patsubst %, $(OBJDIR)/%, $(notdir $(shell find $(SRCDIR) -type d -not -path $(SRCDIR))))

.PHONY: all libs clean fclean re norm relibs fcleanlibs items test

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

grind: all
	clear
	valgrind ./$(NAME) $(EXEARGS)
