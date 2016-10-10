/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlist_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 19:09:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putlist_fd(t_list **sl, int fd)
{
	int		i;
	t_list	*current;

	if (sl != NULL)
	{
		current = *sl;
		i = -1;
		while (current != NULL && current->next != *sl && !(0 * ++i))
		{
			ft_putnbr_fd(i, fd);
			ft_putstr_fd("\ncontent_size : ", fd);
			ft_putnbr_fd(current->content_size, fd);
			ft_putstr_fd("\ncontent : ", fd);
			if (current->content_size == 0 || current->content == NULL)
				ft_putstr_fd("(NULL)", fd);
			else
				write(fd, current->content, current->content_size);
			ft_putstr_fd("\n\n", fd);
			current = current->next;
		}
		if (current == NULL)
			ft_putstr_fd("\nEnd of list (NULL)\n", fd);
		else
			ft_putstr_fd("\nEnd of list (Cycle)\n", fd);
	}
}
