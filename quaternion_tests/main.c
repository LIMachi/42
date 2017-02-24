#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct			s_double3
{
	double x;
	double y;
	double z;
}						t_double3;

typedef struct			s_quaternion
{
	double r;
	double x;
	double y;
	double z;
}						t_quaternion;

/*
** normalize the vector if needed, math and logic optimised by me
** return -42 in the r component if an error (null vector) occur
*/
t_quaternion			rotation_quaternion_build(double angle, t_double3 v)
{
	double			t;
	t_quaternion	out;

	if (v.x == v.y && v.x == v.z && v.x == 0)
		return ((t_quaternion){.r = -42});
	angle /= 2;
	out.r = cos(angle);
	if ((t = v.x * v.x + v.y * v.y + v.z * v.z) != 1)
		t = sin(angle) / sqrt(t);
	else
		t = sin(angle);
	out.x = t * v.x;
	out.y = t * v.y;
	out.z = t * v.z;
	return (out);
}

/*
** warning, does not check the norm of the quaternion! (asume the quaternion to
** be a rotation quaternion normalized), and does not check the size of mat
*/

/*
** mat[1][2] = 2 * (q.y * q.z - q.r * q.x); was initialy (in the math i found)
** mat[1][2] = 2 * (q.y * q.z + q.r * q.x); but i think is an error because it
** seem to give incorect "y" rotation
*/

void					rotation_quaternion_to_mat(t_quaternion q, double **mat)
{
	mat[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
	mat[0][1] = 2 * (q.x * q.y - q.r * q.z);
	mat[0][2] = 2 * (q.r * q.y + q.x * q.z);
	mat[1][0] = 2 * (q.r * q.z + q.x * q.y);
	mat[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
	mat[1][2] = 2 * (q.y * q.z - q.r * q.x);
	mat[2][0] = 2 * (q.x * q.z - q.r * q.y);
	mat[2][1] = 2 * (q.r * q.x + q.y * q.z);
	mat[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);
}

/*
** warning, does not check if mat is a valid rotation matrix of size 3 * 3
*/

t_double3				rotation_apply(t_double3 v, double **mat)
{
	return ((t_double3){
		.x = v.x * mat[0][0] + v.y * mat[0][1] + v.z * mat[0][2],
		.y = v.x * mat[1][0] + v.y * mat[1][1] + v.z * mat[1][2],
		.z = v.x * mat[2][0] + v.y * mat[2][1] + v.z * mat[2][2]});
}

/*
** note: multiplying a per b should result in the rotation b after the
** rotation a, wich should remove the quadran effect
*/

t_quaternion			quaternion_multiply(t_quaternion a, t_quaternion b)
{
	return ((t_quaternion){
		.r = a.r * b.r - a.x * b.x - a.y * b.y - a.z * b.z,
		.x = a.x * b.r + a.r * b.x - a.z * b.y + a.y * b.z,
		.y = a.y * b.r + a.z * b.x + a.r * b.y - a.x * b.z,
		.z = a.z * b.r - a.y * b.x + a.x * b.y + a.r * b.z});
}

int						main(void)
{
	t_double3		*points;
	t_double3		axe;
	t_quaternion	rotation;
	t_quaternion	tmp_quat;
	double			**tmp_mat;
	int				i;
	double			angle;

	angle = 120.0 * (M_PI / 180.0);
	axe = (t_double3){.x = 1, .y = 1, .z = 1};
	tmp_quat = rotation_quaternion_build(angle, axe);
	if ((tmp_quat = rotation_quaternion_build(angle, axe)).r == -42)
		printf("quaternion could not be calculated with axe x: %f, y: %f, z: %f\n", axe.x, axe.y, axe.z);
	points = (t_double3*)malloc(sizeof(t_double3) * 8);
	points = (t_double3[8]){{-1, -1, -1},{1, -1, -1},{-1, 1, -1},{1, 1, -1},
							{-1, -1, 1},{1, -1, 1},{-1, 1, 1},{1, 1, 1}};
	rotation = (t_quaternion){.r = 1};
	rotation = quaternion_multiply(rotation, tmp_quat);
	tmp_mat = (double**)malloc(sizeof(double*) * 3);
	tmp_mat[0] = (double*)malloc(sizeof(double) * 3);
	tmp_mat[1] = (double*)malloc(sizeof(double) * 3);
	tmp_mat[2] = (double*)malloc(sizeof(double) * 3);
	rotation_quaternion_to_mat(rotation, tmp_mat);
	printf("initial state:\n");
	for (i = 0; i < 8; ++i)
	{
		printf("x: %.3f, y: %.3f, z: %.3f\n", points[i].x, points[i].y, points[i].z);
		points[i] = rotation_apply(points[i], tmp_mat);
	}
	printf("\nafter rotation:\n");
	for (i = 0; i < 8; ++i)
		printf("x: %.3f, y: %.3f, z: %.3f\n", points[i].x, points[i].y, points[i].z);
}
