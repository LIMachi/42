#name of the author of the executable
AUTHOR = "hmarot\nhmartzol\npbondoer\nsbouyahi"

#name of compiled file
NAME = rt

#args passed to executable if executed from "make test"
EXEARGS = scenes/test.json

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = \
		argn \
		cam \
		cl_float4_operations \
		cl_vector_from_json_array \
		main \
		cmd \
		out \
		mouse \
		direct_output \
		materials \
		textures_holder \
		parser/check_parsed_data \
		parser/default_material \
		parser/parse_camera \
		parser/parse_lights \
		parser/parse_objects \
		parser/parse_render_options \
		parser/parse_materials \
		parser/parse_images \
		parser/parse_texture \
		parser/parser \
		prim \
		rt \
		update_kernel_args \
		lights \
		ft_vector_thales

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations -g -O3
#path to external includes
PINC = ../libft/inc ../libftx2/inc ../minilibx_X11 ../libftocl/inc ../libftjson/inc
#path to libs to compile
CLIB = ../libft ../libftx2 ../minilibx_X11 ../libftocl ../libftjson
#exact path of lib files to add in source
LIB = ../libftx2/libftx2.a ../libftocl/libftocl.a ../libftjson/libftjson.a ../libft/libft.a ../minilibx_X11/libmlx.a
#args passed to gcc depending on the os
ARGS = -lOpenCL -ICL -lXext -lX11

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -g
#path to external includes
PINC = ../libft/inc ../libftx2/inc ../minilibx_macos ../libftocl/inc ../libftjson/inc
#path to libs to compile
CLIB = ../libft ../libftx2 ../minilibx_macos ../libftocl ../libftjson
#exact path of lib files to add in source
LIB = ../libftx2/libftx2.a ../libftocl/libftocl.a ../libftjson/libftjson.a ../libft/libft.a ../minilibx_macos/libmlx.a
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
	rm -f "log.txt"

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
