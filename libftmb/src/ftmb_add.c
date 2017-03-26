/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmb_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 10:58:51 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/24 11:01:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmb.h>

t_nbyte_int	ftmb_add_8(const t_nbyte_int *a, const t_nbyte_int *b)
{
	t_nbyte_int	o;
	uint8_t		tmp;
	uint8_t		carry;

	carry = 0;
	o = NBYTE_ZERO;
	while ((o.size < a->size || o.size < b->size) && o.size < NBYTE_MAX_SIZE)
	{
		if (carry)
		{
			if ((tmp = a->data.u8[o.size] + carry) > a->data.u8[o.size])
				carry = 0;
			if ((o.data.u8[o.size] = tmp + b->data.u8[o.size])
					< b->data.u8[o.size] && o.data.u8[o.size] < tmp)
				carry = 1;
		}
		else if ((o.data.u8[o.size] = a->data.u8[o.size] +
					b->data.u8[o.size]) < a->data.u8[o.size] &&
					o.data.u8[o.size] < b->data.u8[o.size])
			carry = 1;
		++o.size;
	}
	if (carry && ++o.size <= NBYTE_MAX_SIZE)
		o.data.u8[o.size - 1] = carry;
	return (o);
}

t_nbyte_int	ftmb_add_16(const t_nbyte_int *a, const t_nbyte_int *b)
{
	t_nbyte_int	o;
	uint8_t		tmp;
	uint8_t		carry;

	carry = 0;
	o = NBYTE_ZERO;
	while ((o.size < a->size || o.size < b->size) && o.size < NBYTE_MAX_SIZE)
	{
		if (carry)
		{
			if ((tmp = a->data.u8[o.size] + carry) > a->data.u8[o.size])
				carry = 0;
			if ((o.data.u8[o.size] = tmp + b->data.u8[o.size])
					< b->data.u8[o.size] && o.data.u8[o.size] < tmp)
				carry = 1;
		}
		else if ((o.data.u8[o.size] = a->data.u8[o.size] +
					b->data.u8[o.size]) < a->data.u8[o.size] &&
					o.data.u8[o.size] < b->data.u8[o.size])
			carry = 1;
		++o.size;
	}
	if (carry && ++o.size <= NBYTE_MAX_SIZE)
		o.data.u8[o.size - 1] = carry;
	return (o);
}

t_nbyte_int	ftmb_add_32(const t_nbyte_int *a, const t_nbyte_int *b)
{
	t_nbyte_int	o;
	uint8_t		tmp;
	uint8_t		carry;

	carry = 0;
	o = NBYTE_ZERO;
	while ((o.size < a->size || o.size < b->size) && o.size < NBYTE_MAX_SIZE)
	{
		if (carry)
		{
			if ((tmp = a->data.u8[o.size] + carry) > a->data.u8[o.size])
				carry = 0;
			if ((o.data.u8[o.size] = tmp + b->data.u8[o.size])
					< b->data.u8[o.size] && o.data.u8[o.size] < tmp)
				carry = 1;
		}
		else if ((o.data.u8[o.size] = a->data.u8[o.size] +
					b->data.u8[o.size]) < a->data.u8[o.size] &&
					o.data.u8[o.size] < b->data.u8[o.size])
			carry = 1;
		++o.size;
	}
	if (carry && ++o.size <= NBYTE_MAX_SIZE)
		o.data.u8[o.size - 1] = carry;
	return (o);
}

t_nbyte_int	ftmb_add_64(const t_nbyte_int *a, const t_nbyte_int *b)
{
	t_nbyte_int	o;
	uint8_t		tmp;
	uint8_t		carry;

	carry = 0;
	o = NBYTE_ZERO;
	while ((o.size < a->size || o.size < b->size) && o.size < NBYTE_MAX_SIZE)
	{
		if (carry)
		{
			if ((tmp = a->data.u8[o.size] + carry) > a->data.u8[o.size])
				carry = 0;
			if ((o.data.u8[o.size] = tmp + b->data.u8[o.size])
					< b->data.u8[o.size] && o.data.u8[o.size] < tmp)
				carry = 1;
		}
		else if ((o.data.u8[o.size] = a->data.u8[o.size] +
					b->data.u8[o.size]) < a->data.u8[o.size] &&
					o.data.u8[o.size] < b->data.u8[o.size])
			carry = 1;
		++o.size;
	}
	if (carry && ++o.size <= NBYTE_MAX_SIZE)
		o.data.u8[o.size - 1] = carry;
	return (o);
}

t_nbyte_int	ftmb_add(const t_nbyte_int *a, const t_nbyte_int *b)
{
	(void)b;
	return (*a);
}
