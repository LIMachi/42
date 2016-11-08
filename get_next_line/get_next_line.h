/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:19:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 16:16:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** if NORM_42 is not set, asume that the norm is aplied, if NORM_42 is set to
** a value under 1, then activate potential non-autorized code
*/

#if defined(NORM_42) && (NORM_42 < 1)
# include <limits.h>
#endif

#define BUFF_SIZE 80

int 				get_next_line(const int fd, char **line);

/*
** A FD_LIMIT (or other name) can be found in some headers/librairies that set
** a hard limit of FDs per terminal, usually around 12288 in unix like systems.
** A SSIZE_MAX can also be found in some headers/librairies that set a hard
** limit to the maximum of Bytes that can be read in a single call of function
** read, usually around 9223372036854775807L in posix-1. But because READ_MAX
** shouldn't be bigger than the RAM available, i set the hard limit to a
** maximum of 4GB (32-bit hard limit for the ram).
*/

/*
** if FD_LIMIT wasn't set by a header or library, use the default 12288 value
*/

#ifndef FD_LIMIT
# define FD_LIMIT 12288
#endif

/*
** if READ_MAX is unset or too big, set it:
** if SSIZE_MAX is unset or too big, use the default 4294967295UL instead of
** SSIZE_MAX to set READ_MAX
*/

#if !(defined (READ_MAX) && (READ_MAX <= (4294967296ULL)))
# ifdef READ_MAX
#  undef READ_MAX
# endif
# if defined(SSIZE_MAX) && (SSIZE_MAX <= (4294967296ULL))
#  define READ_MAX SSIZE_MAX
# else
#  define READ_MAX (4294967295UL)
# endif
#endif

#define TEST_BUFF_SIZE (BUFF_SIZE <= READ_MAX)
