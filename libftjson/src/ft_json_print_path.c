/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_print_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 04:33:24 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 23:40:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftjson.h>

int		sf_json_print_path_array(char path[PATH_MAX], int i,
								t_json_value *tmp[2])
{
	unsigned long	t;
	int				l;
	t_json_array	*ar;
	char			*s;

	t = -1;
	ar = (t_json_array*)tmp[0]->ptr;
	while (++t < ar->nb_values)
		if (ar->value[t] == tmp[1])
			break ;
	if (t == ar->nb_values)
		ft_error(EINTERN, "ft_json_print_path found invalid node link\n");
	s = ft_itoa(t);
	l = ft_strlen(s);
	if ((i -= l + 2) < 0)
		ft_error(ENOMEM, "ft_json_print_path: calculated path is too long\n");
	path[i] = '[';
	ft_memmove(&path[i + 1], s, l);
	path[i + 1 + l] = ']';
	ft_free(s);
	return (i);
}

int		sf_json_print_path_object(char path[PATH_MAX], int i,
								t_json_value *tmp[2])
{
	unsigned long	t;
	t_json_object	*obj;

	t = -1;
	obj = (t_json_object*)tmp[0]->ptr;
	while (++t < obj->nb_pairs)
		if (obj->pair[t]->value == tmp[1])
			break ;
	if (t == obj->nb_pairs)
		ft_error(EINTERN, "ft_json_print_path found invalid node link\n");
	if ((i -= obj->pair[t]->key->length + 1) < 0)
		ft_error(ENOMEM, "ft_json_print_path: calculated path is too long\n");
	path[i] = '.';
	ft_memmove(&path[i + 1], obj->pair[t]->key->ptr, obj->pair[t]->key->length);
	return (i);
}

void	ft_json_print_path(int fd, t_json_value *v)
{
	char			path[PATH_MAX];
	int				i;
	t_json_value	*tmp[2];

	if (v == NULL)
		ft_error(EINVAL, "ft_json_print_path got NULL pointer\n");
	tmp[0] = v;
	i = PATH_MAX;
	path[--i] = '\0';
	while (tmp[0]->parent != tmp[0])
	{
		tmp[1] = tmp[0];
		tmp[0] = tmp[0]->parent;
		if (tmp[0]->type == object && tmp[0]->ptr != NULL)
			i = sf_json_print_path_object(path, i, tmp);
		else if (tmp[0]->type == array && tmp[0]->ptr != NULL)
			i = sf_json_print_path_array(path, i, tmp);
		else
			ft_error(EINTERN, "ft_json_print_path found invalid node link\n");
	}
	if ((i -= 4) < 0)
		ft_error(ENOMEM, "ft_json_print_path: calculated path is too long\n");
	ft_memmove(&path[i], "root", 4);
	ft_putstr_fd(&path[i], fd);
}
