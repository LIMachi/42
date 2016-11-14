/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:00:20 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 10:08:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

static void CL_CALLBACK	notify(const char *errinfo, const void *private_info,
								size_t cb, void *user_data)
{
	static unsigned int	n = 0;

	++n;
	(void)private_info;
	(void)cb;
	(void)user_data;
	*ft_global_flags() |= GF_FORCE_LOG;
	ft_putendl("_____________________________________________________________");
	ft_putstr("OpenCL notify error (nb: ");
	ft_putnbr(n);
	ft_putstr("): ");
	ft_putstr(errinfo);
	ft_putchar('\n');
	ft_putendl("_____________________________________________________________");
}

t_ocl_data	*ftocl_data(void)
{
	static t_ocl_data	data = {0};
	cl_uint		n;
	cl_int		e;

	if (!(data.platform && data.device && data.context && data.queue))
	{
		ft_log("Initializing OpenCL environement...\n");
		clGetPlatformIDs(0, NULL, &n);
		if (n == 0)
			ft_error(EINTERN, "No opencl platform found");
		clGetPlatformIDs(1, &data.platform, NULL);
		clGetDeviceIDs(data.platform, CL_DEVICE_TYPE_GPU, 1, &data.device, &n);
		if (n == 0)
			ft_error(EINTERN, "No opencl gpu device found");
		data.context = clCreateContext(0, 1, &data.device, &notify, NULL, &e);
		if (e != CL_SUCCESS)
			ft_error(EINTERN, "Error on creation of context");
		data.queue = clCreateCommandQueue(data.context, data.device, 0, &e);
		if (e != CL_SUCCESS)
			ft_error(EINTERN, "Error on creation of command queue");
	}
	return (&data);
}
