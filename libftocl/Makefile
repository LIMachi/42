#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftocl.a

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = ftocl_clear_current_kernel_arg \
		ftocl_start_current_kernel \
		ftocl_read_current_kernel_arg \
		ftocl_end \
		ftocl_make_program \
		ftocl_set_current_kernel \
		ftocl_data \
		ftocl_set_current_program \
		ftocl_set_current_kernel_arg

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations
#path to external includes
PINC = ../libft/includes
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
CFLAGS = -Wall -Wextra
#path to external includes
PINC = ../libft/includes
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

.PHONY: all libs clean fclean re norm

all: $(NAME)

libs:
	$(foreach V, $(CLIB), make -C $(V);)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) auteur libs $(DOTO)
	ar -rc $(NAME) $(FLAGS) $(DOTO) $(LIB)
	ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(DOTO)

fclean: clean
	rm -rf $(NAME)

re: fclean all

auteur:
	echo $(AUTHOR) > auteur

norm:
	clear
	norminette $(SRCDIR)
	norminette $(SRCINC)
