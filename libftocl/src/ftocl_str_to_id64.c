/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_str_to_id64.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:10:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/19 16:11:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** transform a 8 char string to a uint64_t id, all unset char will be set to \0,
** all extra chars after the 8 first will be discarded
** strict-aliasing compliant (dereferencing of buff delayed by out)
*/

uint64_t	ftocl_str_to_id64(char *str)
{
	char		buff[8];
	int			i;
	uint64_t	*out;

	i = 0;
	while (*str != '\0')
		buff[i++] = *str++;
	while (i < 8)
		buff[i++] = '\0';
	out = (uint64_t*)buff;
	return (*out);
}