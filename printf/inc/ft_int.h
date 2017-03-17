/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:28:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/17 03:07:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INT_H
# define FT_INT_H

# define FT_INT_USE_LOGICAL 1

# ifndef __SIZEOF_CHAR__
#  if FT_INT_USE_LOGICAL
#   define __SIZEOF_CHAR__ 1
#  else
#   define __SIZEOF_CHAR__ (sizeof(char))
#  endif
# endif

# ifndef __CHAR_BIT__
#  if FT_INT_USE_LOGICAL
#  	define __CHAR_BIT__ 0xFF
#  else
#   define __CHAR_BIT__ ((1 << (__SIZEOF_CHAR__ << 3)) - 1)
#  endif
# endif

# ifndef __SIZEOF_INTMAX_T__
#  if FT_INT_USE_LOGICAL
#   define __SIZEOF_INTMAX_T__ __SIZEOF_LONG_LONG__
#  else
#   define __SIZEOF_INTMAX_T__ (sizeof(__INTMAX_TYPE__))
#  endif
# endif

# define TSHORT_BIT	((__SHRT_MAX__ << 1) | 1)
# define TINT_BIT	((__INT_MAX__ << 1) | 1)
# define TLONG_BIT	((__LONG_MAX__ << 1) | 1)
# define TLLONG_BIT	((__LONG_LONG_MAX__ << 1) | 1)
# define TINTMAX_BIT ((__INTMAX_MAX__ << 1) | 1)
# define TSIZE_BIT __SIZE_MAX__
# define TPTRDIFF_BIT ((__PTRDIFF_MAX__ << 1) | 1)

typedef union	u_i128
{
	__UINT64_TYPE__	u64[2];
	__int128_t		i128;
	__uint128_t		u128;
}				t_i128;

#endif
