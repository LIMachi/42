/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:16:45 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/05 18:07:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	out;
	int	i;

	if (nb > 12)
		return (0);
	if (nb < 0)
		return (0);
	out = 1;
	i = 1;
	while (i++ < nb)
		out *= i;
	return (out);
}
