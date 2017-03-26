/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 14:04:55 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/21 16:02:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftthread.h>
#include <libft.h>
#include <stdio.h>

void	*thread_function(void *data)
{
	pthread_t id = pthread_self();
	printf("thread id: %ld\n", (long)data);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	int				r;
	void			*thread_return[2];
	pthread_t		thread_id[2];
	pthread_attr_t	attributes[2];
	if (r = pthread_attr_init(&attributes[0]))
		ft_error(r, "Pthread error: ");
	if (r = pthread_attr_init(&attributes[1]))
		ft_error(r, "Pthread error: ");
	if (r = pthread_create(&thread_id[0], &attributes[0], &thread_function, NULL))
		ft_error(r, "Pthread error: ");
	if (r = pthread_create(&thread_id[1], &attributes[1], &thread_function, (void*)1l))
		ft_error(r, "Pthread error: ");
	if (r = pthread_attr_destroy(&attributes[0]))
		ft_error(r, "Pthread error: ");
	if (r = pthread_attr_destroy(&attributes[1]))
		ft_error(r, "Pthread error: ");
	if (r = pthread_join(thread_id[0], &thread_return[0]))
		ft_error(r, "Pthread error: ");
	if (r = pthread_join(thread_id[1], &thread_return[1]))
		ft_error(r, "Pthread error: ");
	return (0);
}
