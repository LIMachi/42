/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_log.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 10:01:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		sf_reset(int *fd, char **str1, char **str2)
{
	if (fd != NULL)
	{
		if (*fd != -1)
			close(*fd);
		*fd = -1;
	}
	if (str1 != NULL)
	{
		if (*str1 != NULL)
			ft_free(*str1);
		*str1 = NULL;
	}
	if (str2 != NULL)
	{
		if (*str2 != NULL)
			ft_free(*str2);
		*str2 = NULL;
	}
	return (1);
}

char			*ft_global_log(int flag, char *data)
{
	static char	*path = NULL;
	static char	*log = NULL;
	static int	fd = -1;

	if ((*ft_global_flags() & GF_USE_LOG) != GF_USE_LOG)
		return (NULL);
	if ((flag & LOG_SET_PATH) && data != NULL)
	{
		if (sf_reset(&fd, &path, NULL) && (path = ft_strdup(data)) == NULL)
			return (NULL);
		return (path);
	}
	if ((flag & LOG_SET) && sf_reset(NULL, &log, NULL))
		if ((log = ft_strdup(data)) == NULL)
			return (NULL);
	if ((flag & LOG_PRINT) && log != NULL)
		write(1, log, ft_strlen(log));
	if ((flag & LOG_STORE) && log != NULL && (fd != -1 || path != NULL))
	{
		if (fd == -1 && (fd = open(path, O_WRONLY | O_CREAT | O_APPEND)) == -1)
			return (NULL);
		write(fd, log, ft_strlen(log));
	}
	(void)((flag == LOG_END) && sf_reset(&fd, &path, &log));
	return (log);
}