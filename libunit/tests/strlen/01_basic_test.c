/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:29:08 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 17:12:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*
** length returned by ft_strlen should be the same has strlen for same input
*/

int	basic_test(void)
{
	char	buff[1024];

	write(1, "truc", 5);
	lseek(1, -5, SEEK_CUR);
	read(1, buff, 5);
	if (memcmp(buff, "truc", 5))
		return (-1);
	else
		return (0);
//	if (ft_strlen("Hello") == strlen("Hello"))
//		return (0);
//	else
//		return (-1);
}
