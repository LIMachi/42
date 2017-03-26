AUTHOR := hmartzol
NAME := 3Dengine
EXEARGS :=

SRCDIR := src
INCDIRS := inc
OBJDIR := .obj
DEPDIR := .dep

CFLAGS := -Wall -Wextra -Werror -O2 -g -Wno-deprecated -Wno-deprecated-declarations -pthread
PINC := ../libft/inc ../libftx2/inc ../libftocl/inc ../libftjson/inc ../glfw-3.2.1/deps
LPINC := ../minilibx_X11
MPINC := ../minilibx_macos
LCLIB := ../libft ../libftx2 ../minilibx_X11 ../libftocl ../libftjson
MCLIB := ../libft ../libftx2 ../minilibx_macos ../libftocl ../libftjson
LLIB := ../libftx2/libftx2.a ../libftocl/libftocl.a ../libftjson/libftjson.a ../libft/libft.a ../minilibx_X11/libmlx.a
MLIB := ../libftx2/libftx2.a ../libftocl/libftocl.a ../libftjson/libftjson.a ../libft/libft.a ../minilibx_macos/libmlx.a
LLARGS := -lOpenCL -ICL -lXext -lX11 -lglfw -lGL -lpthread
MLARGS = -framework OpenCL -framework OpenGL -framework AppKit ../glfw-3.2.1/src/libglfw3.a -lpthread

include ../Makefiles/Makefile.gen
