/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:49:56 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 13:14:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>
#include <libftx.h>
#include <fractol.h>

/*
** return print all kernel names found in source and return the number of
** names print this way (return -1 on error)
*/

int		print_kernel_names(const char *ocl_src)
{
	char	*tmp;
	int		out;
	char	name_buff[128];
	int		i;

	tmp = ((char*)ocl_src) - 1;
	out = 0;
	while ((tmp = ft_strstr(tmp + 1, "__kernel")) != NULL && ++out)
	{
		tmp += 8;
		while (ft_isspace(*tmp))
			++tmp;
		while (ft_isalnum(*tmp))
			++tmp;
		while (ft_isspace(*tmp))
			++tmp;
		i = 0;
		while (ft_isunix(*tmp) && i < 127)
			name_buff[i++] = *tmp++;
		name_buff[i] = '\0';
		ft_putendl(name_buff);
	}
	return (out);
}

int		print_usage(char *name)
{
	char	*tmp;
	int		fd;

	ft_putstr("Usage: ");
	if ((tmp = ft_strrchr(name, '/')) == NULL)
		ft_putstr(name);
	else
		ft_putstr(tmp + 1);
	ft_putstr(" [source.cl] <kernel_id>\n");
	ft_putstr("Kernel ids found in default ./scl/fractol.cl:\n");
	if ((fd = open("./scl/fractol.cl", O_RDONLY)) == -1)
		ft_putstr("./scl/fractol.cl can't be oppened\n");
	else
	{
		if ((tmp = ft_readfile(fd)) == NULL)
			ft_putstr("./scl/fractol.cl can't be read\n");
		close(fd);
		if (print_kernel_names(ft_str_clear_commentaries(tmp)) == 0)
			ft_putstr("Can't find kernel names in ./scl/fractol.cl\n");
		ft_free(tmp);
	}
	ft_end(0);
	return (0);
}

void	print_no_id(char *src, char *ptr)
{
	ft_putstr("There was no fractal correcponding to the id passed in arg");
	ft_putstr(". Valid id for ");
	ft_putstr(src);
	ft_putstr(" are:\n");
	print_kernel_names(ptr);
}

int		main(int argc, char **argv, char **env)
{
	int		fd;
	char	*src;
	char	*ptr;

	ft_init(env);
	if (argc < 2 || argc > 3)
		return (print_usage(argv[0]));
	src = argc == 2 ? "./scl/fractol.cl" : argv[1];
	if ((fd = open(src, O_RDONLY)) == -1)
		return (-1);
	ftocl_make_program(ft_str_to_id64("fractol"),
						ft_str_clear_commentaries(ptr = ft_readfile(fd)), NULL);
	close(fd);
	fractol_data()->lock = ft_str_to_id64(argv[argc - 1]) !=
												ft_str_to_id64("julia");
	if (!(fd = ftocl_set_current_kernel(ft_str_to_id64(argv[argc - 1]))))
		fractol();
	if (fd == 1)
		print_no_id(src, ptr);
	ftocl_end();
	return (0);
}
