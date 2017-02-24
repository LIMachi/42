/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:52:17 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 20:02:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdio.h>
#include <fcntl.h>

static void	sf_print_signals(int state)
{
	if (WTERMSIG(state) == SIGBUS)
		print(1, "[BUS]", 5);
	else if (WTERMSIG(state) == SIGSEGV)
		print(1, "[SEGV]", 6);
	else if (WTERMSIG(state) == SIGABRT)
		print(1, "[ABRT]", 6);
	else if (WTERMSIG(state) == SIGALRM)
		print(1, "[TIMEOUT]", 9);
	else
		print(1, "[SIGNAL]", 8);
}

static void	sf_shild(int (*test_func)(void))
{
	int		test_stdout;

	alarm(10);
	if ((test_stdout = open(TEST_STDOUT_PATH, O_RDWR | O_CREAT | O_TRUNC,
			0755)) == -1 && write(2, "shild's call to open returned -1\n", 33))
		exit(-1);
	if ((dup2(test_stdout, 1)) == -1 &&
			print_yellow(2, "shild's call to dup returned -1\n", 32))
		exit(-1);
	close(test_stdout);
	exit(test_func());
}

int			call_test(int (*test_func)(void), int expected_status)
{
	int		out;
	int		state;

	out = 1;
	if (fork() == 0)
		sf_shild(test_func);
	else
	{
		wait(&state);
		write(1, (out = !(state == expected_status)) ? TF_RED : TF_GREEN, 5);
		if (WIFSIGNALED(state))
			sf_print_signals(state);
		else if (WIFEXITED(state))
			print(1, WEXITSTATUS(state) ? "[KO]" : "[OK]", 4);
		else
			print(1, "[STOPED]", 8);
		write(1, TF_RESET, 5);
	}
	return (out);
}
