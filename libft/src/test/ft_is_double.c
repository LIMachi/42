/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 21:31:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/16 18:51:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** return 1 if str points to a string of the form "[ +-][0-9][.fFdDeE]"
** (C format double)
*/

int				ft_is_double(const char *str)
{
	unsigned long	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (ft_isdigit(str[i]))
		++i;
	return (ft_isinset(str[i], ".fFdDeE"));
}
