/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:37:17 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/18 14:01:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** set of defines and types used in dtoa*, *printf and advanced float usages.
** Seting __T_FLOAT_SIZE to 4 or 8 will change the size of the t_float
*/

#ifndef FT_FLOAT_H
# define FT_FLOAT_H

# ifndef __T_FLOAT_SIZE
#  define __T_FLOAT_SIZE 8
# endif

# if __T_FLOAT_SIZE == 8

#  if __SIZEOF_DOUBLE__ == 8
#   define __T_FLOAT double
#  elif __SIZEOF_FLOAT__ == 8
#   define __T_FLOAT float
#  elif __SIZEOF_LONG_DOUBLE__ == 8
#   define __T_FLOAT long double
#  else
#   error "no valid 8 bytes floating precision container found"
#  endif

#  define __T_FLOAT_EXP_SIZE 11
#  define __T_FLOAT_MANT_SIZE 52
#  define __T_FLOAT_UI __UINT64_TYPE__
#  define __T_FLOAT_I __INT64_TYPE__
#  define __T_FLOAT_BSIZE 64

# elif __T_FLOAT_SIZE == 4

#  if __SIZEOF_DOUBLE__ == 4
#   define __T_FLOAT double
#  elif __SIZEOF_FLOAT__ == 4
#   define __T_FLOAT float
#  elif __SIZEOF_LONG_DOUBLE__ == 4
#   define __T_FLOAT long double
#  else
#   error "no valid 4 bytes floating precision container found"
#  endif

#  define __T_FLOAT_EXP_SIZE 8
#  define __T_FLOAT_MANT_SIZE 23
#  define __T_FLOAT_UI __UINT32_TYPE__
#  define __T_FLOAT_I __INT32_TYPE__
#  define __T_FLOAT_BSIZE 32

# else
#  error "invalid __T_FLOAT_SIZE value"
# endif

# define __T_FLOAT_EXP_BIAS ((((__T_FLOAT_I)1) << (__T_FLOAT_EXP_SIZE - 1)) - 1)
# define __T_FLOAT_MANT_COMP (((__T_FLOAT_UI)1) << __T_FLOAT_MANT_SIZE)

typedef struct	s_float_big_ieee_754
{
	__T_FLOAT_UI	sign : 1;
	__T_FLOAT_UI	exp : __T_FLOAT_EXP_SIZE;
	__T_FLOAT_UI	mant : __T_FLOAT_MANT_SIZE;
}				t_float_big_ieee_754;

typedef struct	s_float_little_ieee_754
{
	__T_FLOAT_UI	mant : __T_FLOAT_MANT_SIZE;
	__T_FLOAT_UI	exp : __T_FLOAT_EXP_SIZE;
	__T_FLOAT_UI	sign : 1;
}				t_float_little_ieee_754;

# if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define __T_FLOAT_IEEE_754 t_float_little_ieee_754
# else
#  define __T_FLOAT_IEEE_754 t_float_big_ieee_754
# endif

typedef union	u_float
{
	__T_FLOAT			f;
	__T_FLOAT_IEEE_754	part;
}				t_float;

# define __INFINITY_EXP ((1 << __T_FLOAT_EXP_SIZE) - 1)
# define INFINITY (((t_float){.part.exp = __INFINITY_EXP, .part.mant = 0}).f)

#endif
