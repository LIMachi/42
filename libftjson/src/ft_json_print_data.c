/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_print_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 01:05:28 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/25 23:46:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftjson.h>

inline static int	sf_json_print_data(int fd, t_json_value *node)
{
	if (node->type == string)
	{
		ft_putchar_fd('\"', fd);
		ft_putstr_fd(((t_json_string*)node->ptr)->ptr, fd);
		ft_putchar_fd('\"', fd);
	}
	if (node->type == integer)
		ft_putnbr_fd(*(int*)node->ptr, fd);
//	if (node->type == number)
//		ft_printf("%f", *(double*)node->ptr);
	if (node->type == array)
	{
		ft_putstr_fd("(t_json_array*)", fd);
		ft_putnbr_hex_fd((unsigned long)node->ptr, fd);
	}
	if (node->type == object)
	{
		ft_putstr_fd("(t_json_object*)", fd);
		ft_putnbr_hex_fd((unsigned long)node->ptr, fd);
	}
	return (0);
}

int					ft_json_print_data(int fd, t_json_value *node)
{
	if (node == NULL)
	{
		ft_putstr_fd("NULL pointed value", fd);
		return (-1);
	}
	if (node->type == none)
	{
		ft_putstr_fd("invalid typed value", fd);
		return (-1);
	}
	if (node->type == string && ((t_json_string*)node->ptr)->ptr == NULL)
	{
		ft_putstr_fd("NULL pointed string", fd);
		return (-2);
	}
	if (node->type == null || node->ptr == NULL)
		ft_putstr_fd("null", fd);
	if (node->type == boolean)
		ft_putstr_fd(*(int*)node->ptr ? "true" : "false", fd);
	return (sf_json_print_data(fd, node));
}
