/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:48:16 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 01:06:57 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper for the standard function free (add 1 error sent directly to
** ft_error on NULL ptr), returns NULL on any case
*/

#if !defined(FT_USE_FINAL_FREE) || FT_USE_FINAL_FREE == 0

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

#else

/*
** in final free mode, this function will also search and NULLify occurences of
** ptr in the malloc stack, to avoid multiples frees on ft_final_free call
*/

void	*ft_free(void *ptr)
{
	size_t	i;
	int		found;

	if (ptr == NULL)
	{
		(void)ft_error(EINVAL, "ft_free call failed: ");
		return (NULL);
	}
	found = 0;
	i = 0;
	while (i < ft_global_malloc_stack()->head)
	{
		if (ft_global_malloc_stack()->data[i] == ptr && (found = 1))
			ft_global_malloc_stack()->data[i] = NULL;
		++i;
	}
	if (found == 0)
		ft_log(
			"Warning: ft_free called on pointer not allocated by ft_malloc\n");
	free(ptr);
	return (NULL);
}

#endif
