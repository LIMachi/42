#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftocl.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = \
		ftocl_clear_current_kernel_arg \
		ftocl_data \
		ftocl_end \
		ftocl_make_program \
		ftocl_read_current_kernel_arg \
		ftocl_run_percent_callback \
		ftocl_set_current_kernel \
		ftocl_set_current_kernel_arg \
		ftocl_set_current_program \
		ftocl_start_current_kernel

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations -g -O3
#path to external includes
PINC = ../libft/inc
#path to libs to compile
CLIB = ../libft
#exact path of lib files to add in source
LIB = ../libft/libft.a
#args passed to gcc depending on the os
ARGS = -lOpenCL -ICL

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
ARGS = -framework OpenCL

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
