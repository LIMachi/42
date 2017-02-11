/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_null_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:30:59 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 06:33:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*
** ft_strlen should segfault on NULL input like strlen
*/

int	null_test(void)
{
	ft_strlen(NULL);
	return (-1);
}
