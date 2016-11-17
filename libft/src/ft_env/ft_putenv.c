/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 19:00:26 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:16:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** add or change (overwrite), one environement variable of the form name=value
** will actually store the pointer to the string passed in arg, so changing
** the string further on will change the environement variable corresponding
** will return 0 on succes and -1 on failure
** failures might be ENOMEM (no more memory to store environement) or
** EINVAL (no = in the string or NULL string) (non posix)
*/

static int	sf_search(t_object *node, void *data)
{
	char	*str1;
	char	*str2;

	str1 = (char*)data;
	str2 = (char*)node->data;
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2++ && *str1 != '=')
		++str1;
	return (*str1 == '\0' || *str1 == '=');
}

int	ft_putenv(char *string)
{
	t_object	*lst;

	if (string == NULL || ft_strchr(string, '=') == NULL)
	{
		(void)ft_error(EINVAL, "Invalid string passed to ft_putenv\n");
		return (-1);
	}
	lst = ft_object_search(*ft_global_env(), &sf_search, (void*)string);
	if (lst != NULL)
		lst->data = (void*)string;
	else
	{
		if ((lst = ft_object_new((void*)string)) == NULL)
			return (-1);
		if (ft_object_add(ft_global_env(), lst) == NULL)
			return (-1);
	}
	return (0);
}
