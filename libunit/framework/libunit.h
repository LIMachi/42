/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:12:06 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 19:54:25 by hmartzol         ###   ########.fr       */
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

# include <stdlib.h>

/*
** unistd.h:
** 		ssize_t write(int fildes, const void *buf, size_t nbyte);
** 		pid_t fork(void);
*/

# include <unistd.h>

/*
** sys/wait.h:
** 		pid_t wait(int *stat_loc);
** 		man 2 wait macros
*/

# include <sys/wait.h>

/*
** signal.h:
** 		man 3 signal macros
*/

# include <signal.h>

# define LOG_PATH			"./log.txt"
# define TEST_STDOUT_PATH	"./test_stdout.txt"

# define TF_RED				"\033[31m"
# define TF_GREEN			"\033[32m"
# define TF_YELLOW			"\033[33m"
# define TF_LIGHT_CYAN		"\033[96m"

# define TF_RESET			"\033[0m"

typedef struct				s_unit_test
{
	char				*name;
	int					(*test_func)(void);
	struct s_unit_test	*next;
	int					expected_status;
}							t_unit_test;

int							global_fd_log(void);

int							create_signal_code(int sig, int ret);
int							call_test(int (*test_func)(void),
										int expected_status);
void						load_test(t_unit_test **list, char *name,
								int (*test_func)(void), int expected_status);
int							launch_test(t_unit_test **list);

int							print_red(int fd_out, char *str,
										unsigned long size);
int							print_green(int fd_out, char *str,
											unsigned long size);
int							print_cyan(int fd_out, char *str,
											unsigned long size);
int							print_yellow(int fd_out, char *str,
											unsigned long size);
int							print(int fd_out, char *str,
									unsigned long size);

#endif
