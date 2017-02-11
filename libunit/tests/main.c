/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 05:57:33 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/11 15:33:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "tests.h"

int	main(void)
{
	if (strlen_launcher())
		write(1, TF_RED "test failled\n" TF_RESET, 23);
	else
		write(1, TF_GREEN "test passed\n" TF_RESET, 22);
}
