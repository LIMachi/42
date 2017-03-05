.obj/create_signal_code.o: create_signal_code.c
	/usr/bin/perl ~/.bin/colorgcc.pl  -Wall -Wextra -Werror -g    -I.  -I../../libft/inc -c create_signal_code.c -o  .obj/create_signal_code.o