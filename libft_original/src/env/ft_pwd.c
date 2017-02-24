/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:30:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:36:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Return the PWD stored in env, or NULL if PWD is not set.
** Warning: the returned value is a direct pointer to env PWD, any change on
** the memory pointed by this pointer will change the env.
*/

char	*ft_pwd(void)
{
	char	*out;

	out = ft_getenv("PWD");
	if (out != NULL)
		return (out + 4 * sizeof(char));
	return (NULL);
}
