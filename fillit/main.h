/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 13:03:57 by cchaumar          #+#    #+#             */
/*   Updated: 2016/03/07 23:14:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <libft.h>
# define USE		"usage: fillit source_file\n"
# define ERR		"error\n"
# define BLOC		'#'
# define EMPT		'.'
# define LINE		'\n'
# define LMASK		(unsigned long long)0x8000800080008000

typedef struct				s_tet
{
	unsigned long long		blocs;
	t_point					pos;
	struct s_tet			*ident;
	unsigned char			xmax;
	unsigned char			ymax;
}							t_tet;

void						solve(int fd, int size, int n);

#endif
