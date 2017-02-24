/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 03:01:51 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/21 15:15:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftjson.h>

inline static void	sf_json_print_pair(int fd, t_json_pair *pair, int level)
{
	if (pair == NULL)
		return ;
//	while (level-- > 0)
//		ft_putchar_fd('\t', fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd(pair->key != NULL && pair->key->ptr != NULL ?
				pair->key->ptr : "(NULL)", fd);
	ft_putstr_fd("\": ", fd);
	sf_json_print(fd, pair->value, level);

}

inline static void	sf_json_print_object(int fd, t_json_object *obj, int level)
{
	long	i;
	int		l;

	if (obj == NULL)
		return ;
	i = -2l;
	while (++i <= (long)obj->nb_pairs)
	{
		l = level;
		if (i != -1l)
			while (l-- > 0)
				ft_putchar_fd('\t', fd);
		if (i == -1l || i == (long)obj->nb_pairs)
			ft_putstr_fd(i == -1l ? "{\n" : "}", fd);
		else
		{
			ft_putchar_fd('\t', fd);
			sf_json_print_pair(fd, obj->pair[i], level + 1);
			if (i != (long)obj->nb_pairs - 1)
				ft_putchar_fd(',', fd);
			ft_putchar_fd('\n', fd);
		}
	}
}

inline static void	sf_json_print_array(int fd, t_json_array *ar, int level)
{
	long	i;
	int		l;

	if (ar == NULL)
		return ;
	i = -2l;
	while (++i <= (long)ar->nb_values)
	{
		l = level;
		if (i != -1l)
			while (l-- > 0)
				ft_putchar_fd('\t', fd);
		if (i == -1l || i == (long)ar->nb_values)
			ft_putstr_fd(i == -1l ? "[\n" : "]", fd);
		else
		{
			ft_putchar_fd('\t', fd);
			sf_json_print(fd, ar->value[i], level + 1);
			if (i != (long)ar->nb_values - 1)
				ft_putchar_fd(',', fd);
			ft_putchar_fd('\n', fd);
		}
	}
}

void	sf_json_print(int fd, t_json_value *node, int level)
{
	if (node == NULL)
		return ;
	if (node->type == array)
		sf_json_print_array(fd, (t_json_array*)node->ptr, level);
	else if (node->type == object)
		sf_json_print_object(fd, (t_json_object*)node->ptr, level);
	else
		ft_json_print_data(fd, node);
}

void	ft_json_print(int fd, t_json_value *root)
{
	sf_json_print(fd, root, 0);
	ft_putchar_fd('\n', fd);
}
