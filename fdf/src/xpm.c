/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 09:31:43 by hmartzol          #+#    #+#             */
/*   Updated: 2016/08/10 11:10:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

char	*remove_c_commentaries(char *str)
{
	char *ptr;
	char *out;

	if (str == NULL)
		return (NULL);
	ptr = ft_strdup(str);
	out = ptr;
	while (*str)
	{
		if (*str == '/' && (*(str + 1) == '/' || *(str + 1) == '*'))
		{
			++str;
			if (*str++ == '/')
				while (*str != '\n' || *str)
					++str;
			else
				while (!(*(str - 1) == '*' && *str == '/') || !++str)
					++str;
		}
		*ptr++ = *str++;
	}
	*ptr = 0;
	return (out);
}

char	**read_xpm3(const char *path)
{
	int i;
	char *str1;
	char *str2;
	char *str3;
	char **data;

	if (path == NULL || (i = open(path, O_RDONLY | O_BINARY)) == -1)
		return (NULL);
	str1 = ft_readfile(i);
	close(i);
	if (str1 == NULL)
		return (NULL);
	str2 = remove_c_commentaries(str1);
	free(str1);
	str1 = ft_strchr(str2, '{') + 1;
	*ft_strchr(str1, '}') = 0;
	i = ft_strcntc(str1, '\"');
	if (i % 2 || (data = (char **)malloc(sizeof(char *) * (1 + i / 2))) == NULL)
	{
		free(str2);
		return (NULL);
	}
	i = 0;
	while (ft_strchr(str1, '\"') && (str3 = ft_strchr(str1, '\"') + 1))
	{
		if (ft_strchr(str3, '\"'))
		{
			data[i] = ft_strndup(str3, (int)(ft_strchr(str3, '\"') - str3 + 1));
			if (ft_strchr(str3, '\"'))
				str1 = ft_strchr(str3, '\"') + 1;
		}
		++i;
	}
	data[i] = 0;
	free(str2);
	return (data);
}
