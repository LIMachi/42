/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:29:08 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 19:50:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*
** length returned by ft_strlen should be the same has strlen for same input
*/

int	basic_test(void)
{
	if (ft_strlen("salut") == strlen("salut"))
		return (0);
	else
		return (-1);
}
