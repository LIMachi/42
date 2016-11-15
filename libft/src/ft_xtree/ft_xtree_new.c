/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtree_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:12:57 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_xtree	*ft_xtree_new(void *data, t_xtree **root, int type, int security)
{
	t_xtree						*out;
	static unsigned long long	id = 0;

	if ((out = (t_xtree*)ft_memalloc(sizeof(t_xtree))) == NULL)
		return (NULL);
	out->type = type;
	out->security = security;
	out->data = data;
	out->id = id++;
	if (root == NULL)
	{
		if ((root = (t_xtree**)ft_memalloc(sizeof(t_xtree*))) == NULL)
		{
			free(out);
			return (NULL);
		}
		*root = out;
	}
	out->root = root;
	return (out);
}
