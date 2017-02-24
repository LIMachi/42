// raytracer kernel is pretty cool actually

#if __OPENCL_VERSION__ < 120
# define COS cosf
#else
# define COS cos
#endif

#define NONE 0
#define NO_PRIMITIVE -1

typedef enum		e_prim_type
{
	SPHERE = 0, PLANE = 1, CONE = 2, CYLINDER = 3, PARABOLOID = 4
}					t_prim_type;

typedef enum		e_pert_type
{
	SINE = 1, CHECKERBOARD = 2
}					t_pert_type;

typedef enum		e_color_filter
{
	SEPIA = 1, GRAYSCALE = 2, CARTOON = 3
}					t_color_filter;

typedef enum		e_ray_type
{
	ORIGIN = 0, REFLECTED = 1
}					t_ray_type;

typedef struct		s_perturbation
{
	float			normal;
	t_pert_type		color;
}					t_perturbation;

typedef struct		s_texture
{
	ulong			info_index;
	float2			stretch;
	float2			offset;
}					t_texture;

typedef struct		s_material
{
	float4			color;
	float			diffuse;
	float			specular;
	float			reflection;
	t_perturbation	perturbation;
	t_texture		texture;
}					t_material;

typedef struct		s_img_info
{
	ulong			index;
	int2			size;
}					t_img_info;

typedef struct		s_camera
{
	float4			pos;
	float4			dir;
	float4			up;
	float4			right;
	float4			vpul;
	float2			vp_size;
}					t_camera;

typedef struct		s_limit
{
	int				relative;
	float4			high;
	float4			low;
}					t_limit;

typedef struct		s_primitive
{
	t_prim_type		type;
	float4			position;
	float4			direction;
	float			radius;
	uint			material;
	t_limit			limit;
}					t_primitive;

typedef struct		s_light
{
	float4			position;
	float4			color;
}					t_light;

typedef struct		s_argn
{
	int2			screen_size;
	int				nb_objects;
	int				nb_lights;
	int				map_primitives;
	float			ambient;
	float			direct;
	int				antialias;
	int				bounce_depth;
	int				filter;
	int				stereoscopy;
	t_texture		skybox;
	int				nb_info;
	int				nb_materials;
}					t_argn;

typedef struct		s_ray
{
	float4			origin;
	float4			direction;
	float			dist;
	float			weight;
	int				depth;
	int				primitive_id;
	t_ray_type		type;
	float4			color;
}					t_ray;

//j'aime les commentaires, et vous? :p
/*
   NOTE HYPER IMPORTANTE:
   pour la compatibilité AMD, il faut continuer d'utiliser les flags __global et les pointeurs
   (AMD ne copie pas les déréférencements de pointeurs dans la stack, ce qui fait que les objets et la lumière n'étaient pas envoyé aux calculs)
   */

int		plane_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		sphere_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		cylinder_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		cone_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		paraboloid_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		solve_quadratic(float a, float b, float c, float *dist);
float4	get_normal(__global t_primitive *obj, __global t_material *mat, float4 point, t_ray *ray);
float4	phong(float4 dir, float4 norm);
float4	color_texture(__global t_primitive *prim, __global t_texture *tex, float4 normal, __global t_img_info *info, __global int *raw_bmp);
float4	skybox(__global t_texture *tex, t_ray ray, __global int *raw_bmp, __global t_img_info *img_info);
int		color_to_int(float4 color);
float4	int_to_color(int c);
int		raytrace(t_ray *ray, float4 *color, float4 *point,
		int *result, __global t_primitive *objects, __global t_light *lights,
		__global t_argn *argn, __global t_material *materials,
		__global t_img_info *img_info, __global int *raw_bmp);

#if 0
# define DOT local_dot
# define NORMALIZE local_normalize
# define LENGTH local_length
# define CROSS local_cross

inline float4	local_normalize(float4 v);
inline float	local_dot(float4 v1, float4 v2);
inline float4	local_cross(float4 v1, float4 v2);
inline float	local_length(float4 v);

inline float4	local_cross(float4 v1, float4 v2)
{
	float4 res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

inline float	local_dot(float4 v1, float4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float4	local_normalize(float4 v)
{
	float	t;

	if ((v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) || (t = (v.x * v.x + v.y * v.y + v.z * v.z)) == 1.0f)
		return (v);
	return (v / sqrt(t));
}

inline float	local_length(float4 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
#else
# define DOT dot
# define NORMALIZE normalize
# define LENGTH length
# define CROSS cross
#endif

// error correction
#ifndef EPSILON
# define EPSILON 0.0001f
#endif

// for shadows we need a larger value
#ifndef SHADOW_E
# define SHADOW_E 0.1f
#endif

// maximum ray count
#ifndef MAX_RAY_COUNT
# define MAX_RAY_COUNT (1 << 32)
#endif

// minimum direct lighting coefficient
#ifndef MIN_DIRECT
# define MIN_DIRECT 0.95f
#endif

// normal perturbation size
#ifndef NORMAL_PERTURBATION_SIZE
# define NORMAL_PERTURBATION_SIZE 10.0f
#endif

// color perturbation checkerboard size
#ifndef CHECKER_SIZE
# define CHECKER_SIZE 10
#endif

// cartoon effect steps
#ifndef CARTOON_STEPS
# define CARTOON_STEPS 3
#endif

int		plane_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float d = DOT(obj->direction, ray->direction);

	// facing the plane (d == 0)
	if (d > -EPSILON && d < EPSILON)
		return (0);

	float new_dist = DOT(obj->position - ray->origin, obj->direction) / d;

	if (new_dist > EPSILON && new_dist < *dist)
	{
		*dist = new_dist;
		return (d > 0 ? -1 : 1);
	}
	return (0);
}

int		sphere_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = obj->position - ray->origin;

	float a = DOT(ray->direction, ray->direction);
	float b = 2 * DOT(ray->direction, pos);
	float c = DOT(pos, pos) - obj->radius * obj->radius;
	return solve_quadratic(a, b, c, dist);
}

int		cylinder_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = obj->position - ray->origin;
	float4 p = CROSS(pos, obj->direction);
	float4 r = CROSS(ray->direction, obj->direction);

	float a = DOT(r, r);
	float b = 2 * DOT(r, p);
	float c = DOT(p, p) - obj->radius * obj->radius * DOT(obj->direction, obj->direction);
	return solve_quadratic(a, b, c, dist);
}

int		cone_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = ray->origin - obj->position;
	float4 dir = -ray->direction;

	float tr = tan(obj->radius * M_PI / 180.0f);
	float r = 1.0f + tr * tr;
	float dd = DOT(dir, obj->direction);
	float xv = DOT(pos, obj->direction);

	float a = DOT(dir, dir) - (r * dd * dd);
	float b = 2.0f * (DOT(dir, pos) - (r * dd * xv));
	float c = DOT(pos, pos) - (r * xv * xv);

	return solve_quadratic(a, b, c, dist);
}

int		paraboloid_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = ray->origin - obj->position;
	float4 dir = -ray->direction;

	float dv = DOT(dir, obj->direction);
	float xv = DOT(pos, obj->direction);

	float a = DOT(dir, dir) - dv * dv;
	float b = 2.0f * (DOT(dir, pos) - dv * (xv + 2.0f * obj->radius));
	float c = DOT(pos, pos) - xv * (xv + 4.0f * obj->radius);

	return solve_quadratic(a, b, c, dist);
}

int		solve_quadratic(float a, float b, float c, float *dist)
{
	float delta = b * b - 4.0f * a * c;
	if (delta < 0)
		return (0);

	delta = sqrt(delta);
	float x1 = (b - delta) / (2.0f * a);
	float x2 = (b + delta) / (2.0f * a);

	if (x1 < EPSILON) // use x2 is x1 is negative
	{
		if (x2 < EPSILON) // both are negative
			return (0);
		else if (x2 < *dist) // x2 positive
		{
			*dist = x2;
			return (-1);
		}
	}
	else if (x1 < *dist) // x1 positive
	{
		*dist = x1;
		return (1);
	}
	return (0);
}

inline int		limit(__global t_primitive *obj, float4 point)
{
	if (obj->limit.relative)
		point -= obj->position;
	//high
	return (point.x > obj->limit.high.x ||
		point.y > obj->limit.high.y ||
		point.z > obj->limit.high.z ||
		point.x < obj->limit.low.x ||
		point.y < obj->limit.low.y ||
		point.z < obj->limit.low.z);
}

inline int		intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	int i = 0;
	float d = *dist;

	switch (obj->type)
	{
		case SPHERE:
			i = sphere_intersect(obj, ray, dist);
			break;
		case PLANE:
			i = plane_intersect(obj, ray, dist);
			break;
		case CONE:
			i = cone_intersect(obj, ray, dist);
			break;
		case CYLINDER:
			i = cylinder_intersect(obj, ray, dist);
			break;
		case PARABOLOID:
			i = paraboloid_intersect(obj, ray, dist);
			break;
	}

	// limit our object
	float4 point = ray->origin + ray->direction * (*dist);
	if (limit(obj, point))
	{
		*dist = d;
		return (0);
	}

	return (i);
}

inline float4	get_normal(__global t_primitive *obj, __global t_material *mat, float4 point, t_ray *ray)
{
	float4 n = (float4)(0, 0, 0, 0);
	float r;

	switch (obj->type)
	{
		case SPHERE:
			n = point - obj->position;
			break;
		case PLANE:
			n = obj->direction;
			break;
		case CYLINDER:
			n = DOT(obj->direction, obj->position - point) * obj->direction + (point - obj->position);
			break;
		case CONE:

			r = DOT(ray->direction, obj->direction) * ray->dist + DOT(ray->origin - obj->position, obj->direction);
			n = point - obj->position - (1.0f + pow((float)tan(obj->radius * M_PI / 180.0f), 2)) * obj->direction * r;
/*
			r = obj->radius * M_PI / 180.0f;
			n = point - obj->position + (obj->direction * -DOT(point, obj->direction) / pow(COS(r), 2));*/
			break;
		case PARABOLOID:
			n = point - obj->position - obj->direction * obj->radius;
			break;
		default:
			return (n);
	}

	// normal perturbation
	if (mat->perturbation.normal > 0.0f)
	{
		float len = LENGTH(n);
		n.y += COS(point.y / NORMAL_PERTURBATION_SIZE) * mat->perturbation.normal * (len / NORMAL_PERTURBATION_SIZE);
	}

	return (NORMALIZE(n));
}

inline float2	texture_map(__global t_primitive *prim, float4 normal)
{
	float2 pos = (float2)(0, 0);

	switch (prim->type)
	{
		case SPHERE:
			pos.x = 0.5f + atan2(normal.z, normal.x) / (2.0f * M_PI);
			pos.y = 0.5f + asinpi(normal.y);
			break;
		default:
			return (float2)(0, 0);
	}
	return (pos);
}

inline float4	color_texture(__global t_primitive *prim, __global t_texture *tex, float4 normal, __global t_img_info *info, __global int *raw_bmp)
{
	float2 pos = texture_map(prim, normal);
	if (tex->stretch.x != 0.0f && tex->stretch.y != 0.0f)
		pos /= tex->stretch;
	pos += tex->offset;
	pos = fmod(pos, 1.0f);

	int x = pos.x * info->size.x;
	int y = pos.y * info->size.y;
	int raw_c = raw_bmp[info->index + y * (int)info->size.x + x] & 0x00FFFFFF;
	return int_to_color(raw_c);
}

inline float4	color_perturbation(float4 color, __global t_primitive *prim,
		t_pert_type pert, float4 normal)
{
	float2 pos = texture_map(prim, normal);

	switch (pert)
	{
		case CHECKERBOARD:
			if (fmod(pos.x * CHECKER_SIZE, 2) <= 1.0f ^ fmod(pos.y *
					CHECKER_SIZE, 2) <= 1.0f)
				color /= 1.5f;
			break;
		case SINE:
			color *= clamp(fabs(cos((pos.x + pos.y) * 10 * CHECKER_SIZE)), 0.5f, 1.0f);
			break;
	}

	return (color);
}

inline float4	phong(float4 dir, float4 norm)
{
	return (dir - 2 * DOT(dir, norm) * norm);
}

inline int		color_to_int(float4 color)
{
	color = clamp(color * 255.0f, 0.0f, 255.0f);
	return (int)(((int)color.x << 16) + ((int)color.y << 8) + (int)color.z);
}

inline float4	int_to_color(int c)
{
	float b = (c & 0xFF) / 255.0f;
	float g = ((c & 0xFF00) >> 8) / 255.0f;
	float r = ((c & 0xFF0000) >> 16) / 255.0f;
	return (float4)(r, g, b, 0.0f);
}

inline float4		color_filter(float4 color, t_color_filter filter)
{
	float4	out;
	float	t;

	switch (filter)
	{
		case SEPIA:
			out.x = color.x * 0.393f + color.y * 0.769f + color.z * 0.189f;
			out.y = color.x * 0.349f + color.y * 0.686f + color.z * 0.168f;
			out.z = color.x * 0.272f + color.y * 0.534f + color.z * 0.131f;
			break;
		case GRAYSCALE:
			t = (color.x + color.y + color.z) / 3.0f;
			out.x = t;
			out.y = t;
			out.z = t;
			break;
		case CARTOON:
			out.x = floor(color.x * CARTOON_STEPS) / CARTOON_STEPS;
			out.y = floor(color.y * CARTOON_STEPS) / CARTOON_STEPS;
			out.z = floor(color.z * CARTOON_STEPS) / CARTOON_STEPS;
			break;
		default:
			out = color;
			break;
	}

	return (out);
}


int		raytrace(t_ray *ray, float4 *color, float4 *point,
		int *result, __global t_primitive *objects, __global t_light *lights,
		__global t_argn *argn, __global t_material *materials,
		__global t_img_info *img_info, __global int *raw_bmp)
{
	int id = NO_PRIMITIVE;
	int	id_l = -1;
	int cur;
	int temp;

	// hit test against all primitives
	for (cur = 0; cur < argn->nb_objects; cur++)
	{
		if ((temp = intersect(&objects[cur], ray, &ray->dist)))
		{
			id = cur;
			*result = temp;
		}
	}

	// if we hit something, get relevant info
	__global t_primitive *prim;
	__global t_material *mat;
	float4 collision = (float4)(0, 0, 0, 0);
	float4 norm;

	float4 cur_color = (float4)(0, 0, 0, 0);
	float4 add_color = (float4)(0, 0, 0, 0);

	if (id != NO_PRIMITIVE)
	{
		// we have our primitive!
		prim = &objects[id];
		mat = &materials[prim->material];
		collision = ray->origin + ray->direction * ray->dist;

		// get the normal for this intersection point
		norm = get_normal(prim, mat, collision, ray);

		// invert the normal if we're "inside" the primitive
		if (*result == -1)
			norm = -norm;
	}

	// lights, maestro!
	int cur_l;
	t_ray ray_l;
	float dist_l;
	float scal;
	for (cur_l = 0; cur_l < argn->nb_lights; cur_l++)
	{
		t_light light = lights[cur_l];

		// calculate direct lighting
		if (argn->direct > EPSILON)
		{
			dist_l = LENGTH(light.position - ray->origin);
			ray_l.direction = NORMALIZE(light.position - ray->origin);
			ray_l.origin = ray->origin;

			// if our light is closer than intersect
			if (dist_l > EPSILON && dist_l < ray->dist)
			{
				// if our light is between us and the object, dot will
				// be positive
				scal = DOT(ray_l.direction, ray->direction);
				if (scal > EPSILON)
				{
					scal = pow(scal, dist_l / 100);
					if (scal > MIN_DIRECT)
					{
						id_l = cur_l;
						add_color += (light.color * (scal - MIN_DIRECT) / (1.0f - MIN_DIRECT)) * argn->direct;
					}
				}
			}
		}

		// if we didn't hit anything, don't calculate light for object
		if (id == NO_PRIMITIVE)
			continue;

		// check if our light source is blocked by an object
		// shadows start a tiny amount from the actual sphere to prevent
		// rounding errors
		dist_l = LENGTH(light.position - collision);
		ray_l.direction = NORMALIZE(light.position - collision);
		ray_l.origin = collision + ray_l.direction * SHADOW_E;
		int shadow = 0;

		float dist = MAXFLOAT;
		for (cur = 0; cur < argn->nb_objects; cur++)
		{
			if ((shadow = intersect(&objects[cur], &ray_l, &dist)) != 0)
			{
				if (dist > EPSILON && dist < dist_l) // it is between us
					break ;
				else // it is behind us
					shadow = 0;
			}
		}

		// get texture
		float4 color_l = mat->color;
		if (prim->type == SPHERE && mat->texture.info_index != ULONG_MAX)
		{
			__global t_img_info *info = &img_info[mat->texture.info_index];
			color_l = color_texture(prim, &mat->texture, norm, 	info, raw_bmp);
		}

		// ambient
		cur_color += color_l * argn->ambient;

		// did we hit something? it's a shadow... spooky!
		if (shadow)
			continue ;

		// diffuse lighting
		if (mat->diffuse > 0 && (scal = DOT(ray_l.direction, norm)) > 0)
			cur_color += color_l * light.color * scal * mat->diffuse;

		// specular highlights (needs pow to make the curve sharper)
		float4 ir = phong(-ray_l.direction, norm);
		if (mat->specular > 0 && scal > 0 &&
				(scal = DOT(ray_l.direction, ir)) > 0)
			cur_color += light.color * pow(scal, dist_l / 40) * mat->specular;
	}

	// calculate final color
	*color += clamp(cur_color / ((float)argn->nb_lights), 0.0f, 1.0f);

	// perturbation if we hit something
	if (id != NO_PRIMITIVE)
		*color = color_perturbation(*color, prim, mat->perturbation.color, norm);
	else
		*color = skybox(&argn->skybox, *ray, raw_bmp, img_info);

	// added color
	*color += add_color;

	// set collision point, return ID
	*point = collision;
	if (id_l > -1)
		return (-id_l - 2);
	return (id);
}

float4	skybox(__global t_texture *tex, t_ray ray, __global int *raw_bmp, __global t_img_info *img_info)
{
	if (tex->info_index == ULONG_MAX)
		return (float4)(0, 0, 0, 0);

	float4 normal = NORMALIZE(ray.direction);

	float2 pos;
	pos.x = 0.5f + atan2(normal.z, normal.x) / (2.0f * M_PI);
	pos.y = 0.5f + asinpi(normal.y);

	t_img_info info = img_info[tex->info_index];
	int x = pos.x * info.size.x;
	int y = pos.y * info.size.y;
	int raw_c = raw_bmp[info.index + y * info.size.x + x] & 0x00FFFFFF;
	return int_to_color(raw_c);
}

// our stack operations
#define PUSH_RAY(q, r, c) q[c++] = r;
#define POP_RAY(q, r, c) r = q[--c];

__kernel void	rt_kernel(
		__global int			*out,
		__global int			*prim_map,
		__global t_argn			*argn,
		__global t_primitive	*objects,
		__global t_light		*lights,
		__global t_camera		*cam,
		__global t_img_info		*img_info,
		__global t_material		*materials,
		__global int			*raw_bmp,
		__global int			*shift)
{
	//mode 2: we use 1D Kernels:
	size_t i = get_global_id(0) + *shift; //id of the kernel in the global call

	// the amount of kernels executed can be more than the screen_size, protect
	// against bad access
	if (i >= (size_t)argn->screen_size.x * (size_t)argn->screen_size.y)
		return ;

	float x = (float)(i % argn->screen_size.x);
	float y = (float)(i / argn->screen_size.x);

	t_ray		ray;

	// ray queue to emulate recursion
	t_ray		queue[MAX_RAY_COUNT];
	int			queue_pos = 0;

	// antialias variables
	int aa_x;
	int aa_y;
	int count = 0;

	float4 color = (float4)(0, 0, 0, 0);

	// antialias loop
	for (aa_y = 0; aa_y < argn->antialias; aa_y++)
	{
		for (aa_x = 0; aa_x < argn->antialias; aa_x++)
		{
			float2 aa;

			// subpixel positions
			aa.x = x + (aa_x - argn->antialias / 2.0f) / argn->antialias;
			aa.y = y + (aa_y - argn->antialias / 2.0f) / argn->antialias;

			// get our subray
			ray.direction = NORMALIZE(cam->vpul + NORMALIZE(cam->right) * (aa.x) - NORMALIZE(cam->up) * (aa.y));
			ray.origin = cam->pos;
			ray.dist = MAXFLOAT;
			ray.type = ORIGIN;
			ray.depth = 0;
			ray.weight = 1.0f;
			ray.color = (float4)(0, 0, 0, 0);

			// this is our starting ray, add it to the queue
			PUSH_RAY(queue, ray, queue_pos);

			// start iterating over our emulated stack
			while (queue_pos > 0)
			{
				t_ray cur_ray;
				float4 cur_color = (float4)(0, 0, 0, 0);
				float4 collision;

				// get our ray
				POP_RAY(queue, cur_ray, queue_pos);

				// raytrace!
				int result;
				int cur_id = raytrace(&cur_ray, &cur_color, &collision, &result, objects, lights, argn, materials, img_info, raw_bmp);

				if (cur_ray.depth == 0 && argn->map_primitives)
					prim_map[i] = cur_id + 1;

				// do things based on ray type
				switch (cur_ray.type)
				{
					case ORIGIN:
						color += cur_color * cur_ray.weight;
						break;
					case REFLECTED:
						color += cur_color * cur_ray.weight * cur_ray.color;
						break;
				}
				count++;

				// if we have exceeded our depth or didnt hit anything, skip
				if (cur_ray.depth >= argn->bounce_depth || cur_id == -1)
					continue;

				// beautiful reflections
				__global t_material *mat = &materials[objects[cur_id].material];
				float4 normal = get_normal(&objects[cur_id], mat, collision, &cur_ray);

				float refl = mat->reflection;
				if (refl > EPSILON)
				{
					float4 reflect = NORMALIZE(cur_ray.direction - 2.0f * DOT(cur_ray.direction, normal) * normal);

					t_ray r_ray;
					r_ray.dist = MAXFLOAT;
					r_ray.origin = collision + reflect * SHADOW_E;
					r_ray.direction = reflect;
					r_ray.depth = cur_ray.depth + 1;
					r_ray.weight = refl * cur_ray.weight;
					r_ray.type = REFLECTED;
					r_ray.color = color;

					if (r_ray.weight > EPSILON)
						PUSH_RAY(queue, r_ray, queue_pos);
				}

				// beautiful refractions
				/*
				float refr = mat->transparency;
				if (refr > 0.0f)
				{
					float i = cur_ray.refraction_index / mat->refraction_index;
					float d = DOT(-cur_ray.direction, normal);
					float4 refract = NORMALIZE(i * cur_ray.direction + (i * d - sqrt(max(1.0f - i * i * (1.0f - d * d), 0.0f))) * normal);

					t_ray r_ray;
					r_ray.dist = MAXFLOAT;
					r_ray.origin = collision + refract * SHADOW_E;
					r_ray.direction = refract;
					r_ray.depth = cur_ray.depth + 1;
					r_ray.weight = refr * cur_ray.weight;
					r_ray.type = REFRACTED;
					r_ray.color = color;
					r_ray.transparency = cur_ray.transparency;
					r_ray.refraction_index = cur_ray.refraction_index;

					if (r_ray.weight > EPSILON)
						PUSH_RAY(queue, r_ray, queue_pos);
				}*/
			}
		}
	}

	// divide by the total amount of samples
	color /= count;

	// apply color filter
	if (argn->filter != NONE)
		color = color_filter(color, argn->filter);

	// return the pixel color
	out[i] = color_to_int(color);
}
