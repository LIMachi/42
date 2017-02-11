/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:24:16 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 13:23:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

/*
** int launch_test(t_unit_test **list):
** 	Use:
** 		Will browse, print the name and execute all functions in 'list' in a
** 		subproces (forked). If the function return 0, increment the total of
** 		functions that succeded and print "OK", and if the function returned -1
** 		or subproces was killed by a signal (SIGBUS, SIGSEGV, SIGALRM), print
** 		correspondig error message.
** 		Will free the 'list' passed in arg but not the pointer to 'list' itself.
** 	Return:
** 		On error, will print an error to STDERR and call exit with code -1.
** 		Return 0 if all test passed, -1 if at least one test failled.
*/

static int	sf_call_test(int (*test_func)(void))
{
	int		out;
	int		state;

	out = -1;
	if (fork() == 0)
	{
		alarm(10);
		exit(test_func());
	}
	else
	{
		wait(&state);
		if (WIFSIGNALED(state))
		{
			if (WTERMSIG(state) == SIGBUS)
				write(1, "[BUS]", 5);
			else if (WTERMSIG(state) == SIGSEGV)
				write(1, "[SEGV]", 6);
			else if (WTERMSIG(state) == SIGALRM)
				write(1, "[TIMEOUT]", 9);
			else
				write(1, "[SIGNAL]", 8);
		}
		else if(WIFEXITED(state))
			write(1, (out = WEXITSTATUS(state)) ? "[KO]" : "[OK]", 4);
		else
			write(1, "[STOPED]", 8);
	}
	return (out);
}

static int	sf_strlen(char *str)
{
	int	out;

	out = 0;
	while (str[out] != '\0')
		++out;
	return (out);
}

int			launch_test(t_unit_test **list)
{
	t_unit_test	*ptr;
	t_unit_test	*tmp;
	int			succeded;

	if (list == NULL && write(2, "launch_test got NULL list\n", 26))
		exit(-1);
	ptr = *list;
	succeded = 0;
	while (ptr != NULL)
	{
		write(1, "\t> ", 3);
		write(1, ptr->name, sf_strlen(ptr->name));
		write(1, " : ", 3);
		if (sf_call_test(ptr->test_func))
			succeded = -1;
		write(1, "\n", 1);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	return (succeded);
}
