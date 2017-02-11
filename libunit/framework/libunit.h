/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:12:06 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 15:52:59 by hmartzol         ###   ########.fr       */
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

#define TF_RED			"\033[31m"
#define TF_GREEN		"\033[32m"
#define TF_YELLOW		"\033[33m"
#define TF_CYAN			"\033[36m"
#define TF_LIGHT_GREEN	"\033[92m"
#define TF_LIGHT_RED	"\033[91m"
#define TF_LIGHT_YELLOW	"\033[93m"
#define TF_LIGHT_CYAN	"\033[96m"

#define TF_BOLD			"\033[1m"
#define TF_DIM			"\033[2m"
#define TF_UNDERLINE	"\033[3m"
#define TF_BLINK		"\033[4m"
#define TF_INVERT		"\033[5m"
#define TF_HIDEN		"\033[6m"

#define TF_RESET		"\033[0m"

typedef struct			s_unit_test
{
	char				*name;
	int					(*test_func)(void);
	struct s_unit_test	*next;
	int					expected_status;
}						t_unit_test;

int						create_signal_code(int sig, int ret);
int						call_test(int (*test_func)(void), int expected_status);
void					load_test(t_unit_test **list, char* name,
								int (*test_func)(void), int expected_status);
int						launch_test(t_unit_test **list);

#endif
