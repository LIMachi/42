/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:27:04 by lee               #+#    #+#             */
/*   Updated: 2017/02/26 09:00:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <locale.h>

# include <ft_float.h>
# include <libft.h>

# define PRINTF_BUFFER_SIZE 1024

# define PT_PERCENT		0
# define PT_D			1
# define PT_I			2
# define PT_O			4
# define PT_U			8
# define PT_X			16
# define PT_E			32
# define PT_F			64
# define PT_G			128
# define PT_A			256
# define PT_C			512
# define PT_S			1024
# define PT_P			2048
# define PT_N			4096
# define PT_M			8192
# define PT_B			16384

# define PT_AC			(PT_O | PT_X | PT_B)
# define PT_AD			(PT_D | PT_I | PT_O | PT_U | PT_X | PT_B)
# define PT_AF			(PT_A | PT_E | PT_F | PT_G)
# define PT_CS			(PT_C | PT_S)
# define PT_NP			(PT_PERCENT | PT_N)
# define PT_NA			(PT_PERCENT | PT_M)

# define PTL_INT		0
# define PTL_SHORT		1
# define PTL_LONG		2
# define PTL_LONGD		4
# define PTL_INTMAX		8
# define PTL_SSIZE		16
# define PTL_PTRDIFF	32
# define PTL_INT128		64
# define PTL_CHAR		128
# define PTL_LONGL		256

# define PA_HASH		1
# define PA_ZERO		2
# define PA_MINUS		4
# define PA_SPACE		8
# define PA_PLUS		16
# define PA_AQ			32
# define PA_I			64
# define PA_MAJ			128

typedef union	u_i128
{
	__int128_t		i128;
	__uint128_t		u128;
	__UINT64_TYPE__	u64[2];
}				t_i128;

typedef union	u_printf_arg
{
	__uint128_t		ui;
	__int128_t		i;
	__T_FLOAT		f;
	void			*p;
}				t_printf_arg;

typedef struct	s_printf_form
{
	int				attr;
	char			valid : 1;
	char			ind_field : 1;
	char			ind_precision : 1;
	char			ind_array : 1;
	char			padding : (__CHAR_BIT__ - 4);
	int				field;
	int				precision;
	int				tlength;
	int				type;
	int				array;
	t_printf_arg	arg;
}				t_printf_form;

typedef struct	s_printf_put_arg
{
	t_printf_form	*forms;
	size_t			size;
	const char		*format;
	size_t			pos;
}				t_printf_put_arg;

typedef union	u_fss
{
	int			fd;
	char		*str;
	FILE		*stream;
}				t_fss;

typedef struct	s_printf_data
{
	size_t		max_len;
	size_t		len;
	size_t		buffer_size;
	size_t		buffer_pos;
	char		buffer[PRINTF_BUFFER_SIZE];
	t_fss		fss;
	void		(*buffer_dumper)(t_fss, char *, size_t, size_t);
}				t_printf_data;

void			debug_printf_forms(t_printf_form *forms);

int				ft_asnprintf(char **strn, size_t size, const char *format, ...);
int				ft_asprintf(char **strn, const char *format, ...);
int				ft_dnprintf(int fd, size_t size, const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_fnprintf(FILE *stream, size_t size, const char *format, ...);
int				ft_fprintf(FILE *stream, const char *format, ...);
int				ft_printf(const char *format, ...);
int				ft_snprintf(char *str, size_t size, const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);

int				ft_vasnprintf(char **strn, size_t size, const char *format,
							va_list ap);
int				ft_vasprintf(char **strn, const char *format, va_list ap);
int				ft_vdnprintf(int fd, size_t size, const char *format,
							va_list ap);
int				ft_vdprintf(int fd, const char *format, va_list ap);
int				ft_vfnprintf(FILE *stream, size_t size, const char *format,
							va_list ap);
int				ft_vfprintf(FILE *stream, const char *format, va_list ap);
int				ft_vprintf(const char *format, va_list ap);
int				ft_vsnprintf(char *str, size_t size, const char *format,
							va_list ap);
int				ft_vsprintf(char *str, const char *format, va_list ap);

char			*thousands_sep(void);
int				parse_number(const char *format, int *number, int *arg_number,
							int *pos);
int				parse_args(t_printf_form *forms, va_list ap, int argn);
void			bufferize_char(t_printf_data *data, char c);

t_printf_form	*parse_forms(const char *format, int *argn);
int				parse_args(t_printf_form *forms, va_list ap, int argn);
int				dn_put_arg(t_printf_put_arg *parg, int formn, size_t len,
							int fd);

#endif
