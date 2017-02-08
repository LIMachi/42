/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <hmarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2017/02/08 18:26:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <wchar.h>

# define BUFF_SIZE 1024
# define SHARP (1)
# define ZERO (1 << 1)
# define LESS (1 << 2)
# define MORE (1 << 3)
# define SPACE (1 << 4)

typedef	struct	s_penv
{
	char	flag;
	char	modif;
	int		pressi;
	int		field;
	char	buffer[BUFF_SIZE];
	int		pos;
	int		ret;
	int		err;
}				t_penv;

void			push_buff(char c, t_penv *env);
int				prf_conv(char *format, int i, t_penv *env, va_list ap);
int				char_chr(char c, char *chr);
void			prf_conv_mod(t_penv *env, va_list ap);
int				ft_printf(const char *format, ...);
int				prf_flag(char *form, int i, t_penv *env);
void			prf_flag_sharp(t_penv *env);
void			prf_flag_zero(t_penv *env);
void			prf_flag_less(t_penv *env);
void			prf_flag_more(t_penv *env);
void			prf_flag_space(t_penv *env);
int				prf_pressi(char *form, int i, t_penv *env);
int				prf_field(char *form, int i, t_penv *env);
int				prf_modif(char *form, int i, t_penv *env);
void			prf_init(t_penv *env);
void			prf_loop(t_penv *env);
unsigned long	prf_u_arg(va_list ap, t_penv env);
long			prf_arg(va_list ap, t_penv env);
void			prf_con_s(t_penv *env, va_list ap);
void			prf_con_ls(t_penv *env, va_list ap);
void			prf_con_p(t_penv *env, va_list ap);
void			prf_con_ld(t_penv *env, va_list ap);
void			prf_con_id(t_penv *env, va_list ap);
void			prf_con_o(t_penv *env, va_list ap);
void			prf_con_lo(t_penv *env, va_list ap);
void			prf_con_u(t_penv *env, va_list ap);
void			prf_con_lu(t_penv *env, va_list ap);
void			prf_con_x(t_penv *env, va_list ap);
void			prf_con_lx(t_penv *env, va_list ap);
void			prf_con_c(t_penv *env, va_list ap);
void			prf_con_lc(t_penv *env, va_list ap);
void			prf_con_m(t_penv *env, va_list ap);
void			prf_con_b(t_penv *env, va_list ap);
int				prf_itoa_bin(unsigned long nb, t_penv *env, int index);
void			prf_print_mem(t_penv *env, unsigned char *mem, int len);
void			prf_mod_int(t_penv *env, unsigned char *mem, int i, int len);
void			prf_itoa(long nb, t_penv *env);
int				nb_len(long nb);
void			prf_pos_pressi(t_penv *env, int len);
void			aply_signe(long nb, t_penv *env);
void			prf_pos_field(t_penv *env, int len);
void			prf_itoa_b(unsigned long nb, t_penv *env, int b, int maj);
int				nb_len_b(unsigned long nb, int b);
void			aply_sharp(t_penv *env, int conv);
int				prf_strlen(char *str);
int				push_uni(wchar_t c, t_penv *env, int nbbi);
int				prf_strlen_uni(wchar_t *str);
int				prf_main_b(char *form, t_penv *env, int i, va_list ap);
void			return_null(t_penv *env);
void			ft_void(long long voidable_content);

#endif
