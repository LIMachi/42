#define USE_DOUBLE 0

#if USE_DOUBLE
typedef double		t_float;
#else
typedef float		t_float;
#endif

typedef struct
{
	t_float r;
	t_float i;
}	comp;

typedef struct
{
	int	x;
	int	y;
}	point;

typedef struct
{
	unsigned int	iterations;
	comp			z0;
	point			size;
	comp			vp_ul;
	comp			vp_dr;
	float			color;
}	t_fractol_args;

comp	comp_divide(comp a, comp b);
t_float	comp_abs(comp z);
comp	ccomp(t_float r, t_float i);
comp	comp_sqr(comp z);
comp	comp_cube(comp z);
comp	comp_add(comp a, comp b);
int		hsv2rgb(float hue, float saturation, float value);
int		coloration(int iteration, int max, float shift);

comp	comp_divide(comp a, comp b)
{
	comp	out;

	if(b.r == 0)
		b.r = 0.00000001;
	if(b.i == 0)
		b.i = 0.00000001;
	out.r = (a.r * b.r + a.i * b.i) / (b.r * b.r + b.i * b.i);
	out.i = (a.i * b.r - a.r * b.i) / (b.r * b.r + b.i * b.i);
	return (out);
}

t_float	comp_abs(comp z)
{
	return (sqrt(z.r * z.r + z.i * z.i));
}

comp	ccomp(t_float r, t_float i)
{
	comp	out;

	out.r = r;
	out.i = i;
	return (out);
}

comp	comp_sqr(comp z)
{
	comp out;

	out.r = z.r * z.r - z.i * z.i;
	out.i = 2.0f * z.r * z.i;
	return (out);
}

comp	comp_cube(comp z)
{
	comp	out;

	out.r = z.r * z.r * z.r - 3 * z.r * z.i * z.i;
	out.i = 3 * z.r * z.r * z.i - z.i * z.i * z.i;
	return (out);
}

comp	comp_add(comp a, comp b)
{
	comp	out;

	out.r = a.r + b.r;
	out.i = a.i + b.i;
	return (out);
}

int		hsv2rgb(float hue, float saturation, float value)
{
	float	c;
	float	x;
	float	m;
	float	h;
	float	tmp[3];

	c = value * saturation;
	h = fmod(fabs(hue), 360.0f) / 60.0f;
	x = c * (1.0f - fabs(fmod(h, 2.0f) - 1.0f));
	m = value - c;
	tmp[0] = m + c * ((h >= 0.0f && h < 1.0f) || (h >= 5.0f && h < 6.0f))
			+ x * ((h >= 1.0f && h < 2.0f) || (h >= 4.0f && h < 5.0f));
	tmp[1] = m + c * (h >= 1.0f && h < 3.0f)
			+ x * ((h >= 0.0f && h < 1.0f) || (h >= 3.0f && h < 4.0f));
	tmp[2] = m + c * (h >= 3.0f && h < 5.0f)
			+ x * ((h >= 2.0f && h < 3.0f) || (h >= 5.0f && h < 6.0f));
	return (((int)(tmp[0] * 255.0f) << 16) | ((int)(tmp[1] * 255.0f) << 8) |
			(int)(tmp[2] * 255.0f));
}

int		coloration(int iteration, int max, float shift)
{
	if (iteration == max)
		return (0);
	return (hsv2rgb(shift + 360.0f * (float)iteration / (float)max, 1.0f, 1.0f));
}

__kernel void	mandelbrot(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	c;
	c.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	c.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	z = args->z0;
	unsigned int		iteration = 0;
	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
		z = comp_add(comp_sqr(z), c);
		++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	julia(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	z;
	z.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	z.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	c = args->z0;
	unsigned int		iteration = 0;
	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
		z = comp_add(comp_sqr(z), c);
		++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	burning_ship(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	c;
	c.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	c.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	z = args->z0;
	unsigned int		iteration = 0;
	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
		z.i = fabs(z.i);
		z.r = fabs(z.r);
		z = comp_add(comp_sqr(z), c);
		++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	custom(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	c;
	c.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	c.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	unsigned int		iteration = 0;
	comp	z;
	z = args->z0;
	comp	t;
	while ((unsigned int)iteration < args->iterations)
	{
		t.r = z.r * z.r;
		t.i = z.i * z.i;
		if ((t.r + t.i) > 4.0f)
			break ;
		z.i = (2.0f * z.i * z.r) + c.i;
		z.r = t.r - t.i + c.r;
		++iteration;
	}
	iteration = (int)(((t.r + t.i) / c.r) * c.i) % args->iterations;
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	multibrot(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	c;
	c.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	c.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	z = args->z0;
	unsigned int		iteration = 0;
	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
		z = comp_add(comp_cube(z), c);
		++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	newtonbug(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	c;
	c.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	c.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	z;
	z = c;
	comp	r1;
	comp	r2;
	comp	r3;
	r1.r = -1.0f; r1.i = 0.0f;
	r2.r = 0.5f; r2.i = (float)-sin(2.0f * 3.14159265359f / 3.0f);
	r2.r = 0.5f; r2.i = -r2.i;
	comp	z3;
	comp	z2;
	unsigned int		iteration = 0;

	while ((unsigned int)iteration < args->iterations
		&& comp_abs(comp_add(z, r1)) >= 0.00000001f
		&& comp_abs(comp_add(z, r2)) >= 0.00000001f
		&& comp_abs(comp_add(z, r3)) >= 0.00000001f)
		if (comp_abs(z) <= 0.00000001f)
			iteration = args->iterations;
		else
		{
			z3 = comp_cube(z);
			z2 = comp_sqr(z);
			z.r -= (z3.r - 1.0f) / (z2.r + 3.0f);
			z.i -= (z3.i - 1.0f) / (z2.i + 3.0f);
			++iteration;
		}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	spider(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	z;
	z.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	z.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	c;
	c = z;
	unsigned int		iteration = 0;

	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
			z = comp_add(comp_sqr(z), c);
			c = comp_add(comp_divide(c, ccomp(2, 0)), z);
			++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	circle(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	z;
	z.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	z.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	c;
	c = args->z0;
	unsigned int		iteration = 0;

	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
			z = comp_add(comp_sqr(z), ccomp(sin(comp_abs(z)), cos(comp_abs(c))));
			c = ccomp(-z.i, z.r);
			++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	trijulia(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	z;
	z.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	z.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	c;
	c = args->z0;
	unsigned int		iteration = 0;

	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
			z = comp_add(comp_cube(z), c);
			++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	halfwing(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	z;
	z.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	z.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	comp	c;
	c = args->z0;
	unsigned int		iteration = 0;

	while (z.r * z.r + z.i * z.i < 4 && (unsigned int)iteration < args->iterations)
	{
			z = comp_add(z, c);
			c = comp_cube(comp_add(z, ccomp(c.i, -c.r)));
			++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}

__kernel void	brotiverse(__global const t_fractol_args *args, __global int *color)
{
	size_t		kindex =	get_global_id(0);
	if (kindex >= (size_t)(args->size.x * args->size.y))
		return ;
	comp	c;
	c.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((t_float)((kindex % args->size.x)) / (t_float)args->size.x);
	c.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((t_float)((kindex / args->size.x)) / (t_float)args->size.y);
	unsigned int		iteration = 0;
	comp	z;
	z = args->z0;
	comp	t;
	while ((unsigned int)iteration < args->iterations)
	{
		t.r = z.r * z.r * 2;
		t.i = z.i * z.i;
		if ((t.r + t.i) > 4.0f)
			break ;
		z.i = (3.0f * z.i * z.r) + cos(c.i);
		z.r = t.r - t.i + sin(c.r);
		++iteration;
	}
	color[kindex] = coloration(iteration, args->iterations, args->color);
}
