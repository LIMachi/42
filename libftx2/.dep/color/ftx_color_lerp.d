.obj/color/ftx_color_lerp.o: src/color/ftx_color_lerp.c
	/usr/bin/perl ~/.bin/colorgcc.pl  -Wall -Wextra -Werror -g   -Iinc  -I../libft/inc  -I../minilibx_macos -c src/color/ftx_color_lerp.c -o  .obj/color/ftx_color_lerp.o