#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftx2.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = \
		color/ftx_color_lerp \
		ftx_data \
		ftx_start \
		image/ftx_fill_image \
		image/ftx_free_image \
		image/ftx_get_pixel_img \
		image/ftx_horizontal_line \
		image/ftx_img_to_img \
		image/ftx_line \
		image/ftx_new_image \
		image/ftx_pixel \
		image/ftx_put_pixel_img \
		image/ftx_selection_square \
		image/ftx_set_cursor \
		image/ftx_slerp_pixel \
		image/ftx_vertical_line \
		image/ftx_write \
		key/ftx_key_hook \
		key/ftx_key_status \
		mice/ftx_hook_mice \
		mice/ftx_button_status \
		window/ftx_free_window \
		window/ftx_new_window \
		window/ftx_refresh_window \
		window/ftx_screenshoot \
		image/ftx_put_ubmp_img \
		ftx_loop_hook

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -g -O3
#path to external includes
PINC = ../libft/inc ../minilibx_X11
#path to libs to compile
CLIB = ../libft ../minilibx_X11
#exact path of lib files to add in source
LIB = ../libft/libft.a ../minilibx_X11/libmlx.a
#args passed to gcc depending on the os
ARGS = -lXext -lX11

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -g
#path to external includes
PINC = ../libft/inc ../minilibx_macos
#path to libs to compile
CLIB = ../libft ../minilibx_macos
#exact path of lib files to add in source
LIB = ../libft/libft.a ../minilibx_macos/libmlx.a
#args passed to gcc depending on the os
ARGS = -framework OpenGL -framework AppKit

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
