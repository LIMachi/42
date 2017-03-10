#name of the author of the executable (used by the creation of the auteur file)
AUTHOR = hmartzol

#name of compiled file (if the 'a' extension is used, the makefile will use the library compilation mode)
NAME = libftocl.a

#args passed to executable if executed from "make test"
EXEARGS =

#path to folder containing source files, project header and resulting objects
#note: SRCDIR and INCDIRS can be ".", but try to have a diferent path for objects
#note: SRCDIR and OBJDIR must only contain one path, INCDIRS can have multiple paths
SRCDIR = src
INCDIRS = inc
OBJDIR = .obj

#path to a main function containing file to test the library (if the output is a library)
MAIN =

#path of files (from $(SRCDIR)) to compile without the extension (you can run "make items" to get them in the file "items")
#include items
ITEMS = ftocl_clear_current_kernel_arg \
	ftocl_data \
	ftocl_end \
	ftocl_make_program \
	ftocl_read_current_kernel_arg \
	ftocl_run_percent_callback \
	ftocl_set_current_kernel \
	ftocl_set_current_kernel_arg \
	ftocl_set_current_program \
	ftocl_start_current_kernel \
	ftocl_str_to_id64

#variables for Linux
ifeq ($(shell uname),Linux)

#CC flags
CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations -g -O3
#path to external includes
PINC = ../libft/inc
#path to libs to compile
CLIB = ../libft
#exact path of lib files to add in source
LIB = ../libft/libft.a
#args passed to CC/ar on final link depending on the os
LARGS = -lOpenCL -ICL

endif

#variables for Max
ifeq ($(shell uname),Darwin)

#CC flags
CFLAGS = -Wall -Wextra -Werror -g
#path to external includes
PINC = ../libft/inc
#path to libs to compile
CLIB = ../libft
#exact path of lib files to add in source
LIB = ../libft/libft.a
#args passed to CC/ar on final link depending on the os
LARGS = -framework OpenCL

endif

include ../Makefiles/Makefile.gen

################################################################################
################################################################################
################                                                ################
################   don't change anything past this commentary   ################
################                                                ################
################################################################################
################################################################################
#
# DEPDIR = .dep
#
# CC = gcc #/usr/bin/perl ~/.bin/colorgcc.pl #/usr/bin/clang
#
# AR = ar #/usr/bin/ar
#
# RANLIB = ranlib #/usr/bin/ranlib
#
# RM = rm -f #/bin/rm -f
#
# NORMINETTE = /usr/bin/sh ~/.bin/norminette.sh
#
# DOTC = $(patsubst %, $(SRCDIR)/%.c, $(ITEMS))
# DOTO = $(patsubst %, $(OBJDIR)/%.o, $(ITEMS))
# DOTD = $(patsubst %, $(DEPDIR)/%.d, $(ITEMS))
#
# INCLUDES = $(patsubst %, -I%, $(INCDIRS)) $(patsubst %, -I%, $(PINC))
#
# .PHONY: all clean fclean re norm libs relibs cleanlibs fcleanlibs items test grind hell redep
# .PRECIOUS: $(DOTD) items auteur
# .SUFFIXES:
#
# all: dirs auteur libs $(NAME)
#
# redep:
# 	@printf "rebuilding dependencies/rules: "
# 	@$(RM) $(DOTD)
# 	@if [ -z "$$(find $(DEPDIR) -type f)" ]; then $(RM) -r $(DEPDIR); fi
# 	@$(MAKE) -s $(DOTD)
# 	@printf "\nall dependencies/rules have been rebuilt\n"
#
# $(DEPDIR)/%.d: $(SRCDIR)/%.c
# 	@mkdir -p $(DEPDIR) $(patsubst %, $(DEPDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v -F $(DEPDIR) | cut -f2- -d/)) >/dev/null
# 	@printf "."
# ifeq ($(SRCDIR), )
# 	@$(CC) -M -MT $(patsubst %.c, $(OBJDIR)/%.o, $<) $(INCLUDES) $< > $@
# 	@printf "\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(patsubst %.c, $(OBJDIR)/%.o, $<)" >> $@
# else
# ifeq ($(SRCDIR), .)
# 	@$(CC) -M -MT $(patsubst %.c, $(OBJDIR)/%.o, $<) $(INCLUDES) $< > $@
# 	@printf "\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(patsubst %.c, $(OBJDIR)/%.o, $<)" >> $@
# else
# 	@$(CC) -M -MT $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<) $(INCLUDES) $< > $@
# 	@printf "\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<)" >> $@
# endif
# endif
#
# libs:
# ifneq ($(shell [[ 0 = 0$(patsubst %, && `make -q -C %; echo $$?` = 0, $(CLIB)) ]]; echo $$?), 0)
# 	@echo "rebuilding needed static libraries"
# 	@$(foreach V, $(CLIB), make -C $(V);)
# 	@echo "all needed static libraries have been rebuilt"
# endif
#
# relibs:
# 	@echo "rebuilding needed static libraries"
# 	@$(foreach V, $(CLIB), make re -C $(V);)
# 	@echo "all needed static libraries have been rebuilt"
# 	@$(MAKE) re
#
# fcleanlibs: fclean
# 	@echo "fclean-ing all static libraries"
# 	@$(foreach V, $(CLIB), make fclean -C $(V);)
# 	@echo "all static libraries have been fclean-ed"
#
# cleanlibs: clean
# 	@echo "cleaning all static libraries"
# 	@$(foreach V, $(CLIB), make clean -C $(V);)
# 	@echo "all static libraries have been cleaned"
#
# ifneq ($(OBJDIR), )
# SUBDIRS = $(patsubst %, $(OBJDIR)/%, $(shell find $(SRCDIR) -type d -not -path $(SRCDIR) | grep -v -F $(OBJDIR) | cut -f2- -d/))
# dirs:
# ifeq ($(shell [[ -d $(OBJDIR) $(patsubst %, && -d %, $(SUBDIRS)) ]]; echo $$?), 1)
# 	@mkdir -p $(OBJDIR) $(SUBDIRS)
# 	@echo "made directory '$(OBJDIR)' to hold temporary object files"
# endif
# endif
#
# $(NAME): $(DOTO) $(LIB)
# ifeq ($(suffix $(NAME)), .a)
# 	$(AR) -rc $(NAME) $(DOTO) $(LIB)
# 	$(RANLIB) $(NAME)
# else
# 	$(CC) $(CFLAGS) $(LARGS) $(INCLUDES) $(DOTO) $(LIB) -o $(NAME)
# endif
#
# -include $(DOTD)
#
# clean:
# 	$(RM) -f $(DOTO)
# 	$(RM) items
# 	$(RM) -f test.bin
# 	if [ -z "$$(find $(OBJDIR) -type f)" ]; then $(RM) -r $(OBJDIR); fi
#
# fclean: clean
# 	$(RM) -f $(NAME)
#
# re: fclean
# 	@$(MAKE) all
#
# auteur:
# 	@echo $(AUTHOR) > auteur
#
# norm:
# 	$(NORMINETTE) $(DOTC)
# 	$(NORMINETTE) $(INCDIRS)
#
# items:
# 	@printf "ITEMS = " > items;
# 	@$(foreach V, $(shell find $(SRCDIR) -type f | grep "\.c" | rev | cut -f2- -d. | rev | cut -f2- -d/), echo "	$(V) \\" >> items;)
# 	@sed -i "" '$$s/..$$//' items
#
# ifeq ($(suffix $(NAME)), .a)
# test: all
# ifneq ($(MAIN), )
# 	$(CC) $(MAIN) $(LARGS) $(INCLUDES) $(LIB) $(NAME) -o test.bin
# 	./test.bin $(EXEARGS)
# else
# 	echo "main function containing file was not set"
# endif
# else
# test: all
# 	./$(NAME) $(EXEARGS)
# endif
#
# grind: all
# 	clear
# 	valgrind ./$(NAME) $(EXEARGS)
