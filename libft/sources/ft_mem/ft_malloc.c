/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:35:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:42:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper for the standard function malloc (add 2 error sent directly to
** ft_error on size 0 or NULL malloc)
*/

void	*ft_malloc(size_t size)
{
	void	*out;

	if (size == 0)
		return ((void*)ft_error(EINVAL, "ft_malloc call failed: "));
	if ((out = malloc(size)) == NULL)
		return ((void*)ft_error(ENOMEM, "ft_malloc call failed: "));
	return (out);
}
