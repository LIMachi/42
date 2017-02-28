/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_stream.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:52:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 08:56:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	to_stream(t_fss fss, char *buff, size_t size, size_t pos)
{
	(void)pos;
	fwrite(buff, sizeof(char), size, fss.stream);
}
