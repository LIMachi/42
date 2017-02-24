/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_fd_log.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 19:13:11 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 19:52:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <fcntl.h>

int	global_fd_log(void)
{
	static int	fd = -2;

	if (fd == -2)
		if ((fd = open(LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1 &&
	write(2, TF_YELLOW "log could not be oppened or created\n" TF_RESET, 46))
			exit(-1);
	return (fd);
}
