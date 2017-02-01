/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:15:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 12:43:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char	debug[]="__kernel void example1(void)\n{\n}\n";

cl_float4	_cl_float4(cl_float x, cl_float y, cl_float z, cl_float w)
{
	cl_float4	out;

	out.x = x;
	out.y = y;
	out.z = z;
	out.w = w;
	return (out);
}

/*
** prepare a ray array from a camera "cam" to a virtual screen of size
** "screen_size"
*/

cl_float4	*ray_plane(const t_camera *cam, const cl_int2 screen_size)
{
	t_vector	vpul;
	cl_int2		i;
	cl_float4	*out;

	vpul.x = cam->pos.x + (cam->dir.x * cam->dist) + (cam->up.x * (
			screen_size.y / 2.0)) - (cam->right.x * (screen_size.x / 2.0));
	vpul.y = cam->pos.y + (cam->dir.y * cam->dist) + (cam->up.y * (
			screen_size.y / 2.0)) - (cam->right.y * (screen_size.x / 2.0));
	vpul.z = cam->pos.z + (cam->dir.z * cam->dist) + (cam->up.z * (
			screen_size.y / 2.0)) - (cam->right.z * (screen_size.x / 2.0));
	i.y = -1;
	if ((out = (cl_float4*)ft_malloc(sizeof(
			cl_float4) * screen_size.x * screen_size.y)) == NULL)
		return (NULL);
	while (++i.y < screen_size.y && (i.x = -1))
		while (++i.x < screen_size.x)
			out[i.y * screen_size.x + i.x] = _cl_float4(
				(cl_float)(vpul.x + cam->right.x * i.x - cam->up.x *i.y),
				(cl_float)(vpul.y + cam->right.y * i.x - cam->up.y *i.y),
				(cl_float)(vpul.z + cam->right.z * i.x - cam->up.z *i.y),
				(cl_float)0);
	return (out);
}

void	rtv1(void)
{
	ft_printf("Kernel: %.8s was succesfully loaded\n",
				(char*)&ftocl_data()->current_kernel->id);
}

int	main(const int argc, char **argv, char **env)
{
	void	*ptr;
	int		fd;

	ft_init(env);
	if (argc != 2)
	{
		ft_printf("\nUsage: \t%s/%s <scene.json>\n\n", ft_pwd(),
					ptr = ft_path_name(argv[0]));
		ft_free(ptr);
		ft_end(0);
	}
	if ((fd = open(OCL_SOURCE_PATH, O_RDONLY)) == -1)
		ft_end(-1);
	ftocl_make_program(ftocl_str_to_id64("rtv1"),
		ft_str_clear_commentaries(ft_readfile(fd)));
	close(fd);
	if (!(fd = ftocl_set_current_kernel(ftocl_str_to_id64("example2"))))
		rtv1();
	if (fd == 1)
		ft_end(0 * ft_printf("kernel was not found\n"));
	ftocl_end();
	ft_end(0);
	return (0);
}
