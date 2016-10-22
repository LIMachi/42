/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:48:16 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:46:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper for the standard function free (add 1 error sent directly to
** ft_error on NULL ptr)
*/

void	ft_free(void *ptr)
{
	if (ptr == NULL)
	{
		(void)ft_error(EINVAL, "ft_free call failed: ");
		return ;
	}
	free(ptr);
}
