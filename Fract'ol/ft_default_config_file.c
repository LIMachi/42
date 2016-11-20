/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_config_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 12:26:06 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/20 13:47:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** int ft_default_config_file(void):
**  if needed, will create and set a .config file
**  returns -1 on error and throw an error to ft_error
**  returns 0 if the file .config didn't need a change
**  return 1 if a new .config file was created
*/

inline static void	sf_default_config_file_0(int fd)
{
	write(fd, "#Indev .config file format by H \"LIMachi\" Martzolf\n#to", 54);
	write(fd, " read and use this file, use the libftconf.a by Hugo \"LIM", 57);
	write(fd, "achi\" Martzolf\n#All space (except in strings) are ignore", 56);
	write(fd, "d. spaces are ' ' and '\\t' only.\n#All commands are only ", 56);
	write(fd, "one line, the '\\n' is used to cut commands and should be ", 57);
	write(fd, "writen in plain text in string for returns\n#Any line with", 57);
	write(fd, " a starting # will be considered as commentary and will no", 58);
	write(fd, "t be evaluated\n#There is only four types in config: point", 57);
	write(fd, "ers to int, pointers to double, pointers to string and poi", 58);
	write(fd, "nters to functions\n#All variables names are upercase plus", 57);
	write(fd, " eventual underscores and numbers, and can be up to 24 cha", 58);
	write(fd, "rs (they are stored as 2 uint64_t)\n#<> means an arg is ob", 57);
	write(fd, "ligatory, [] means an arg is facultative, ... means the la", 58);
	write(fd, "st facultative arg can be reused multiple times\n#All stri", 58);
	write(fd, "ngs, even path, should be encased in "", if not, they will", 58);
	write(fd, " be considered as int or double, '<char>' will be consider", 58);
	write(fd, "ed as the wchar_t value of <char> stored in a int\n\n#.INT", 56);
	write(fd, "ERNAL is a special keyword to precise that the C code shou", 58);
	write(fd, "ld autofill all names listed in INTERNAL instead of using ", 58);
	write(fd, "the ones in .config\n.INTERNAL=WINDOW_NAME,ITERATIONS,VIEW", 57);
	write(fd, "_PORT\n\n#default path to the OpenCL source file\nDEFAULT_", 55);
	write(fd, "CL=\"./scl/fractol.cl\"\n\n#default kernel names found in ", 54);
	write(fd, "DEFAULT_CL\n#the search command search in a fashion close ", 57);
	write(fd, "to grep and scanf (%w means whites, tabs or space, %u mean", 58);
}

inline static void	sf_default_config_file_1(int fd)
{
	write(fd, "s unix text, only lower case, numbers and underscores, * m", 58);
	write(fd, "eans any number of chars except \\n and \\0)\n#the syntax ", 56);
	write(fd, "is make-like: $(search <text to find>, <transformation>, <", 58);
	write(fd, "source text>)\nDEFAULT_KERNEL_ID=$(search \"__kernel%wvoid", 56);
	write(fd, "%w%u%w(*)\",\" %u\", $(DEFAULT_CL))\n\n#ifeq is make-like,", 54);
	write(fd, " compares the two string passed in arg, execute if they're", 58);
	write(fd, " equivalent (space and returns aren't tested): ifeq(<strin", 58);
	write(fd, "g 1>,<string 2>)\nifeq($(KERNEL_ID),)\n\n#redefinition of ", 56);
	write(fd, "variables is valable in those config, but follow the top t", 58);
	write(fd, "o bottom rule\nKERNEL_ID=\"No kernel id where found in $(D", 56);
	write(fd, "EFAULT_CL)\"\n\n#keyword to stop a if, ifeq, ifneq or othe", 55);
	write(fd, "r if statement\nendif\n\n#string printed on invalid comman", 55);
	write(fd, "d passed to ./fractol\nUSAGE=\"Usage: ./fractol [source.cl", 56);
	write(fd, "] <kernel_id> [kernel_id] ...\\nDefault source: $(DEFAULT_", 57);
	write(fd, "CL)\\nkernel id avaliable: $(KERNEL_ID)\\n\"\n\n#string pr", 54);
	write(fd, "inted while executing ./fractol if KEY_H is pressed\nHELP=", 57);
	write(fd, "\"H: Show this help\\nMice scroll: zoom\\nMice position: c", 55);
	write(fd, "hange values of some fractals\\nMice drag left: new viewpo", 57);
	write(fd, "rt (Combo O: keep orientation/Combo R: keep ratio)\\nArrow", 57);
	write(fd, "s: move viewport\\nCombo I + PAD_+/PAD_-: change the numbe", 57);
	write(fd, "r of iterations\\nCombo C + PAD_+/PAD_-: change the color ", 57);
	write(fd, "palette\\nCombo Ctrl + S: Save screenshot (Combo A: Save w", 57);
	write(fd, "ith info)\\nD: toggle debug information\"\n\n#path to the ", 54);
	write(fd, "fonts to use to print text\nFONT_PATH=\"./resource/font.bm", 56);
}

inline static void	sf_default_config_file_2(int fd)
{
	write(fd, "p\"\n\n#keybindings, they follow the format <key1>[+key2..", 55);
	write(fd, ".]=<function> and are separed by ':'\n#the linking of keys", 57);
	write(fd, " and function is internal, and migt throw an error on inva", 58);
	write(fd, "lid key/action names or invalid function names\n#since the", 58);
	write(fd, " linking is internal, there is no need to declare keys and", 58);
	write(fd, " functions as internal\nKEY_BIND=\"KEY_H=show_help:MICE_SC", 56);
	write(fd, "ROLL_UP=zoom_plus:MICE_SCROLL_DOWN=zoom_minus:MICE_POS=set", 58);
	write(fd, "_z0:MICE_DRAG=new_view:KEY_O+MICE_DRAG=new_view_oriented:K", 58);
	write(fd, "EY_R+MICE_DRAG=new_view_ratio:KEY_O+KEY_R+MICE_DRAG=new_vi", 58);
	write(fd, "ew_oriented_ratio:KEY_R+KEY_O+MICE_DRAG=new_view_oriented_", 58);
	write(fd, "ratio:KEY_UP=move_view_port_up:KEY_DOWN=move_view_port_dow", 58);
	write(fd, "n:KEY_RIGHT=move_view_port_right:KEY_LEFT=move_view_port_l", 58);
	write(fd, "eft:KEY_I+KEY_PAD_PLUS=iteration_plus:KEY_I+KEY_PAD_MINUS=", 58);
	write(fd, "iteration_minus:KEY_C+KEY_PAD_PLUS=color_plus:KEY_C+KEY_PA", 58);
	write(fd, "D_MINUS=color_minus:KEY_CTRL+KEY_S=screensot:KEY_CTRL+KEY_", 58);
	write(fd, "A+KEY_S=screenshot_info:KEY_D=toggle_info\"\n\n#default fo", 55);
	write(fd, "rmat for the names of screenshot\nBMP_DEFAULT_NAME_FORMAT=", 57);
	write(fd, "\"$(WINDOW_NAME).bmp\"\n\n#extended (detailled) format for", 54);
	write(fd, " the names of screenshot\nBMP_EXTENDED_NAME_FORMAT=\"$(WIN", 56);
	write(fd, "DOW_NAME)-iterations:$(ITERATIONS)-view_port:$(VIEW_PORT).", 58);
	write(fd, "bmp\"\n", 5);
}

inline static int	sf_default_config_file(void)
{
	int fd;

	if ((fd = open(".config", O_WRONLY)) == -1)
	{
		ft_error(ERROR_ERRNO,
			"ft_default_config_file failed to open .config (2)\n");
		return (-1);
	}
	sf_default_config_file_0(fd);
	sf_default_config_file_1(fd);
	sf_default_config_file_2(fd);
	if (close(fd) == -1)
	{
		ft_error(ERROR_ERRNO,
			"ft_default_config_file failed to close .config (2)\n");
		return (-1);
	}
	return (1);
}

int					ft_default_config_file(void)
{
	int	fd;
	int	i;

	if ((fd = open(".config", O_RDONLY | O_CREAT)) == -1)
	{
		ft_error(ERROR_ERRNO,
			"ft_default_config_file failed to open .config (1)\n");
		return (-1);
	}
	if ((i = read(fd, &i, 1)) == -1)
	{
		ft_error(ERROR_ERRNO,
			"ft_default_config_file failed to read .config\n");
		return (-1);
	}
	if (close(fd))
	{
		ft_error(ERROR_ERRNO,
			"ft_default_config_file failed to close .config (1)\n");
		return (-1);
	}
	if (i == 1)
		return (0);
	return (sf_default_config_file());
}
