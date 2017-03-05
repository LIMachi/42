#name of the author of the executable (used by the creation of the auteur file)
AUTHOR = hmartzol

#name of compiled file (if the 'a' extension is used, the makefile will use the library compilation mode)
NAME = test.bin

#args passed to executable if executed from "make test"
EXEARGS = full.json

#path to folder containing source files, project header and resulting objects
#note: SRCDIR and INCDIRS can be ".", but try to have a diferent path for objects
#note: SRCDIR and OBJDIR must only contain one path, INCDIRS can have multiple paths
SRCDIR = src
INCDIRS = .
OBJDIR = .obj

#path to a main function containing file to test the library (if the output is a library)
MAIN =

#path of files (from $(SRCDIR)) to compile without the extension (you can run "make items" to get them in the file "items")
#include items
ITEMS = test

#variables for Linux
ifeq ($(shell uname),Linux)

#CC flags
CFLAGS = -Wall -Wextra -Werror -g #-O2 -arch X86_64
#path to external includes
PINC = ../../libft/inc ../inc
#path to libs to compile
CLIB = ../../libft ../
#exact path of lib files to add in source
LIB = ../libftjson.a ../../libft/libft.a
#args passed to CC depending on the os
ARGS =

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#CC flags
CFLAGS = -Wall -Wextra -Werror -g #-O2 -arch X86_64
#path to external includes
PINC = ../../libft/inc ../inc
#path to libs to compile
CLIB = ../../libft ../
#exact path of lib files to add in source
LIB = ../libftjson.a ../../libft/libft.a
#args passed to CC depending on the os
ARGS =

endif

################################################################################
################################################################################
################                                                ################
################   don't change anything past this commentary   ################
################                                                ################
################################################################################
################################################################################

DEPDIR = .dep

CC = /usr/bin/perl ~/.bin/colorgcc.pl #/usr/bin/clang

AR = /usr/bin/ar

RANLIB = /usr/bin/ranlib

RM = /bin/rm -f

NORMINETTE = /usr/bin/sh ~/.bin/norminette.sh

DOTC = $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))
DOTO = $(patsubst %, $(OBJDIR)/%.o, $(ITEMS))
DOTD = $(patsubst %, $(DEPDIR)/%.d, $(ITEMS))

INCLUDES = $(patsubst %, -I%, $(INCDIRS)) $(patsubst %, -I%, $(PINC))

.PHONY: all clean fclean re norm libs relibs cleanlibs fcleanlibs items test grind hell
.PRECIOUS: $(DOTD) items
.SUFFIXES:

all: dirs auteur libs $(NAME)

$(shell mkdir -p $(DEPDIR) $(patsubst %, $(DEPDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v -F $(DEPDIR) | cut -f2- -d/)) >/dev/null)	#create dependendies/rules subdirs

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
	@$(MAKE) re	#delay the re to make sure all libs are compiled before $(NAME)

fcleanlibs: fclean
	$(foreach V, $(CLIB), make fclean -C $(V);)

cleanlibs: clean
	$(foreach V, $(CLIB), make clean -C $(V);)

ifneq ($(OBJDIR), )
SUBDIRS = $(patsubst %, $(OBJDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v -F $(OBJDIR) | cut -f2- -d/))
dirs:
ifeq ($(shell [[ -d $(OBJDIR) $(patsubst %, && -d %, $(SUBDIRS)) ]]; echo $$?), 1)
	mkdir -p $(OBJDIR) $(SUBDIRS)
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
	$(RM) -f $(DOTO)
	$(RM) items
	$(RM) -f test.bin
	$(shell if [ -z "`find $(OBJDIR) -type f`" ]; then $(RM) -r $(OBJDIR); fi)	#test if OBJDIR contain no more files, and if true, remove it (safer)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

auteur:
	@echo $(AUTHOR) > auteur

norm:
	$(NORMINETTE) $(DOTC)
	$(NORMINETTE) $(INCDIRS)

items:
	@printf "ITEMS = " > items;
	@$(foreach V, $(shell find $(SRCDIR) -type f | grep "\.c" | rev | cut -f2- -d. | rev | cut -f2- -d/), echo "	$(V) \\" >> items;)
	@sed -i "" '$$s/..$$//' items

ifeq ($(suffix $(NAME)), .a)
test: all
ifneq ($(MAIN), )
	$(CC) $(MAIN) $(ARGS) $(INCLUDES) $(LIB) $(NAME) -o test.bin
	./test.bin $(EXEARGS)
else
	echo "main function containing file was not set"
endif
else
test: all
	./$(NAME) $(EXEARGS)
endif

grind: all
	clear
	valgrind ./$(NAME) $(EXEARGS)
