/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 09:57:43 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/12 01:43:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char			*file;
	int				fd;
	cl_program		program;
	cl_kernel		kernel;
	size_t	x_pixels = 16;
	size_t	y_pixels = 16;
	size_t	mod = (x_pixels * y_pixels) % 16;
	const size_t	array_size = (x_pixels * y_pixels) + (mod ? 16 - mod : 0);
	int		*hc = (int*)ft_malloc(sizeof(int) * array_size);
	cl_mem dl, dvpxl, dvpxr, dvpyu, dvpyd, dxp, dyp, dc;
	int				err = 0;

	if (argc < 2)
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	file = ft_readfile(fd);
//	printf("%s", file);
	close(fd);
	float hvpxl = -2.0f;
	float hvpyu = -2.0f;
	float hvpxr = 2.0f;
	float hvpyd = 2.0f;
	unsigned int hl = 100;
	DEBUG
	program = ftocl_make_program(1, (const char **)&file, NULL);
	DEBUG
	kernel = clCreateKernel(program, "mandelbrot", 0);
	DEBUG
	dvpxl = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_float), &hvpxl, 0);
	dvpxr = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_float), &hvpxr, 0);
	dvpyu = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_float), &hvpyu, 0);
	dvpyd = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_float), &hvpyd, 0);
	dxp = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_uint), &x_pixels, 0);
	dyp = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_uint), &y_pixels, 0);
	dl = clCreateBuffer(ftocl_data()->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_uint), &hl, 0);
	dc = clCreateBuffer(ftocl_data()->context, CL_MEM_WRITE_ONLY,
		array_size * sizeof(cl_int), 0, 0);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&dvpxl);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&dvpyu);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&dvpxr);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&dvpyd);
	clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&dxp);
	clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&dyp);
	clSetKernelArg(kernel, 6, sizeof(cl_mem), (void *)&dl);
	clSetKernelArg(kernel, 7, sizeof(cl_mem), (void *)&dc);
	clEnqueueNDRangeKernel(ftocl_data()->queue, kernel, 1, 0, &array_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(ftocl_data()->queue, dc, CL_TRUE, 0,
		array_size * sizeof(cl_int), hc, 0, 0, 0);
	for(int i = 0; i < y_pixels; ++i)
	{
		for(int j = 0; j < x_pixels; ++j)
			printf("%d ", hc[i * x_pixels + j]);
		printf("\n");
	}
	free(hc);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(dl);
	clReleaseMemObject(dvpxl);
	clReleaseMemObject(dvpxr);
	clReleaseMemObject(dvpyu);
	clReleaseMemObject(dvpyd);
	clReleaseMemObject(dxp);
	clReleaseMemObject(dyp);
	clReleaseMemObject(dc);
	ftocl_end();
}
