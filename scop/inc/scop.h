/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:13:36 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/26 21:13:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

//most of the structures below use arrays with null termination

typedef struct						s_material
{
	GLfloat				ambient;
	GLfloat				diffuse;
	GLfloat				specular;
	GLfloat				specular_exponent;
	GLfloat				alpha;
	GLint				illumination_model;
}									t_material;

typedef struct						s_vertex
{
	GLfloat4			vpos;
	t_material			*material;
	GLfloat4			tpos;
}									t_vertex;

typedef struct						s_texture
{
	GLint4				size;
	GLfloat4			scale;
	GLfloat4			*pixel;
}									t_texture;

typedef struct						s_face
{
	t_vertex			vertex[3];
	t_texture			*texture;
}

typedef enum 					e_object3d_type{
	O3D_INVALID = 0,
	O3D_WORLD = 1,
	O3D_CAMERA = 2,
	O3D_OBJECT = 3,
	O3D_PARTICLE = 4,
	O3D_GROUP = 5
}								t_object3d_type;

typedef struct s_object3d_group	t_object3d_group;

typedef struct					s_object3d_base
{
	t_object3d_type		type;
	void				*self;		//literally a pointer to himslef
	t_object3d_group	**group;	//pointers to the group containing the object3d_base (inside any object3d, camera, world or particle), NULL terminated list
	GLfloat4			x_axis;
	GLfloat4			y_axis;
	GLfloat4			z_axis;
	GLfloat4			origin;
	GLfloat4			quaternion;
}								t_object_base;

struct							s_object3d_group
{
	t_object3d_base		base;		//used to apply transformation relative to the group and not from the world nor from the object
	GLuint				flags;		//flags to acces rights of group, like rotate, translate, scale, remove object, add object, etc...
	GLuint				nb_objects;
	t_object_base		**object;	//should contain an array of pointers to either t_object3d, t_camera, t_particle or t_world casted in t_object_base** for convenience
};

typedef struct					s_object3d
{
	t_object3d_base		base;
	GLuint				render_mode;
}								t_object3d;

typedef struct					s_camera
{
	t_object_base		base;
	t_object3d			*phisical_render;
	GLuint				filter;
	GLuint				output_mode;
	void				*output_target;
}								t_camera;

typedef struct					s_particle	//not yet implemented
{
	t_object_base		base;
}								t_particle;

//holder for easy clearing of allocated data used in worlds, and fast acces to object3d_base
typedef struct					s_3d_global_data_holder
{

}								t_3d_global_data_holder;

typedef struct					s_world
{
	t_object_base		base;			//all objects of the wolrd can be acceced via (world.base.group[0]->object)[object_id], by convention, object_id 0 should be the world itself
	t_camera			*active_camera;
}								t_world;

#endif
