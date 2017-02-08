/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/07 00:59:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	sf_putdata(void *data, size_t size)
{
	char	*buff;

	ft_void(write(1, data, size));
	if ((*ft_global_flags() & GF_FORCE_LOG) == GF_FORCE_LOG)
	{
		buff = (char*)ft_malloc(size + 1);
		ft_memcpy(buff, data, size);
		buff[size] = '\0';
		ft_global_log(LOG_SET | LOG_STORE, buff);
		ft_free(buff);
	}
}

void		ft_putlist(t_list **sl)
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
				sf_putdata(current->data, current->content_size);
			ft_putstr("\n\n");
			current = current->next;
		}
		if (current == NULL)
			ft_putstr("\nEnd of list (NULL)\n");
		else
			ft_putstr("\nEnd of list (Cycle)\n");
	}
}
