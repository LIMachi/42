/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 20:11:48 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 22:28:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** search in the environement the environement variable corresponding to the
** name, return a pointer to said environement, or NULL if there was no match
*/

static int	sf_search(t_object *node, void *data)
{
	char	*str1;
	char	*str2;

	str1 = (char*)data;
	str2 = (char*)node->data;
	while (*str1 != '\0' && *str2 != '\0' && *str1++ == *str2++)
		;
	return (*str1 == '\0');
}

char		*ft_getenv(const char *name)
{
	t_object	*tmp;

	tmp = ft_object_search(*ft_global_env(), &sf_search, (void*)name);
	if (tmp != NULL)
		return ((char*)tmp->data);
	return (NULL);
}
