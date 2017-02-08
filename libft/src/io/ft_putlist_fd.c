/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlist_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/07 00:58:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	sf_putdata(int fd, void *data, size_t size)
{
	char	*buff;

	ft_void(write(fd, data, size));
	if ((*ft_global_flags() & GF_FORCE_LOG) == GF_FORCE_LOG)
	{
		buff = (char*)ft_malloc(size + 1);
		ft_memcpy(buff, data, size);
		buff[size] = '\0';
		ft_global_log(LOG_SET | LOG_STORE, buff);
		ft_free(buff);
	}
}

void		ft_putlist_fd(t_list **sl, int fd)
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
			if (current->content_size == 0 || current->data == NULL)
				ft_putstr_fd("(NULL)", fd);
			else
				sf_putdata(fd, current->data, current->content_size);
			ft_putstr_fd("\n\n", fd);
			current = current->next;
		}
		if (current == NULL)
			ft_putstr_fd("\nEnd of list (NULL)\n", fd);
		else
			ft_putstr_fd("\nEnd of list (Cycle)\n", fd);
	}
}
