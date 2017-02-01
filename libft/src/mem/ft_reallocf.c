/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:04:00 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 16:48:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** fake reallocf from FreeBSD, will always free ptr, and prototype differ
*/

void	*ft_reallocf(void *ptr, size_t size_original, size_t size_new)
{
	void	*out;

	if ((out = ft_malloc(size_new)) == NULL)
		return ((void*)ft_error(ENOMEM, "reallocf didn't allocate memory\n"));
	if (size_original > size_new)
		size_original = size_new;
	if (ptr != NULL)
	{
		if (size_original > 0)
			ft_memmove(out, ptr, size_original);
		ft_free(ptr);
	}
	return (out);
}
