/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:24:16 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 15:52:43 by hmartzol         ###   ########.fr       */
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

static int	sf_strlen(char *str)
{
	int	out;

	out = 0;
	while (str[out] != '\0')
		++out;
	return (out);
}

static void	sf_putnbr(unsigned int v)
{
	unsigned int		p;
	static const char	base[11] = "0123456789";

	p = 1;
	while (p * 10 < v)
		p *= 10;
	while (p)
	{
		write(1, &base[((v / p) % 10)], 1);
		p /= 10;
	}
}

static void	sf_final_count(unsigned int succeded, unsigned int total)
{
	write(1, TF_CYAN "\n--- ", 10);
	sf_putnbr(succeded);
	write(1, "/", 1);
	sf_putnbr(total);
	write(1, " test passed successfully ---\n" TF_RESET, 35);
}

int			launch_test(t_unit_test **list)
{
	t_unit_test		*ptr;
	t_unit_test		*tmp;
	unsigned int	succeded;
	unsigned int	total;

	if (list == NULL && write(2, "launch_test got NULL list\n", 26))
		exit(-1);
	ptr = *list;
	succeded = 0;
	total = 0;
	while (ptr != NULL)
	{
		++total;
		write(1, "\t> ", 3);
		write(1, ptr->name, sf_strlen(ptr->name));
		write(1, " : ", 3);
		if (!call_test(ptr->test_func, ptr->expected_status))
			++succeded;
		write(1, "\n", 1);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	sf_final_count(succeded, total);
	return (succeded != total);
}
