/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 01:09:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#ifdef _ERRNO_H

int	ft_global_error(int flag, long data)
{
	static int	error = 0;
	char		*tmp_str;

	if (flag == ERROR_SET || flag == ERROR_ERRNO)
		error = data * (flag == ERROR_SET) |
				errno * (flag == ERROR_ERRNO);
	error = flag == ERROR_CLEAR ? 0 : error;
	if ((flag == ERROR_PRINT) && error)
	{
		ft_putstr_fd((char*)data, 2);
		ft_log((char*)data);
		if ((tmp_str = strerror(error)) == NULL)
		{
			ft_putstr_fd("Unknown error number: ", 2);
			ft_putnbr_fd(error, 2);
			ft_putchar_fd('\n', 2);
		}
		else
			ft_putendl_fd(strerror(error), 2);
	}
	EXIT(error);
}

#else

int	ft_global_error(int flag, long data)
{
	static int	error = 0;

	error = flag == ERROR_SET ? data : error;
	if (flag == ERROR_CLEAR)
		error = 0;
	if (flag == ERROR_ERRNO)
		ft_putendl_fd("Warning: errno.h was not compiled in!", 2);
	if ((flag == ERROR_PRINT) && error)
	{
		if (data)
			ft_putstr_fd((char*)data, 2);
		if (error <= MAXERRNOD)
			ft_putendl_fd(ft_strerror(error), 2);
		else
		{
			ft_putstr_fd("Unknown error number: ", 2);
			ft_putnbr_fd(error, 2);
			ft_putchar_fd('\n', 2);
		}
	}
	EXIT(error);
}

#endif
