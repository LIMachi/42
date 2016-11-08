/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:15:34 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 17:29:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stdlib for malloc and free
*/

#include <stdlib.h>

/*
** unistd for read
*/

#include <unistd.h>

/*
** get_next_line.h for BUFF_SIZE, FD_LIMIT, SSIZE_MAX and t_gnl
*/

#include "get_next_line.h"

#if defined(NORM_42) && (NORM_42 < 1)
size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		++len;
	return (len);
}
#else
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}
#endif

#if defined(NORM_42) && (NORM_42 < 1)
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if (s == NULL || c > 127 || c < -128)
		return (NULL);
	ptr = (char*)s;
	while (*ptr && *ptr != (char)c)
		++ptr;
	if (*ptr != (char)c)
		return (NULL);
	return (ptr);
}
#else
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char*)s;
	while (*ptr && *ptr != (char)c)
		++ptr;
	if (*ptr != (char)c)
		return (NULL);
	return (ptr);
}
#endif

#if defined(NORM_42) && (NORM_42 < 1)
char	*ft_strndup(const char *s, size_t n)
{
	char	*out;

	if (s == NULL)
		return (NULL);
	if ((out = (char*)malloc(++n * sizeof(char))) == NULL)
		return (NULL);
	out[--n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}
#else
char	*ft_strndup(const char *s, size_t n)
{
	char	*out;

	if ((out = (char*)malloc(++n * sizeof(char))) == NULL)
		return (NULL);
	out[--n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}
#endif

char	*ft_stracat(char *str1, char *str2)
{
	size_t	size;
	char	*out;
	char	*ptr;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str1 == NULL)
		return (ft_strndup(str2, ft_strlen(str2)));
	if (str2 == NULL)
		return (ft_strndup(str1, ft_strlen(str1)));
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	if ((out = (char*)malloc(size * sizeof(char))) == NULL)
		return (NULL);
	ptr = out;
	while (*str1)
		*ptr++ = *str1++;
	while (*str2)
		*ptr++ = *str2++;
	*ptr = '\0';
	return (out);
}

char	*ft_strpdup(const char *s, const char *e)
{
	char	*out;
	size_t	size;

	if (s == NULL || e == NULL || s > e)
		return (NULL);
	size = (size_t)(e - s);
	if ((out = (char*)malloc(++size * sizeof(char))) == NULL)
		return (NULL);
	out[--size] = '\0';
	while (size--)
		out[size] = s[size];
	return (out);
}

/*
** note: container should be a pointer to a pointer NULL who will be set by
** sf_read_until_char_occurence
** return -1 on error, 0 on direct EoF, and 1 on succes (even if EoF is reached)
*/

int	sf_read_until_char_occurence(const int fd, int c, char **container)
{
	char	buffer[BUFF_SIZE];
	int		r;
	char	*tmp;

	if (container == NULL || *container != NULL)
		return (-1/*| ft_error(EINVAL,
				"invalid container passed to sf_read_until_char_occurence ")*/);
	while ((r = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[r] = '\0';
		tmp = ft_stracat(*container, buffer);
		if (*container != NULL)
			free(*container);
		*container = tmp;
		if (ft_strchr(buffer, c))
			break ;
	}
	if (r == -1)
		return (-1/* | ft_error(0,
					"sf_read_until_char_occurence's call to read failed: ")*/);
	if (r == 0 && *container == NULL)
		return (0);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char		*tab[FD_LIMIT] = {0};
	char			*ptr0;
	char			*ptr1;
	int				r;

	if (fd < 0)
		return (-1/* | ft_error(ENOENT, "incorect fd passed to get_next_line")*/);
	if (fd >= FD_LIMIT)
		return (-1/* | ft_error(EBADF, "incorect fd passed to get_next_line")*/);
	if (line == NULL)
		return (-1/* | ft_error(EINVAL, "**line passed to get_next_line is NULL ")*/);
	if (*line != NULL)
		return (-1/* | ft_error(EINVAL, "*line passed to get_next_line is not NULL ")*/);
	if (!TEST_BUFF_SIZE)
		return (-1/* | ft_error(ENOMEM, "BUFF_SIZE passed to get_next_line too big ")*/);
	if (tab[fd] == NULL || ft_strchr(tab[fd], '\n') == NULL)
	{
		ptr0 = NULL;
		if ((r = sf_read_until_char_occurence(fd, '\n', &ptr0)) == -1)
			return (-1);
		if (r == 0 && tab[fd] == NULL)
			return (0);
		if ((ptr1 = ft_stracat(tab[fd], ptr0)) == NULL)
			return (-1);
		free(ptr0);
		if (tab[fd] != NULL)
			free(tab[fd]);
		tab[fd] = ptr1;
	}
	if ((ptr0 = ft_strchr(tab[fd], '\n')) == NULL)
	{
		if ((*line = ft_strndup(tab[fd], ft_strlen(tab[fd]))) == NULL)
			return (-1);
		free(tab[fd]);
		tab[fd] = NULL;
		return (1);
	}
	if ((*line = ft_strpdup(tab[fd], ptr0++)) == NULL)
		return (-1);
	if ((ptr1 = ft_strpdup(ptr0, ft_strchr(ptr0, '\0'))) == NULL)
		return (-1);
	free(tab[fd]);
	tab[fd] = ptr1;
	return (1);
}
