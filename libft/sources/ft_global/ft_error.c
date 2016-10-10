/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 11:40:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** global error function used in most of my ft_functions and programs.
** used like errno, but can also store strings to print detailed errors.
** note: this do not use any exit() or stop() or break(), you might have to
** stop your program with the calling of if (ft_error(FT_ERROR_CHECK)) return;
*/

/*
** list of flags:
**	FT_ERROR_SET: uses data to set the global error
**	FT_ERROR_CLEAR: discard the last error (set it to 0)
**	FT_ERROR_PRINT: print the error and return the error code, if there is
**					if data is set, will only print the error if the stored
**					error is equal to data
**	FT_ERROR_ERRNO: catch the errno and store it, if there is a code, print it,
**	and return it (note: flag unused if errno.h is not compiled in)
** return:
** return the last error value stored (might not be equal to errno)
*/

#ifdef _ERRNO_H
int	ft_error(int flag, long data)
{
	static int	error = 0;
	char		*tmp_str;

	if (flag == ERROR_SET || flag == ERROR_ERRNO)
		error = data * (flag == ERROR_SET) |
				errno * (flag == ERROR_ERRNO);
	error = flag == ERROR_CLEAR ? 0 : error;
	if ((flag == ERROR_PRINT || flag == ERROR_ERRNO) && error)
	{
		if (data)
			ft_putstr_fd((char*)data, 2);
		if ((tmp_str = strerror(error)) == NULL)
		{
			ft_putstr_fd("Unknown error number: ", 2);
			ft_putnbr_fd(error, 2);
			ft_putchar_fd('\n', 2);
		}
		else
			ft_putendl_fd(strerror(error), 2);
	}
	return (error);
}
#else
int	ft_error(int flag, long data)
{
	static int	error = 0;

	error = flag == ERROR_SET ? data : error;
	if (flag == ERROR_CLEAR)
		error = 0;
	if (flag == ERROR_ERRNO)
		ft_putendl_fd("Warning: errno.h was not compiled in!", 2);
	if ((flag == ERROR_PRINT || flag == ERROR_ERRNO) && error)
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
	return (error);
}
#endif
