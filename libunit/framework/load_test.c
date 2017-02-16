/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:23:36 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 19:47:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

/*
** void load_test(t_unit_test **list, char *name, int (*test_func)(void)):
** 	Use:
** 	Return:
** 		On error, will print an error to STDERR and call exit with code -1.
** 	Args:
** 		t_unit_test **list:
** 			Pointer to head of linked list of type t_unit_test.
** 			The first call of 'load_test' should have 'list' pointing to a NULL.
** 			Each consecutive call to 'load_test' will expand 'list'.
** 			The expanded list use allocated memory and should be sent to a
** 			closing 'launch_test' call ('launch_test' will free 'list', but not
** 			the pointer to 'list' itself).
** 		char *name:
** 			Name to print when running test_func.
** 			Should not be NULL.
** 		int (*test_func)(void):
** 			Pointer to a function to execute.
** 			Should not be NULL.
** 			Pointed function should return -1 on test fail or 0 on succes.
*/

static t_unit_test	*sf_load_test(t_unit_test **list, char *name,
								int (*test_func)(void))
{
	t_unit_test	*out;

	if (list == NULL &&
			print_yellow(2, "load_test got NULL list\n", 24))
		exit(-1);
	if (name == NULL &&
			print_yellow(2, "load_test got NULL name\n", 24))
		exit(-1);
	if (test_func == NULL &&
		print_yellow(2, "load_test got NULL test_func\n", 29))
		exit(-1);
	if ((out = (t_unit_test*)malloc(sizeof(t_unit_test))) == NULL &&
		print_yellow(2, "load_test's call to malloc returned NULL\n", 41))
		exit(-1);
	return (out);
}

void				load_test(t_unit_test **list, char *name,
								int (*test_func)(void), int expected_status)
{
	t_unit_test	*out;
	t_unit_test	*tmp;

	out = sf_load_test(list, name, test_func);
	out->name = name;
	out->test_func = test_func;
	out->expected_status = expected_status;
	out->next = NULL;
	if (*list == NULL)
		*list = out;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = out;
	}
}
