/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_print_clike.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 01:25:05 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/21 15:15:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftjson.h>

inline static void	sf_json_print_clike_object(int fd, t_json_object *obj)
{
	unsigned long	i;

	if (obj == NULL)
		return ;
	i= 0;
	while (i < obj->nb_pairs)
		if (obj->pair[i++] != NULL && obj->pair[i - 1]->value != NULL)
			ft_json_print_clike(fd, obj->pair[i - 1]->value);
}

inline static void	sf_json_print_clike_array(int fd, t_json_array *ar)
{
	unsigned long	i;

	if (ar == NULL)
		return ;
	i = 0;
	while (i < ar->nb_values)
		if (ar->value[i++] != NULL)
			ft_json_print_clike(fd, ar->value[i - 1]);
}

void				ft_json_print_clike(int fd, t_json_value *root)
{
	if (root == NULL)
		return ;
	if (root->type == array)
	{
		ft_putstr_fd("//array size: ", fd);
		ft_putnbr_fd(((t_json_array*)root->ptr)->nb_values, fd);
		ft_putchar_fd('\n', fd);
	}
	if (root->type == object)
	{
		ft_putstr_fd("//object size: ", fd);
		ft_putnbr_fd(((t_json_object*)root->ptr)->nb_pairs, fd);
		ft_putchar_fd('\n', fd);
	}
	ft_json_print_path(fd, root);
	ft_putstr_fd(" = ", fd);
	ft_json_print_data(fd, root);
	ft_putstr_fd(";\n", fd);
	if (root->type == array)
		sf_json_print_clike_array(fd, (t_json_array*)root->ptr);
	if (root->type == object)
		sf_json_print_clike_object(fd, (t_json_object*)root->ptr);
}
