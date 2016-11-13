typedef struct
{
	float r;
	float i;
}	complex;

typedef struct	s_fractol_args
{
	unsigned int	iterations;
	float			z0r;
	float			z0i;
	unsigned int	width;
	unsigned int	length;
	float			view_port_left;
	float			view_port_up;
	float			view_port_right;
	float			view_port_down;
}				t_fractol_args;

complex	comp_sqr(complex z)
{
	complex out;

	out.r = z.r * z.r - z.i * z.i;
	out.i = 2.0f * z.r * z.i;
	return (out);
}

complex	comp_add(complex a, complex b)
{
	complex	out;

	out.r = a.r + b.r;
	out.i = a.i + b.i;
	return (out);
}

float	ft_absf(float v)
{
	if (v < 0.0f)
		return (-v);
	return (v);
}

float	ft_modf(float v, float m)
{
	if (m == 0.0f)
		return (-1.0f);
	m = ft_absf(m);
	while (v < 0.0f)
		v += m;
	while (v > m)
		v -= m;
	return (v);
}

int	ft_hsv2rgb(float hue, float saturation, float value)
{
	float	c;
	float	x;
	float	m;
	float	h;
	float	tmp[3];

	c = value * saturation;
	h = hue / 60;
	x = c * (1.0 - ft_absf(ft_modf(h, 2.0) - 1.0));
	m = value - c;
	tmp[0] = m + c * ((h >= 0 && h < 1) || (h >= 5 && h < 6))
			+ x * ((h >= 1 && h < 2) || (h >= 4 && h < 5));
	tmp[1] = m + c * (h >= 1 && h < 3)
			+ x * ((h >= 0 && h < 1) || (h >= 3 && h < 4));
	tmp[2] = m + c * (h >= 3 && h < 5)
			+ x * ((h >= 2 && h < 3) || (h >= 5 && h < 6));
	return (((int)(tmp[0] * 255) << 16) | ((int)(tmp[1] * 255) << 8) |
			(int)(tmp[2] * 255));
}

__kernel void	mandelbrot( __global const t_fractol_args *args,
							__global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= args->width * args->length)
		return ;
	float x = args->view_port_left + (args->view_port_right - args->view_port_left) * ((float)(kindex % args->width) / (float)args->width);
	float y = args->view_port_up + (args->view_port_down - args->view_port_up) * ((float)(kindex / args->width) / (float)args->length);

	complex	c;
	c.r = x;
	c.i = y;
	complex	z;
	z.r = args->z0r;
	z.i = args->z0i;
	int		i =			-1;

	while (z.r * z.r + z.i * z.i < 4 && ++i < args->iterations)
		z = comp_add(comp_sqr(z), c);
	color[kindex] = ft_hsv2rgb(((float)i / (float)args->iterations) * 360.0f, 1.0f, 1.0f);
}
