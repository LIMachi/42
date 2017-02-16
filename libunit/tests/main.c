/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 05:57:33 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/12 19:38:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "tests.h"
#include <fcntl.h>

int	main(void)
{
	if (strlen_launcher())
		print_red(1, "test failled\n", 13);
	else
		print_green(1, "test passed\n", 12);
}
