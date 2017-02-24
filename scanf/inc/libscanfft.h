/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libscanfft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:35:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/05 15:41:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSCANFFT_H
# define LIBSCANFFT_H

# include <libft.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_vsscanf(const char *str, const char *format, va_list ap);
int	ft_sscanf(const char *str, const char *format, ...);

int	ft_vfscanf(FILE *stream, const char *format, va_list ap);
int	ft_fscanf(FILE *stream, const char *format, ...);

int	ft_vdscanf(const int fd, const char *format, va_list ap);
int	ft_dscanf(const int fd, const char *format, ...);

int	ft_vscanf(const char *format, va_list ap);
int	ft_scanf(const char *format, ...);

#endif
