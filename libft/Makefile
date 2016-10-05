# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/15 00:21:43 by hmartzol          #+#    #+#              #
#    Updated: 2016/06/22 13:40:40 by hmartzol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =

SRCDIR =
OBJDIR =
INCDIR =

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBS =

OS = $(shell uname)

ifeq ($(SRCDIR), )
ifneq ($(wildcard src/.), )
SRCDIR = src
else
SRCDIR = .
endif
endif

DOTC = $(shell find $(SRCDIR) -maxdepth 1 -type f | grep -e '\.c$$')

MAINP = main(
ifneq ($(DOTC), )
MAINFOUND = $(shell grep -l -e"$(MAINP)" $(DOTC))
endif

ifeq ($(INCDIR), )
ifneq ($(wildcard includes/.), )
INCDIR = includes
else
ifneq ($(wildcard include/.), )
INCDIR = include
else
ifneq ($(wildcard inc/.), )
INCDIR = inc
else
INCDIR = .
endif
endif
endif
endif

ifeq ($(NAME), )
ifneq ($(MAINFOUND), )
NAME = $(notdir $(basename $(MAINFOUND)))
else
ifneq ($(shell find $(INCDIR) -type f | grep -e '\.h$$'), )
NAME = $(notdir $(basename $(shell find includes -type f | grep -e '\.h$$' | head))).a
else
NAME = $(shell pwd | rev | cut -f 1 -d '/' | rev).a
endif
endif
endif

INCLUDES = $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$')

ifeq ($(OBJDIR), )
OBJDIR = OBJ
endif

ifneq ($(INCLUDES), )
MLXFOUND = $(shell grep '\#*include\ <mlx.h>' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
ifeq ($(MLXFOUND), )
MLXFOUND = $(shell grep '\#*include\ \"mlx.h\"' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
endif
endif
ifeq ($(MLXFOUND), )
MLXFOUND = $(shell grep '\#*include\ <mlx.h>' $(DOTC))
ifeq ($(MLXFOUND), )
MLXFOUND = $(shell grep '\#*include\ \"mlx.h\"' $(DOTC))
endif
endif

ifneq ($(INCLUDES), )
MATHFOUND = $(shell grep '\#*include\ <math.h>' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
ifeq ($(MATHFOUND), )
MATHFOUND = $(shell grep '\#*include\ \"math.h\"' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
endif
endif
ifeq ($(MATHFOUND), )
MATHFOUND = $(shell grep '\#*include\ <math.h>' $(DOTC))
ifeq ($(MATHFOUND), )
MATHFOUND = $(shell grep '\#*include\ \"math.h\"' $(DOTC))
endif
endif
ifneq ($(MATHFOUND), )
MATHLIB = -lm
endif

ifneq ($(INCLUDES), )
PTHFOUND = $(shell grep '\#*include\ <pthread.h>' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
ifeq ($(PTHFOUND), )
PTHFOUND = $(shell grep '\#*include\ \"pthread.h\"' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
endif
endif
ifeq ($(PTHFOUND), )
PTHFOUND = $(shell grep '\#*include\ <pthread.h>' $(DOTC))
ifeq ($(PTHFOUND), )
PTHFOUND = $(shell grep '\#*include\ \"pthread.h\"' $(DOTC))
endif
endif
ifneq ($(PTHFOUND), )
PTHLIB = -lpthread
endif

ifeq ($(OS),Linux)
TASKS = $(shell 1 + $(shell grep -c ^processor /proc/cpuinfo))
ifneq ($(MLXFOUND), )
ifneq ($(wildcard minilibx_X11/.),)
MLX = minilibx_X11
LMLX = libmlx.a
MLXFLAGS = -lXext -lX11 minilibx_X11/libmlx.a
IMLX = -Iminilibx_X11
else
MLXFLAGS = -lXext -lX11 -lmlx
endif
endif
endif
ifeq ($(OS),Darwin)
TASKS = $(shell 1 + $(shell system_profiler | awk '/Number Of CPUs/{print $4}{next;}'))
ifneq ($(MLXFOUND), )
ifneq ($(wildcard minilibx/.),)
MLX = minilibx
LMLX = libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit minilibx/libmlx.a
IMLX = -Iminilibx
else
MLXFLAGS = -framework OpenGL -framework AppKit -lmlx
endif
endif
endif

OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(DOTC))

ifneq ($(NAME), libft.a)
ifneq ($(INCLUDES), )
LFTFOUND = $(shell grep '\#*include\ <libft.h>' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
ifeq ($(LFTFOUND), )
LFTFOUND = $(shell grep '\#*include\ \"libft.h\"' $(shell find $(INCDIR) -maxdepth 1 -type f | grep -e '\.h$$'))
endif
endif
ifeq ($(LFTFOUND), )
LFTFOUND = $(shell grep '\#*include\ <libft.h>' $(DOTC))
ifeq ($(LFTFOUND), )
LFTFOUND = $(shell grep '\#*include\ \"libft.h\"' $(DOTC))
endif
endif
ifneq ($(LFTFOUND), )
ifneq ($(wildcard libft/.), )
LIBFT = libft
LLIBFT = libft.a
LFLAGS = libft/libft.a
ifneq ($(wildcard libft/includes/.), )
ILIBFT = -Ilibft/includes
else
ifneq ($(wildcard libft/include/.), )
ILIBFT = -Ilibft/include
else
ifneq ($(wildcard libft/inc/.), )
ILIBFT = -Ilibft/inc
else
ILIBFT = -Ilibft
endif
endif
endif
LDEP = libft
endif
endif
endif

ifneq ($(MLXFOUND), )
DEP = $(LDEP) mlx
endif

INCLUDES = $(shell find $(INCDIR) $(MLX) $(LIBFT) -maxdepth 1 -type f | grep -e '\.h$$')

.PHONY: all
all: auteur $(NAME)

ifneq ($(MAINFOUND), )
$(NAME): trash $(DEP) allobj
	@echo "compiling executable"
	@$(CC) $(FLAGS) $(ILIBFT) $(IMLX) $(LIBS) $(OBJ) $(MLXFLAGS) $(LFLAGS) $(MATHLIB) $(PTHLIB) -o $(NAME)
else
$(NAME): trash $(DEP) allobj
	@echo "compiling library"
	@ar -rcs $(NAME) $(ILIBFT) $(IMLX) $(LIBS) $(OBJ) $(MLXFLAGS) $(LFLAGS) $(MATHLIB) $(PTHLIB)
	@ranlib $(NAME)
endif

ifneq ($(LIBFT), )
.PHONY: libft
libft:
	@echo "making libft"
	@test '$(LIBFT)' != '' && make -C $(LIBFT) --no-print-directory
endif

ifneq ($(MLXFOUND), )
.PHONY: mlx
ifneq ($(MLX), )
mlx:
	@echo "making mlx"
	@test '$(MLX)' != '' && make -C $(MLX) --no-print-directory
else
mlx:
	@echo "using standard mlx"
endif
endif

.PHONY: allobj
allobj:
	@echo "making objects"
	@make makeobj -j$(NPROCS) AOBJ="$(OBJ)" --no-print-directory #--silent

.PHONY: makeobj
makeobj: $(OBJDIR) $(AOBJ)
	@echo "objects made"

$(OBJDIR):
	@echo "creating dir $(OBJDIR)"
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(FLAGS) -c $< -o $@ $(patsubst %, -I%, $(INCDIR)) $(ILIBFT) $(IMLX)

TRASH = $(shell find `pwd` -type f | grep -e "/\._" -e "~$$" -e "\.swp$$" -e "\.DS_Store$$") $(shell find `pwd` -type f | grep -e "/\#" | grep -e "\#$$")

.PHONY: trash
ifneq ('$(TRASH)', ' ')
trash:
	@echo "trashing unwanted files"
	@rm -f $(TRASH)
else
trash:
	@echo "no trash to clear"
endif

.PHONY: clean
.PHONY: fclean

ifneq ($(LIBFT), )
ifneq ($(MLX), )
clean: trash
	@make clean -C $(LIBFT) --no-print-directory
	@make clean -C $(MLX) --no-print-directory
	@rm -rf $(OBJDIR)
fclean: trash
	@make clean -C $(MLX) --no-print-directory
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME)
else
clean: trash
	@make clean -C $(LIBFT) --no-print-directory
	@rm -rf $(OBJDIR)
fclean: trash
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME)
endif
else
ifneq ($(MLX), )
clean: trash
	@make clean -C $(MLX) --no-print-directory
	@rm -rf $(OBJDIR)
fclean: trash
	@make clean -C $(MLX) --no-print-directory
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME)
else
clean: trash
	@rm -rf $(OBJDIR)
fclean: trash
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME)
endif
endif

.PHONY: re
re: fclean all

auteur:
	@echo "creating default auteur file"
	@echo "hmartzol" > auteur
