typedef struct	s_primitive	//structure containing generic and specific data on the objects of the scene
{							//note the corespondance with the C structure (types end position of variables correspond, but types have a preceding "cl_")
	int		type;			//numerical type, ex: 0 = light, 1 = spheroid, 2 = planoid, 3 = cylinder, 4 = conoid, 5 = cuboid
	int		id;				//unique numerical id of the object
	float4	position;		//position of the object (accesed by .x, .y, .z, .w, w is discarded in 3D space)
	float4	direction;		//direction vector of the object (accesed by .x, .y, .z, .w, w is discarded in 3D space)
	float	radius;			//radius (if needed) of the object
	int		color;			//color (in 0xAARRGGBB) of the object
}				t_primitive;//norm42 magle

typedef struct	s_argn		//structure containing the limit of out, rays and objects
{							//note the corespondance with the C structure (types end position of variables correspond, but types have a preceding "cl_")
	int2	screen_size;	//total screen size in pixels (accesed by .x and .y)
	int		nb_objects;		//total number of object in the scene
}				t_argn;		//norm42 magle

//j'aime les commentaires, et vous? :p

__kernel void	example1(						//main kernel, called for each ray
					__global int *out,			//int bitmap, his size is equal to screen_size.x * screen_size.y
					__global t_argn *argn,		//structure containing important info on how to acces out, rays and objects
					__global float4 *rays,		//vector3 rays stored has float4 for convenience, the size of the array is screen_size.x * screen_size.y
					__global t_primitive *objects)	//set of objects in the scene, the number of objects (and so the limit of this array), is stored in argn
{
	//mode 1: we use 2D kernels:
	int	x = get_global_id(0);	//id x of the kernel in the global call
	int y = get_global_id(1);	//id y of the kernel in the global call

	if (x >= argn->screen_size.x || y >= argn->screen_size.y)	//the number of kernel executed can overflow the number initialy needed, this is a simple protection to avoid bad memory acces
		return ;
	out[x + y * argn->screen_size.x] = 0x00FFFFFF; //example: we discard all info and just set the output to a white screen
}

__kernel void	example2(						//main kernel, called for each ray
					__global int *out,			//int bitmap, his size is equal to screen_size.x * screen_size.y
					__global t_argn *argn,		//structure containing important info on how to acces out, rays and objects
					__global float4 *rays,		//vector3 rays stored has float4 for convenience, the size of the array is screen_size.x * screen_size.y
					__global t_primitive *objects)	//set of objects in the scene, the number of objects (and so the limit of this array), is stored in argn
{
	//mode 2: we use 1D Kernels:
	int i = get_global_id(0);	//id of the kernel in the global call
	int x = i % argn->screen_size.x;
	int y = i / argn->screen_size.x;

	if (i >= argn->screen_size.x * argn->screen_size.y)	//the number of kernel executed can overflow the number initialy needed, this is a simple protection to avoid bad memory acces
		return ;
	out[i] = 0x00FFFFFF; //example: we discard all info and just set the output to a white screen
}
