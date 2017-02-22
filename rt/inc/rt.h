/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:05:50 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 17:32:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include <libftx.h>
# include <libftocl.h>
# include <libftjson.h>

# define OCL_SOURCE_PATH "./scl/raytracer.cl"
# define NONE 0
# define UPD 1

typedef enum		e_prim_type
{
	INVALID = -1, SPHERE = 0, PLANE = 1, CONE = 2, CYLINDER = 3, PARABOLOID = 4
}					t_prim_type;

typedef enum		e_pert_type
{
	SINE = 1, CHECKERBOARD = 2
}					t_pert_type;

typedef enum		e_color_filter
{
	SEPIA = 1, GRAYSCALE = 2, CARTOON = 3
}					t_color_filter;

typedef struct		s_perturbation
{
	cl_float		normal;
	t_pert_type		color;
}					t_perturbation;

typedef struct		s_texture
{
	cl_ulong		info_index;
	cl_float2		stretch;
	cl_float2		offset;
}					t_texture;

typedef struct		s_material
{
	cl_float4		color;
	cl_float		diffuse;
	cl_float		specular;
	cl_float		reflection;
	t_perturbation	perturbation;
	t_texture		texture;
}					t_material;

typedef struct		s_img_info
{
	cl_ulong		index;
	cl_int2			size;
}					t_img_info;

typedef struct		s_pair
{
	char			*name;
	cl_ulong		index;
}					t_pair;

typedef struct		s_material_holder
{
	int				nb_materials;
	char			**name;
	t_material		*materials;
}					t_material_holder;

typedef struct		s_textures_holder
{
	int				nb_info;
	char			**path;
	t_img_info		*info;
	int				total_raw_size;
	cl_int			*raw_bmp;
}					t_textures_holder;

typedef struct		s_camera
{
	cl_float4		pos;
	cl_float4		dir;
	cl_float4		up;
	cl_float4		right;
	cl_float4		vpul;
	cl_float2		vp_size;
	float			dist;
	t_quaternion	orientation;
	t_vector		origin_dir;
	t_vector		origin_up;
	t_vector		origin_right;
}					t_camera;

typedef struct		s_limit
{
	cl_int			relative;
	cl_float4		high;
	cl_float4		low;
}					t_limit;

typedef struct		s_primitive
{
	t_prim_type		type;
	cl_float4		position;
	cl_float4		direction;
	cl_float		radius;
	cl_uint			material;
	t_limit			limit;
}					t_primitive;

typedef struct		s_light
{
	cl_float4		position;
	cl_float4		color;
}					t_light;

typedef struct		s_argn
{
	cl_int2			screen_size;
	cl_int			nb_objects;
	cl_int			nb_lights;
	cl_int			map_primitives;
	cl_float		ambient;
	cl_float		direct;
	cl_int			antialias;
	cl_int			bounce_depth;
	t_color_filter	filter;
	cl_int			stereoscopy;
	t_texture		skybox;
	cl_int			nb_info;
	cl_int			nb_materials;
}					t_argn;

typedef struct		s_mouse
{
	int				is_select;
	int				x;
	int				y;
}					t_mouse;

typedef struct		s_cmd
{
	char			*scene;
	char			*output;
	int				progress_bar_toggle;
}					t_cmd;

int					cb_exit(int k, int s, void *p);
int					keys(t_ftx_data *data);
int					command_line(int argc, char **argv);
void				direct_output(char *path);
void				rt(void);
void				update(int c);
t_camera			*cam(void);
void				rotate_cam(double angle, t_vector axe);
void				calc_vpul(void);
void				update_kernel_args(void);
t_primitive			**prim(void);
t_argn				*argn(void);
t_ubmp				*out(void);
t_ubmp				*prim_map(void);
t_cmd				*cmd(void);
t_light				**lights(void);
void				parser(const char *src);
void				init_output(void);
cl_float4			cl_vector_from_json_array(t_json_value *node,
						cl_float4 default_return);
t_textures_holder	*textures_holder(void);
void				parse_images(t_json_value *root);
t_material_holder	*materials(void);
t_material			default_material(void);
void				parse_images(t_json_value *root);
void				parse_camera(t_json_value *c);
int					check_parsed_data(void);
void				parse_lights(t_json_value *l);
void				parse_objects(t_json_value *o);
void				parse_render_options(t_json_value *ro);
t_texture			parse_texture(t_json_value *t, t_texture default_return);
void				*parse_materials(t_json_value *m);
t_material			parse_material(t_json_value *m, t_material out);
cl_float4			cl_float4_normalize(cl_float4 v);
cl_float4			cl_float4_add(cl_float4 a, cl_float4 b);
void				cl_float4_p_add(cl_float4 *a, cl_float4 b);
cl_float4			cl_float4_scale(cl_float4 v, cl_float s);
cl_float4			cl_float4_sub(cl_float4 a, cl_float4 b);
cl_float4			ft_vector_thales(cl_float4 origin, cl_float4 v1,
						cl_float4 v2, cl_float4 r);
int					mouse_click(int key, int x, int y, void *data);
int					mouse_move(int x, int y, void *data);
int					mouse_off(int key, int x, int y, void *data);

#endif
