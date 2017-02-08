/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 00:41:26 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 23:59:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_DEBUG 1

#include <libft.h>
#include <libftjson.h>

int	main(int argc, char **argv, char **env)
{
	char			*src;
	int				fd;
	t_json_value	*root;

	if (argc < 2)
		return (-1);
	ft_init(env);
	src = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1 || (src = ft_readfile(fd)) == NULL)
		ft_error(EINVAL, "Can't open file\n");
	close(fd);
	if ((fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IDEFAULT)) == -1)
		ft_error(EINTERN, "Can't open file output.txt\n");
	root = ft_json_parse_src(src);
	ft_json_print(fd, root);
	ft_json_print_clike(fd, root);
	close(fd);
	ft_json_free(root);
	ft_free(src);
	double test = 2;
	unsigned long *test2 = (unsigned long*)&test;
	ft_putnbr_bin(*test2);
	ft_putchar('\n');
	ft_end(0);
	return (0);
}
