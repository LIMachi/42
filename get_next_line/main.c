/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:36:24 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 17:22:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stdlib for malloc and free
*/

#include <stdlib.h>

/*
** get_next_line.h for get_next_line
*/

#include "get_next_line.h"

/*
** unistd.h for close, write and read
*/

#include <unistd.h>

/*
** fcntl.h for open
*/

#include <fcntl.h>

/*
** string.h for strlen
*/

#include <string.h>
#include <stdio.h>

char	*ft_strndup(const char *s, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_stracat(char *str1, char *str2);

//*
int	main(int argc, char **argv)
{
	char	*buff;
	int		fd;
	int		r;

	if (argc != 2)
	{
		write(1, argv[0], strlen(argv[0]));
		write(1, " <filepath>\n", 12);
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		write(1, "Invalid fd\n", 11);
		return (-1);
	}
	buff = NULL;
	while ((r = get_next_line(fd, &buff)) > 0)
	{
		printf("r: %d\tstr: '%s'\n", r, buff);
		free(buff);
		buff = NULL;
	}
	close(fd);
}
//*/
/*
int	main(void)
{
	printf("%p\n", ft_strchr("test", '/n'));
}
//*/
