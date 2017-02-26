#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftprintf.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
SRCDIR = ./src
INCDIRS = ./inc
OBJDIR = ./OBJ

#name of files to compile without the extension
ITEMS = \
		./src/printf/ft_printf \
		./src/printf/ft_vdnprintf \
		./src/printf \
		./src/parsing/parse_number \
		./src/debug_printf_forms \
		./src/dtoa \
		./src/buffering/to_fd \
		./src/buffering/to_null \
		./src/buffering/to_str \
		./src/buffering/to_stream \
		./src/buffering/bufferize_char \
		./src/buffering/bufferize_str \
		./src/printf/ft_asnprintf \
		./src/printf/ft_asprintf \
		./src/printf/ft_dnprintf \
		./src/printf/ft_dprintf \
		./src/printf/ft_fnprintf \
		./src/printf/ft_fprintf \
		./src/printf/ft_vdprintf \
		./src/printf/ft_vfnprintf \
		./src/printf/ft_vfprintf \
		./src/printf/ft_vprintf \
		./src/printf/ft_vsnprintf \
		./src/printf/ft_vsprintf \
		./src/printf/ft_snprintf \
		./src/printf/ft_sprintf \
		./src/printf/ft_vasnprintf \
		./src/printf/ft_vasprintf \
		./src/parsing/parse_args


CC = gcc #clang #x86_64-apple-darwin15.6.0-gcc-4.8

AR = ar #x86_64-apple-darwin15.6.0-gcc-ar-4.8

RANLIB = ranlib #x86_64-apple-darwin15.6.0-gcc-ranlib-4.8

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror #-g -arch X86_64
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
CFLAGS = -Wall -Wextra -Werror #-g -arch X86_64
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

DOTC = $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))
DOTO = $(patsubst %, $(OBJDIR)/%.o, $(ITEMS))

INCLUDES = $(patsubst %, -I%, $(INCDIRS)) $(patsubst %, -I%, $(PINC))

.PHONY: all clean fclean re norm libs relibs fcleanlibs items test grind hell

all: dirs auteur libs $(NAME)

libs:
ifneq ($(shell [[ 0 = 0$(patsubst %, && `make -q -C %; echo $$?` = 0, $(CLIB)) ]]; echo $$?), 0)
	$(foreach V, $(CLIB), make -C $(V);)
endif

relibs:
	$(foreach V, $(CLIB), make re -C $(V);)
	@$(MAKE) re

fcleanlibs: fclean
	$(foreach V, $(CLIB), make clean -C $(V);)
	$(foreach V, $(CLIB), make fclean -C $(V);)

ifneq ($(OBJDIR), )
SUBDIRS = $(patsubst %, $(OBJDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v $(OBJDIR)))
dirs:
ifeq ($(shell [[ -d $(OBJDIR) $(patsubst %, && -d %, $(SUBDIRS)) ]]; echo $$?), 1)
	mkdir -p $(SUBDIRS)
endif
endif

ifeq ($(suffix $(NAME)), .a)
$(NAME): $(DOTO) $(LIB)
	$(AR) -rc $(NAME) $(DOTO) $(LIB)
	$(RANLIB) $(NAME)
else
$(NAME): $(DOTO) $(LIB)
	$(CC) $(CFLAGS) $(ARGS) $(INCLUDES) $(DOTO) $(LIB) -o $(NAME)
endif

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(ARGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f items
	rm -f test.bin
	rm -f $(DOTO)
	if [ -z "$(find $(OBJDIR) -type f)" ]; then rm -rf $(OBJDIR); fi	#test if OBJDIR contain no more files, and if true, remove it (safer)

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

auteur:
	@echo $(AUTHOR) > auteur

norm:
	norminette $(DOTC)
	norminette $(INCDIRS)

items:
	@echo "ITEMS = \\" > items;
	@$(foreach V, $(shell find $(SRCDIR) -type f | grep "\.c" | rev | cut -f2- -d. | rev), echo "		$(V) \\" >> items;)
	@less items

ifeq ($(suffix $(NAME)), .a)
test: all
	$(CC) main.c $(ARGS) $(INCLUDES) $(LIB) $(NAME) -o test.bin
	./test.bin $(EXEARGS)
else
test: all
	./$(NAME) $(EXEARGS)
endif

grind: all
	clear
	valgrind ./$(NAME) $(EXEARGS)
