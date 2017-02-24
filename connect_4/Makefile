# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/30 23:15:42 by hmartzol          #+#    #+#              #
#    Updated: 2016/02/28 19:24:46 by hmartzol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		puissance4

SRCDIR =	src
OBJDIR =	OBJ
INCDIR =	includes
LIBDIR =	../libft

ITEMS =		main c4_prepare_grid c4_put_stone c4_print_grid c4_check_grid \
			c4_ia_input c4_clear_screen c4_player_input ftx_hook_keyinit \
			ftx_put_pixel_img ftx_put_circle ftx_put_square ftx_expose \
			ftx_clear_img ftx_hook_miceinit ftx_quit c4_ia_input_2 c4_wait

OBJ =		$(patsubst %, $(OBJDIR)/%.o, $(ITEMS))

CC =		gcc
FLAGS =		-Wall -Wextra -Werror

INCLUDE =	-I $(INCDIR)/ -I $(LIBDIR)/includes
LIBS =		-lmlx -framework OpenGL -framework AppKit
LIBNAME =	libft.a

.PHONY: all
all: $(NAME)

$(NAME): $(LIBDIR)/$(LIBNAME) auteur $(OBJDIR) $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(LIBS) $(OBJ) $(LIBDIR)/$(LIBNAME) -o $@

$(LIBDIR)/$(LIBNAME):
	make re -C $(LIBDIR)/

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBDIR)/

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBDIR)/

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	clear
	norminette $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))

auteur:
	echo "hmartzol\ntgerboui" > auteur
