/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:52:46 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 08:39:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	to_fd(t_fss fss, char *buff, size_t size, size_t pos)
{
	(void)pos;
	write(fss.fd, buff, size);
}
