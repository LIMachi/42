/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:19:22 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 19:52:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

#if OS == LINUX

void		*sf_protected_mlx_init(void)
{
	void	*mlx;
	int		err;

	err = 0;
	if (*ft_global_env() == NULL && (err = 1))
	{
		ft_log("Bad corrector, 'env -i' is bad, and you should fell bad for ");
		ft_log("doing this :´(\nShuting down gracefully anyway\n");
	}
	if (!err && ft_getenv("DISPLAY") == NULL && (err = 1))
	{
		ft_log("Weird, I can't found that damn display... oh, right, 'env -u ");
		ft_log("DISPLAY' must have been there earlier, this filthy stealer. O");
		ft_log("h well, no show tonight\n");
	}
	if (!err && (mlx = mlx_init()) == NULL)
	{
		err = 1;
		ft_log("mlx_init() failed, and I just don't know what went wrong :(\n");
	}
	if (err == 1)
		ft_end(-1);
	if (err == 1)
		return (NULL);
	return (mlx);
}

#else

void		*sf_protected_mlx_init(void)
{
	void	*mlx;
	int		err;

	err = 0;
	if (*ft_global_env() == NULL && (err = 1))
	{
		ft_log("Bad corrector, 'env -i' is bad, and you should fell bad for ");
		ft_log("doing this :´(\nShuting down gracefully anyway\n");
	}
	if (!err && (mlx = mlx_init()) == NULL)
	{
		err = 1;
		ft_log("mlx_init() failed, and I just don't know what went wrong :(\n");
	}
	if (err == 1)
		ft_end(-1);
	if (err == 1)
		return (NULL);
	return (mlx);
}

#endif

t_ftx_data	*ftx_data(void)
{
	static t_ftx_data	data = {.mlx = NULL, .windows = NULL, .images = NULL,

	.focused_window = NULL, .tick = 0, .loop_callback = NULL};
	if (data.mlx == NULL)
		data.mlx = sf_protected_mlx_init();
	return (&data);
}
