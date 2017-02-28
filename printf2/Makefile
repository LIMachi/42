#name of the author of the executable
AUTHOR = hmartzol

#name of compiled file
NAME = libftprintf.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
SRCDIR = src
INCDIRS = inc
OBJDIR = .obj

#name of files to compile without the extension
#include items
ITEMS = \
		buffering/bufferize_char \
		buffering/bufferize_str \
		buffering/to_fd \
		buffering/to_null \
		buffering/to_str \
		buffering/to_stream \
		debug_printf_forms \
		dtoa \
		parsing/parse_args \
		parsing/parse_number \
		printf/ft_asnprintf \
		printf/ft_asprintf \
		printf/ft_dnprintf \
		printf/ft_dprintf \
		printf/ft_fnprintf \
		printf/ft_fprintf \
		printf/ft_printf \
		printf/ft_snprintf \
		printf/ft_sprintf \
		printf/ft_vasnprintf \
		printf/ft_vasprintf \
		printf/ft_vdnprintf \
		printf/ft_vdprintf \
		printf/ft_vfnprintf \
		printf/ft_vfprintf \
		printf/ft_vprintf \
		printf/ft_vsnprintf \
		printf/ft_vsprintf \
		printf \
		printf/main_printf

#variables for Linux
ifeq ($(shell uname),Linux)

#gcc/clang flags
CFLAGS = -Wall -Wextra -Werror -g #-arch X86_64
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
CFLAGS = -Wall -Wextra -Werror -g #-arch X86_64
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

CC = colorgcc.pl #clang

AR = ar #x86_64-apple-darwin15.6.0-gcc-ar-4.8

RANLIB = ranlib #x86_64-apple-darwin15.6.0-gcc-ranlib-4.8

DEPDIR = .dep

DOTC = $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))
DOTO = $(patsubst %, $(OBJDIR)/%.o, $(ITEMS))
DOTD = $(patsubst %, $(DEPDIR)/%.d, $(ITEMS))

INCLUDES = $(patsubst %, -I%, $(INCDIRS)) $(patsubst %, -I%, $(PINC))

.PHONY: all clean fclean re norm libs relibs fcleanlibs items test grind hell
.PRECIOUS: $(DOTD) items
.SUFFIXES:

all: dirs auteur libs $(NAME)

$(shell mkdir -p $(patsubst %, $(DEPDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v -F $(DEPDIR) | cut -f2- -d/)) >/dev/null)	#create dependendies/rules subdirs

$(DEPDIR)/%.d: $(SRCDIR)/%.c
ifeq ($(SRCDIR), )
	$(CC) -M -MT $(patsubst %.c, $(OBJDIR)/%.o, $<) $(INCLUDES) $< > $@
	printf "\t$(CC) $(CFLAGS) $(ARGS) $(INCLUDES) -c $< -o $(patsubst %.c, $(OBJDIR)/%.o, $<)" >> $@
else
ifeq ($(SRCDIR), .)
	$(CC) -M -MT $(patsubst %.c, $(OBJDIR)/%.o, $<) $(INCLUDES) $< > $@
	printf "\t$(CC) $(CFLAGS) $(ARGS) $(INCLUDES) -c $< -o $(patsubst %.c, $(OBJDIR)/%.o, $<)" >> $@
else
	$(CC) -M -MT $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<) $(INCLUDES) $< > $@
	printf "\t$(CC) $(CFLAGS) $(ARGS) $(INCLUDES) -c $< -o $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<)" >> $@
endif
endif

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
SUBDIRS = $(patsubst %, $(OBJDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v -F $(OBJDIR) | cut -f2- -d/))
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

-include $(DOTD)

clean:
	rm -f items
	rm -f test.bin
	rm -f $(DOTO)
	if [ -z "$(find $(OBJDIR) -type f)" ]; then rm -rf $(OBJDIR); fi	#test if OBJDIR contain no more files, and if true, remove it (safer)

fclean: clean
	rm -f $(DOTD)
	if [ -z "$(find $(DEPDIR) -type f)" ]; then rm -rf $(DEPDIR); fi
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

auteur:
	@echo $(AUTHOR) > auteur

norm:
	norminette $(DOTC)
	norminette $(INCDIRS)

items:
	@printf "ITEMS = " > items;
	@$(foreach V, $(shell find $(SRCDIR) -type f | grep "\.c" | rev | cut -f2- -d. | rev | cut -f2- -d/), echo "	$(V) \\" >> items;)
	@sed -i "" '$$s/..$$//' items

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
