/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:09:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putlist(t_list **sl)
{
	int		i;
	t_list	*current;

	if (sl != NULL)
	{
		current = *sl;
		i = -1;
		while (current != NULL && current->next != *sl && !(0 * ++i))
		{
			ft_putnbr(i);
			ft_putstr("\ncontent_size : ");
			ft_putnbr(current->content_size);
			ft_putstr("\ncontent : ");
			if (current->content_size == 0 || current->data == NULL)
				ft_putstr("(NULL)");
			else
				write(1, current->data, current->content_size);
			ft_putstr("\n\n");
			current = current->next;
		}
		if (current == NULL)
			ft_putstr("\nEnd of list (NULL)\n");
		else
			ft_putstr("\nEnd of list (Cycle)\n");
	}
}
