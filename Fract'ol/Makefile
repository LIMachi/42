#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = fractol

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = ft_fractol \
		ftocl_data \
		ftocl_make_program \
		ftocl_end

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror

#variables for Linux
ifeq ($(shell uname),Linux)

#path to external includes
PINC = ../libft/includes ../libftx/inc ../minilibx_X11
#path to libs to compile
CLIB = ../libft ../libftx ../minilibx_X11
#exact path of lib files to add in source
LIB = ../libftx/libftx.a ../libft/libft.a ../minilibx_X11/libmlx.a
#args passed to gcc depending on the os
ARGS = -Wno-deprecated -Wno-deprecated-declarations -lOpenCL -ICL -lXext -lX11

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#path to external includes
PINC = ../libft/includes ../libftx/inc ../minilibx_X11
#path to libs to compile
CLIB = ../libft ../libftx
#exact path of lib files to add in source
LIB = ../libftx/libftx.a ../libft/libft.a
#args passed to gcc depending on the os
ARGS = -framework OpenCL -framework OpenGL -framework AppKit -lmlx

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
	gcc $(FLAGS) $(ARGS) $(INCLUDES) $(DOTO) $(LIB) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(FLAGS) $(ARGS) $(INCLUDES) -c $< -o $@

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
