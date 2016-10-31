/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_page.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 05:44:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/29 05:52:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** create 3 static pages of 1GB and a stack of 256MB for ft_malloc_pgc and
** other pseudo allocation functions
*/

static void	*sf_page0(void)
{
	static unsigned char	p[1 MEM_G];

	return ((void*)p);
}

static void	*sf_page1(void)
{
	static unsigned char	p[1 MEM_G];

	return ((void*)p);
}

static void	*sf_page2(void)
{
	static unsigned char	p[1 MEM_G];

	return ((void*)p);
}

static void	*sf_stack(void)
{
	static unsigned char	s[256 MEM_M];

	return ((void*)s);
}

t_page_3gs	ft_page(void)
{
	return (
		(t_page_3gs){
			.p0 = sf_page0(),
			.p1 = sf_page1(),
			.p2 = sf_page2(),
			.stack = sf_stack(),
			.stack_used_pos = 0,
			.stack_free_pos = 0
		}
	);
}
