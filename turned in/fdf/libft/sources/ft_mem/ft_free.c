/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:48:16 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/25 21:16:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper for the standard function free (add 1 error sent directly to
** ft_error on NULL ptr), returns NULL on any case
*/

void	*ft_free(void *ptr)
{
	if (ptr == NULL)
	{
		(void)ft_error(EINVAL, "ft_free call failed: ");
		return (NULL);
	}
	free(ptr);
	return (NULL);
}
