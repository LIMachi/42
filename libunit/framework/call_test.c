/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:52:17 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 15:56:36 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

static void	sf_print_signals(int state)
{
	if (WTERMSIG(state) == SIGBUS)
		write(1, "[BUS]", 5);
	else if (WTERMSIG(state) == SIGSEGV)
		write(1, "[SEGV]", 6);
	else if (WTERMSIG(state) == SIGABRT)
		write(1, "[ABRT]", 6);
	else if (WTERMSIG(state) == SIGALRM)
		write(1, "[TIMEOUT]", 9);
	else
		write(1, "[SIGNAL]", 8);
}

int			call_test(int (*test_func)(void), int expected_status)
{
	int		out;
	int		state;

	out = 1;
	if (fork() == 0)
	{
		alarm(10);
		exit(test_func());
	}
	else
	{
		wait(&state);
		write(1, (out = !(state == expected_status)) ? TF_RED : TF_GREEN, 5);
		if (WIFSIGNALED(state))
			sf_print_signals(state);
		else if (WIFEXITED(state))
			write(1, out ? "[KO]" : "[OK]", 4);
		else
			write(1, "[STOPED]", 8);
		write(1, TF_RESET, 5);
	}
	return (out);
}
