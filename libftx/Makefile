#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftx.a

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = ftx_color_multiply \
		ftx_ascii \
		ftx_button \
		ftx_create_window \
		ftx_data \
		ftx_error \
		ftx_horizontal_line \
		ftx_image \
		ftx_img \
		ftx_init \
		ftx_input_hooks \
		ftx_is_button_press \
		ftx_line \
		ftx_mice_position \
		ftx_pixel \
		ftx_start \
		ftx_update \
		ftx_vertical_line \
		ftx_window

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror

#variables for Linux
ifeq ($(shell uname),Linux)

#path to external includes
PINC = ../libft/includes ../minilibx_X11
#path to libs to compile
CLIB = ../libft ../minilibx_X11
#exact path of lib files to add in source
LIB = ../libft/libft.a ../minilibx_X11/libmlx.a
#args passed to gcc depending on the os
ARGS = -Wno-deprecated -Wno-deprecated-declarations -lOpenCL -ICL -lXext -lX11

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#path to external includes
PINC = ../libft/includes ../minilibx_macos
#path to libs to compile
CLIB = ../libft ../minilibx_macos
#exact path of lib files to add in source
LIB = ../libft/libft.a ../minilibx_macos/libmlx.a
#args passed to gcc depending on the os
ARGS = -framework OpenCL -framework OpenGL -framework AppKit

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
