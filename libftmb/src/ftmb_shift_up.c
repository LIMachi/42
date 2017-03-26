/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmb_shift_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 11:01:58 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/24 11:11:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmb.h>

t_nbyte_int	ftmb_shift_up_8(const t_nbyte_int *v, size_t shift)
{
	t_nbyte_int	out;
	size_t		i;
	size_t		shift2;

	out = NBYTE_ZERO;
	out.size = shift >> 3;
	i = 0;
	shift &= 7;
	shift2 = 8 - shift;
	out.data.u8[out.size++] = v->data.u8[0] << shift;
	while (i < v->size)
		out.data.u8[out.size++] = (v->data.u8[i] >> shift2) |
						(v->data.u8[++i] << shift);
	return (out);
}

t_nbyte_int	ftmb_shift_up_16(const t_nbyte_int *v, size_t shift)
{
	t_nbyte_int	out;
	size_t		i;
	size_t		shift2;
	size_t		limit;

	out = NBYTE_ZERO;
	out.size = shift >> 4;
	i = 0;
	shift &= 15;
	shift2 = 16 - shift;
	out.data.u16[out.size++] = v->data.u16[0] << shift;
	limit = (v->size >> 1) + (v->size & 1);
	while (i < limit)
		out.data.u16[out.size++] = (v->data.u16[i] >> shift2) |
						(v->data.u16[++i] << shift);
	out.size <<= 1;
	return (out);
}

t_nbyte_int	ftmb_shift_up_32(const t_nbyte_int *v, size_t shift)
{
	t_nbyte_int	out;
	size_t		i;
	size_t		shift2;
	size_t		limit;

	out = NBYTE_ZERO;
	out.size = shift >> 5;
	i = 0;
	shift &= 31;
	shift2 = 32 - shift;
	out.data.u32[out.size++] = v->data.u32[0] << shift;
	limit = (v->size >> 2) + ((v->size & 3) != 0);
	while (i < limit)
		out.data.u32[out.size++] = (v->data.u32[i] >> shift2) |
						(v->data.u32[++i] << shift);
	out.size <<= 2;
	return (out);
}

t_nbyte_int	ftmb_shift_up_64(const t_nbyte_int *v, size_t shift)
{
	t_nbyte_int	out;
	size_t		i;
	size_t		shift2;
	size_t		limit;

	out = NBYTE_ZERO;
	out.size = shift >> 6;
	i = 0;
	shift &= 63;
	shift2 = 64 - shift;
	out.data.u64[out.size++] = v->data.u64[0] << shift;
	limit = (v->size >> 3) + ((v->size & 7) != 0);
	while (i < limit)
		out.data.u64[out.size++] = (v->data.u64[i] >> shift2) |
						(v->data.u64[++i] << shift);
	out.size <<= 3;
	return (out);
}

t_nbyte_int	ftmb_shift_up(const t_nbyte_int *v, size_t shift)
{
	(void)shift;
	return (*v);
}
