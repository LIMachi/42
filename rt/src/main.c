/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:15:54 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/25 23:47:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "mlx.h"

void		rt(void)
{
	calc_vpul();
	update_kernel_args();
	if (cmd()->output != NULL)
		direct_output(cmd()->output);
	ftx_new_window(ft_point(argn()->screen_size.x, argn()->screen_size.y),
			"RT", NULL);
	ftx_key_hook(KEY_EXIT, cb_exit, NULL);
	ftx_key_hook(KEY_P, cb_exit, NULL);
	update(1);
	ftx_loop_hook(&keys);
	mlx_hook(ftx_data()->focused_window->win, 4, 1, mouse_click, NULL);
	mlx_hook(ftx_data()->focused_window->win, 5, 1, mouse_off, NULL);
	mlx_hook(ftx_data()->focused_window->win, 6, 1, mouse_move, NULL);
	ftx_start();
}

int			main(const int argc, char **argv, char **env)
{
	int		fd;
	char	*src;

	ft_init(env);
	if (command_line(argc, argv))
		ft_end(0 /* ft_printf("\nUsage: \t%s/%s <scene.json>\n\n", ft_pwd(),
					ft_path_name(argv[0]))*/);
	if ((fd = open(cmd()->scene, O_RDONLY)) == -1)
		ft_end(-1);
	parser(src = ft_readfile(fd));
	close(fd);
	ft_free(src);
	if ((fd = open(OCL_SOURCE_PATH, O_RDONLY)) == -1)
		ft_end(-1);
	ftocl_make_program(ft_str_to_id64("rt"),
			src = ft_str_clear_commentaries(ft_readfile(fd)), NULL);
	close(fd);
	if (!(fd = ftocl_set_current_kernel(ft_str_to_id64("rt_kernel"))))
		rt();
	ft_free(src);
	if (fd == 1)
		ft_end(0 /* ft_printf("kernel was not found\n")*/);
	ft_end(0);
}
