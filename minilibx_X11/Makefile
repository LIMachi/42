# **************************************************************************** #
#                                                                              #
#         Improved minilibx_X11's Makefile by Hugo "LIMachi" Martzolf          #
#                                                                              #
#                      added a install and uninstall rule                      #
#        corrected the relink and false positive (make -q returning 1)         #
#           all in one makefile, no more configure or sub-makefiles            #
#                                                                              #
#             for any question, contact me: hmartzol@student.42.fr             #
#                                                                              #
# **************************************************************************** #

CC := gcc

NAME := libmlx.a

INSTALLED_NAME := $(patsubst %, /usr/local/lib/%, $(NAME))

SRC	:= mlx_init.c mlx_new_window.c mlx_pixel_put.c mlx_loop.c \
	mlx_mouse_hook.c mlx_key_hook.c mlx_expose_hook.c mlx_loop_hook.c \
	mlx_int_anti_resize_win.c mlx_int_do_nothing.c \
	mlx_int_wait_first_expose.c mlx_int_get_visual.c \
	mlx_flush_event.c mlx_string_put.c \
	mlx_new_image.c mlx_get_data_addr.c \
	mlx_put_image_to_window.c mlx_get_color_value.c mlx_clear_window.c \
	mlx_xpm.c mlx_int_str_to_wordtab.c mlx_destroy_window.c \
	mlx_int_param_event.c mlx_int_set_win_event_mask.c mlx_hook.c \
	mlx_rgb.c mlx_destroy_image.c

OBJ := $(SRC:.c=.o)

MAN := man/man1/mlx_loop.1			\
		man/man1/mlx_new_image.1	\
		man/man1/mlx_new_window.1	\
		man/man1/mlx_pixel_put.1	\
		man/man1/mlx.1				\
		man/man3/mlx_loop.1			\
		man/man3/mlx_new_image.1	\
		man/man3/mlx_new_window.1	\
		man/man3/mlx_pixel_put.1	\
		man/man3/mlx.1				\

INSTALLED_MAN := $(patsubst %, /usr/share/%, $(MAN))

HEADERS := mlx.h

INSTALLED_HEADERS := $(patsubst %, /usr/local/include/%, $(HEADERS))

INCDIRS := /usr/X11 			\
	/usr/X11/include			\
	/usr/X11R6/include			\
	/usr/X11R5/include			\
	/usr/X11R4/include			\
	/usr/include/X11			\
	/usr/include/X11R6			\
	/usr/include/X11R5			\
	/usr/include/X11R4			\
	/usr/local/X11/include		\
	/usr/local/X11R6/include	\
	/usr/local/X11R5/include	\
	/usr/local/X11R4/include	\
	/usr/local/include/X11		\
	/usr/local/include/X11R6	\
	/usr/local/include/X11R5	\
	/usr/local/include/X11R4	\
	/usr/X386/include			\
	/usr/x386/include			\
	/usr/XFree86/include/X11	\
	/usr/include				\
	/usr/local/include			\
	/usr/athena/include			\
	/usr/local/x11r5/include	\
	/usr/lpp/Xamples/include	\
	/usr/openwin/include		\
	/usr/openwin/share/include

INCDIR := $(shell conf_inc=NO; for inc in $(INCDIRS); do if [ -f "$$inc/X11/Xlib.h" -a -f "$$inc/X11/extensions/XShm.h" ]; then conf_inc=$$inc; break; fi; done; echo $$conf_inc)

HT := $(shell if [ -z "$$HOSTTYPE" ]; then echo `uname -s`; else echo $$HOSTTYPE; fi)

ifeq ($(HT), )
DOCP :=
else
DOCP := libmlx_$(HT).a
endif

ifeq ($(INCDIR), NO)
$(error "Can't find a suitable X11 include directory.")
endif

CFLAGS := -O3 -I$(INCDIR)

all: $(DOCP)

$(NAME): $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

libmlx_$(HT).a: $(NAME)
	cp $(NAME) libmlx_$(HT).a

$(INSTALLED_MAN):
	cp $(patsubst /usr/share/%, %, $@) $@

$(INSTALLED_NAME):
	cp $(patsubst /usr/local/lib/%, %, $@) $@

$(INSTALLED_HEADERS):
	cp $(patsubst /usr/local/include/%, %, $@) $@

install: all $(INSTALLED_NAME) $(INSTALLED_HEADERS) $(INSTALLED_MAN)

uninstall:
	rm -f $(INSTALLED_MAN) $(INSTALLED_HEADERS) $(INSTALLED_NAME)

clean:
	rm -f $(OBJ) $(NAME) *~ core *.core

fclean: clean
ifneq ($(DOCP), )
	rm -f $(DOCP)
endif

re: clean all
