/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:32:11 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/05 15:06:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		ft_strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

void	ft_putline(char *str)
{
	while (*str)
		ft_putchar(*str++);
	ft_putchar('\n');
}

void	ft_str_swap(char **s1, char **s2)
{
	char	*str;

	str = *s1;
	*s1 = *s2;
	*s2 = str;
}

void	ft_str_sort(int str_cnt, char **p_str)
{
	int	state;
	int i;

	state = 1;
	while (state && !(state = 0))
	{
		i = 0;
		while (++i < str_cnt)
			if (ft_strcmp(p_str[i - 1], p_str[i]) > 0 && (state = 1))
				ft_str_swap(&p_str[i - 1], &p_str[i]);
	}
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	ft_str_sort(--argc, ++argv);
	while (argc--)
		ft_putline(*argv++);
}
