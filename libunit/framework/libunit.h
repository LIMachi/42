/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:12:06 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 08:18:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

/*
** stdlib.h:
** 		void * malloc(size_t size);
** 		void free(void *ptr);
** 		void exit(int status);
*/

#include <stdlib.h>

/*
** unistd.h:
** 		ssize_t write(int fildes, const void *buf, size_t nbyte);
** 		pid_t fork(void);
*/

#include <unistd.h>

/*
** sys/wait.h:
** 		pid_t wait(int *stat_loc);
** 		man 2 wait macros
*/

#include <sys/wait.h>

/*
** signal.h:
** 		man 3 signal macros
*/

#include <signal.h>

typedef struct			s_unit_test
{
	char				*name;
	int					(*test_func)(void);
	struct s_unit_test	*next;
}						t_unit_test;

void					load_test(t_unit_test **list, char* name,
									int (*test_func)(void));
int						launch_test(t_unit_test **list);

#endif
