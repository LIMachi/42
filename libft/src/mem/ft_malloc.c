/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:35:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:01:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper for the standard function malloc (add 2 error sent directly to
** ft_error on size 0 or NULL malloc)
*/

#if !defined(FT_USE_FINAL_FREE) || FT_USE_FINAL_FREE == 0

void	*ft_malloc(size_t size)
{
	void	*out;

	if (size == 0)
		return ((void*)ft_error(EINVAL, "ft_malloc call failed: "));
	if ((out = malloc(size)) == NULL)
		return ((void*)ft_error(ENOMEM, "ft_malloc call failed: "));
	return (out);
}

#else

/*
** in final free mode, also store a copy of the pointer returned for a final
** free, this mode is slightly more memory and time consumming, but can avoid
** final leaks and might help keeping track of all pointers at any time
*/

void	*ft_malloc(size_t size)
{
	void	*out;

	if (size == 0)
		return ((void*)ft_error(EINVAL, "ft_malloc call failed: "));
	if ((out = malloc(size)) == NULL)
		return ((void*)ft_error(ENOMEM, "ft_malloc call failed: "));
	if (ft_pile_push(ft_global_malloc_stack(), out) == NULL)
		return ((void*)ft_error(ENOMEM, "ft_malloc stacking call failed: "));
	return (out);
}

#endif
