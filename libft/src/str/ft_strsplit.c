/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:41:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	ft_creat_tab(char const *s, char **str, char c)
{
	int i;
	int len;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i + len] != c && s[i + len])
				len++;
			str[j] = ft_strsub(s, i, len);
			++j;
		}
		i = i + len;
	}
	str[j] = NULL;
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;

	str = NULL;
	if (s != NULL)
	{
		str = (char **)ft_malloc(sizeof(char *) * ft_strcntc(s, c) + 1);
		if (str != NULL)
			ft_creat_tab(s, str, c);
	}
	return (str);
}
