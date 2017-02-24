/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 18:54:20 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 19:52:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

int	print_red(int fd_out, char *str, unsigned long size)
{
	write(fd_out, TF_RED, 5);
	write(fd_out, str, size);
	write(global_fd_log(), str, size);
	return (write(fd_out, TF_RESET, 5));
}

int	print_green(int fd_out, char *str, unsigned long size)
{
	write(fd_out, TF_GREEN, 5);
	write(fd_out, str, size);
	write(global_fd_log(), str, size);
	return (write(fd_out, TF_RESET, 5));
}

int	print_cyan(int fd_out, char *str, unsigned long size)
{
	write(fd_out, TF_LIGHT_CYAN, 5);
	write(fd_out, str, size);
	write(global_fd_log(), str, size);
	return (write(fd_out, TF_RESET, 5));
}

int	print_yellow(int fd_out, char *str, unsigned long size)
{
	write(fd_out, TF_YELLOW, 5);
	write(fd_out, str, size);
	write(global_fd_log(), str, size);
	return (write(fd_out, TF_RESET, 5));
}

int	print(int fd_out, char *str, unsigned long size)
{
	write(fd_out, str, size);
	return (write(global_fd_log(), str, size));
}
