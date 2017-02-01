/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:24:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	**ft_strlsplit(char *s, char c)
{
	char	*i;
	t_list	**lst;
	char	*ptr;

	if ((lst = (t_list **)ft_malloc(sizeof(t_list *))) == NULL)
		return (NULL);
	*lst = NULL;
	if (s != NULL && s[0])
	{
		ptr = s;
		while (*ptr && (i = ft_strchr(ptr, c)) != NULL)
		{
			ft_lstappend(lst, ft_lstnew(ft_strsub(ptr, 0, i - ptr + 1),
										(int)(i - ptr + 1)));
			ptr = i + 1;
		}
		if (*ptr)
			ft_lstappend(lst, ft_lstnew(ft_strdup(ptr), ft_strlen(ptr) + 1));
	}
	return (lst);
}
