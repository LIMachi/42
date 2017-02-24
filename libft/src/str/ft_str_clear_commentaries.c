/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_clear_commentaries.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:13:03 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 17:27:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** ft_str_clear_commentaries will set all character in comentaries to ' '
** (except '\n')
*/

char	*ft_str_clear_commentaries(char *str)
{
	char	*out;

	if (str == NULL)
		return (NULL);
	out = str;
	while (*str != '\0')
		if (*str++ == '/' && (*str == '/' || *str == '*') && (str[-1] = ' '))
		{
			if (*str == '/')
				while (*str != '\0' && *str != '\n' && (*str = ' '))
					++str;
			else if (*str == '*')
			{
				while (*str != '\0' && !(str[-1] == '*' && *str == '/'))
					if (*(str++ - 1) != '\n')
						str[-2] = ' ';
				if (str[-1] != '\n')
					str[-1] = ' ';
				if (*str == '/')
					*str = ' ';
			}
		}
	return (out);
}
