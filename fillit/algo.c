/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 15:50:20 by cchaumar          #+#    #+#             */
/*   Updated: 2016/03/07 23:14:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		sf_print_result(int size, t_tet tets[27])
{
	int		i;
	char	tab[17][17];
	t_point	p;

	i = -1;
	while (++i < size)
		ft_memset((void*)tab[i], EMPT, (sizeof(char) * (size_t)size));
	i = 'A' - 1;
	while (tets->blocs && (p.y = -1) && ++i)
	{
		while (++p.y < 4 && (p.x = -1))
			while (++p.x < 4)
				if (tets->blocs & (((unsigned long long)1) <<
					(63 - p.x - (p.y << 4))))
					tab[3 - p.y + tets->pos.y][p.x + tets->pos.x] = (char)i;
		++tets;
	}
	i = 0;
	while (i < size && !(tab[i][size] = 0))
		ft_putendl(tab[i++]);
}

static int		sf_check(unsigned long long piece)
{
	static unsigned long long	pieces[19] = {0xc000c000, 0xf000,
		0x8000800080008000, 0xc0006000, 0x6000c000, 0x8000c0004000,
		0x4000c0008000, 0xe0004000, 0x8000c0008000, 0x4000e000,
		0x4000c0004000, 0x8000e000, 0x2000e000, 0x80008000c000,
		0x40004000c000, 0xe0008000, 0xe0002000, 0xc00080008000,
		0xc00040004000};
	int							i;

	i = -1;
	while (++i < 19)
		if (pieces[i] == piece)
			return (1);
	return (0);
}

static int		sf_tets(int fd, t_tet *tet, t_point p, t_point deg)
{
	while ((deg.y = (int)read(fd, &deg.x, 1)) > 0)
	{
		tet->blocs |= (unsigned long long)(deg.x == BLOC) <<
			(63 - ((3 - p.y) << 4) - p.x);
		if ((p.x += (deg.x != LINE)) == 4)
			p = ft_point(0, p.y + 1);
		if (deg.x == LINE && p.y == 4)
		{
			p = ft_point(-1, -1);
			while (++p.x < 4 && (tet->blocs >>= (!(tet->blocs & 0xFFFF) << 4)))
				tet->blocs <<= !(tet->blocs & LMASK);
			while (++p.y < 4 && (tet->ymax += (tet->ymax < 3 && tet->blocs &
				((unsigned long long)0xF000 << ((tet->ymax + 1) << 4)))))
				tet->xmax += (tet->xmax < 3 && tet->blocs &
					(LMASK >> (tet->xmax + 1)));
			if (tet->blocs == 0xF000)
				tet->xmax = 3;
			p = ft_point(0, 0);
			if (!sf_check(tet->blocs))
				return (-1);
			++tet;
		}
	}
	return (deg.y);
}

static int		sf_rec(unsigned short map[16], t_tet *tet, int size)
{
	if (tet->blocs == 0)
		return (0);
	tet->pos = (tet->ident) ?
		ft_point(tet->ident->pos.x, tet->ident->pos.y - 1) : ft_point(-1, -1);
	while (tet->ymax + (++tet->pos.y) < size)
	{
		while (tet->xmax + (++tet->pos.x) < size)
		{
			if (!(*((unsigned long long*)(map + tet->pos.y)) &
				(tet->blocs >> tet->pos.x)))
			{
				*((unsigned long long*)(map + tet->pos.y)) ^=
					tet->blocs >> tet->pos.x;
				if (!sf_rec(map, tet + 1, size))
					return (0);
				*((unsigned long long*)(map + tet->pos.y)) ^=
					tet->blocs >> tet->pos.x;
			}
		}
		tet->pos.x = -1;
	}
	return (-1);
}

void			solve(int fd, int size, int n)
{
	t_tet			tets[27];
	unsigned short	map[16];
	t_point			i;

	ft_bzero((void *)tets, (size_t)(27 * sizeof(t_tet)));
	ft_bzero((void *)map, (size_t)(16 * sizeof(unsigned short)));
	if (!sf_tets(fd, tets, ft_point(0, 0), ft_point(0, 0)))
	{
		i.x = -1;
		while (++i.x < n && (i.y = -1))
			while (++i.y < i.x)
				if ((tets + i.x)->blocs == (tets + i.y)->blocs)
					(tets + i.x)->ident = tets + i.y;
		while (sf_rec(map, tets, size) == -1)
			size++;
		sf_print_result(size, tets);
	}
	else
	{
		ft_putstr(ERR);
		exit(0);
	}
}
