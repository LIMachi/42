/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:08:49 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 08:38:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "../tests.h"

int strlen_launcher(void)
{
	t_unit_test	*testlist;

	write(1, "STRLEN:\n", 8);
	testlist = NULL;
	load_test(&testlist, "Basic test", &basic_test);
	load_test(&testlist, "NULL test", &null_test);
	return (launch_test(&testlist));
}
