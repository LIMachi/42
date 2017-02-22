/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:48:43 by cchaumar          #+#    #+#             */
/*   Updated: 2016/03/07 23:14:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		sf_out(char *s)
{
	ft_putstr(s);
	exit(0);
}

static int		sf_root(int n)
{
	int		k;

	k = 0;
	while (k * k < n)
		k++;
	return (k);
}

static int		sf_outsider(char *s)
{
	int		n;
	int		i;

	i = 0;
	if (s[4] != LINE)
		return (-1);
	n = 0;
	while (i < 4)
	{
		n += (s[i] == BLOC) ? 1 : 0;
		if (s[i] != BLOC && s[i] != EMPT)
			return (-1);
		i++;
	}
	return (n);
}

static int		sf_get_tet_nbr(int fd, int n_tet, int count, int lines)
{
	char	s[6];
	int		n;
	char	c;

	s[5] = '\0';
	while (read(fd, s, 5) == 5)
	{
		if ((n = sf_outsider(s)) == -1)
			return (-1);
		count += n;
		lines++;
		if (lines == 4)
		{
			n_tet++;
			if ((count = (count == 4) ? 0 : -1) == -1)
				return (-1);
			if (read(fd, &c, 1) == 0)
				return (n_tet);
			if (c != '\n')
				return (-1);
			lines = 0;
		}
		ft_memset(s, '\0', 5);
	}
	return (-1);
}

int				main(int ac, char **av)
{
	int		fd;
	int		n;

	if (ac != 2)
		sf_out(USE);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		sf_out(ERR);
	n = sf_get_tet_nbr(fd, 0, 0, 0);
	close(fd);
	if (n == -1 || n > 26 || (fd = open(av[1], O_RDONLY)) == -1)
		sf_out(ERR);
	solve(fd, sf_root(n * 4), n);
	return (0);
}
