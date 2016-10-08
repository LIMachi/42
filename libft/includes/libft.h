/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/08 04:49:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** optimisation flags to replace code with macro, assembler or other code
*/

/*
** # define OP 1
*/
# define ASM 0
# define BSWAPA 0


# if defined(__unix__) || defined(__unix) || defined(unix)
#  define UNIX 1
# endif

# define BIG_ENDIAN __ORDER_BIG_ENDIAN__
# define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
# define LOCAL_ENDIAN __BYTE_ORDER__

# define MACINTOCH 1
# define LINUX 2
# define FREEBSD 4
# define WINDOWS 8

# if defined(__WINDOWS__)
#  define OS WINDOWS
# elif defined(__MACH__) || defined(__APPLE__)
#  define OS MACINTOCH
# elif defined (__FreeBSD__)
#  define OS FREEBSD
# else
#  define OS LINUX
# endif

# include <stdint.h>

/*
** windows compatibility
*/

# if (OS != WINDOWS)
#  define WORD uint16_t
#  define DWORD uint32_t
#  define LONG uint32_t
#  define O_BINARY 0
# endif

# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>

/*
** error related defines
*/

# define FT_ERROR_CHECK 1
# define FT_ERROR_SET 2
# define FT_ERROR_CLEAR 3
# define FT_ERROR_PRINT 4
# define FT_ERROR_ERRNO 5

/*
** memory related defines
*/

# define MEM_K * 1024
# define MEM_M MEM_K MEM_K
# define MEM_G MEM_M MEM_K
# define MEM_T MEM_G MEM_K
# define BUFF_SIZE 1 MEM_K

/*
** debug and protection related defines
*/

# define ERROR_MODE 0
# define DEBUG_MODE 0
# define FD_LIMIT 12288
# define GLOBAL_ALLOC 2 MEM_M

# define XT_RDONLY 1

/*
** simple matematical defines
*/

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define SIGN(x) ((x) < 0 ? -1 : ((x) > 0))
# define FRAC(x) ((x) - (int)(x))
# define FLOOR(x) ((x) - FRAC(x))
# define CEIL(x) ((x) - FRAC(x) + (FRAC(x) != 0))
# define ROUND(x) ((x) - FRAC(x) + (FRAC(x) >= 0.5))
# define INT(x) ((x) - FRAC(x))
# define SQR(x) ((x) * (x))

/*
** mathematical precision defines
*/

# define DOUBLE_PRECISION 15
# define FLOAT_PRECISION 7

/*
** trigonometrical defines
*/

# define PI	(3.14159265358979323846)
# define PI2 (1.57079632679489661923)
# define PI4 (0.78539816339744830962)
# define PIL (3.141592653589793238462643383279502884L)
# define PI2L (1.570796326794896619231321691639751442L)
# define PI4L (0.785398163397448309615660845819875721L)
# define RADIAN(x) (PIL * (((long double)(x)) / 180.0L))
# define DEGRE(x) (180.0L * (((long double)(x)) / PIL))

typedef	struct	s_ft_fd
{
	int			fd;
	int			pos;
	char		*path;
	int			flags;
}				t_ft_fd;

/*
** typedef of a classic int function pointer with undefined parameters
*/

typedef int (*t_int_func_undef)();

/*
** structures of type linked list
*/

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_alist
{
	int					id;
	void				*content;
	size_t				content_size;
	struct s_alist		*last;
	struct s_alist		*next;
}						t_alist;

/*
** structures of type coordinal points
*/

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_complex
{
	double				r;
	double				i;
}						t_complex;

typedef struct			s_quaternion
{
	double				r;
	double				i;
	double				j;
	double				k;
}						t_quaternion;

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_matrix
{
	double				**mat;
	t_point				size;
}						t_matrix;

/*
** stores the default alignement in a pile then set the alignement to 1
** changing the alignement might change the padding of struct/union/enum/etc
*/
#pragma pack(push, 1)

typedef struct	s_bitmap_file_header
{
	WORD		file_type;
	DWORD		file_size;
	DWORD		reserved;
	DWORD		offset;
}				t_bitmap_file_header;

typedef struct	s_dib_header
{
	DWORD		dib_size;
	LONG		width;
	LONG		height;
	WORD		planes;
	WORD		bit_count;
	DWORD		bit_compression;
	DWORD		size_image;
	LONG		x_pixels_meter;
	LONG		y_pixels_meter;
	DWORD		colors_in_tab;
	DWORD		color_important;
	DWORD		red_bmask;
	DWORD		green_bmask;
	DWORD		blue_bmask;
	DWORD		alpha_bmask;
	DWORD		color_space_type;
	char		color_space_endpoint[36];
	DWORD		gamma_red;
	DWORD		gamma_green;
	DWORD		gamma_blue;
	DWORD		intent;
	DWORD		icc_profile_data;
	DWORD		icc_profile_size;
	DWORD		reserved;
}				t_dib_header;

/*
** restores the padding/alignement from the last call of #pragma pack(push)
*/
#pragma pack(pop)

typedef struct	s_bitmap
{
	t_dib_header	info;
	unsigned char*	bmp;
}				t_bitmap;

/*
** ubmp stands for uncompressed bitmap, size should contain the size in pixels
** and data all the pixels ARGB code stored in a X + size.y * Y patern
** (left to right and top to bottom)
*/

typedef	struct	s_ubmp
{
	t_point		size;
	int			*data;
}				t_ubmp;

/*
** struct for a tree-like 2dlist
*/
typedef struct			s_xtree
{
	int					type;
	int					security;
	unsigned long long	id;
	void				*data;
	struct s_xtree		**root;
	struct s_xtree		*next;
	struct s_xtree		*prev;
	struct s_xtree		*up;
	struct s_xtree		*down;
}						t_xtree;

# if !defined(__BYTE_ORDER__) || !defined(__ORDER_LITTLE_ENDIAN__) || !defined(__ORDER_BIG_ENDIAN__)
#  error "Endian macros are undefined! (Check \"<COMPILER> -E -dM - < /dev/null | grep ORDER\")"
# endif

# if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define DBG_SUBT1 uint16_t
#  define DBG_SUBT2 int16_t
#  define FIX_INT sub.f2
#  define FIX_FRAC sub.f1
#  ifdef OP
#   define INTFIX(x) (x << 16)
#   define FIXINT(x) (x >> 16)
#  endif
# elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define DBG_SUBT1 int16_t
#  define DBG_SUBT2 uint16_t
#  define FIX_INT sub.f1
#  define FIX_FRAC sub.f2
#  ifdef OP
#   define INTFIX(x) (x >> 16)
#   define FIXINT(x) (x << 16)
#  endif
# else
#  error "Unknown Endian! (Check BYTE_ORDER definition)"
# endif

typedef struct			s_subfix
{
	DBG_SUBT1			f1;
	DBG_SUBT2			f2;
}						t_subfix;

typedef union			u_fix
{
	int32_t				i32;
	t_subfix			sub;
}						t_fix;

# ifndef INTFIX
#  define INTFIX(x) ((t_fix){.FIX_INT = x}).i32
# endif
# ifndef FIXINT
#  define FIXINT(x) ((t_fix){.i32 = x}).FIX_INT
# endif

typedef struct			s_fixpoint
{
	t_fix				x;
	t_fix				y;
}						t_fixpoint;

/*
** structure used by the get_next_line function
*/

typedef struct			s_gnl_tcf
{
	char				**ptr;
	char				*str;
}						t_gnl_tcf;

int						ft_error(int flag, int data);

int						get_next_line(const int fd, char **line);

/*
** type conversion function
*/

int						ft_atoi(const char *str);
char					*ft_itoa(int c);

/*
** memory acces and modification function
*/

void					ft_bzero(void *s, size_t n);
void					*ft_memalloc(size_t size);
void					*ft_memccpy(void *dst, const void *src, int c,
									size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					ft_memdel(void **ap);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, int c, size_t len);

/*
** condition check functions, usually returns 1 on succes and 0 on failure
*/

int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_isspace(int c);

/*
** file tree related function
*/

t_xtree					*ft_xtree_new(void *data, t_xtree **root, int type,
										int security);
t_xtree					*ft_xtree_add_shild(t_xtree *parent, void *data,
											int type, int security);
t_xtree					*ft_xtree_add_next(t_xtree *parent, void *data,
											int type, int security);

/*
** linked list related functions
*/

void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst, void (*del)(void *,
									size_t));
void					ft_lstiter(t_list *lst, void(*f)(t_list *elem));
t_list					*ft_lstnew(void const *content, size_t content_size);
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_lstappend(t_list **alst, t_list *new);

t_alist					*ft_alstnew(int id, void *content, size_t content_size);
void					ft_alstadd(t_alist *lst, t_alist *new);
void					ft_alstdel(t_alist *lst, void (*del)(void *, size_t));
void					ft_alstdelone(t_alist *lst, void (*del)(void *,
										size_t));
void					ft_alstappend(t_alist *lst, t_alist *new);
void					ft_alstiter(t_alist *lst, void (*f)(t_alist *elem));
t_alist					*ft_alstmap(t_alist *lst, t_alist *(*f)(t_alist *elem));
t_alist					*ft_alsttop(t_alist *lst);
t_alist					*ft_alstbot(t_alist *lst);
t_alist					*ft_alssearchid(int id, t_alist *lst);
t_alist					*ft_alstdeltop(t_alist *lst, void (*del)(void *,
										size_t));
t_alist					*ft_alstdelbot(t_alist *lst, void (*del)(void *,
										size_t));
t_alist					*ft_alstdelnode(t_alist *lst, void (*del)(void *,
										size_t));

/*
** table related functions
*/

void					**ft_taballoc(int x, int y, size_t block);
void					ft_tabfree(void **tab, int y);
void					***ft_tab3dalloc(int x, int y, int z, size_t block);

/*
** terminal and fd output functions
*/

void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					ft_puttab(char **tab);
void					ft_puttab_fd(char **tab, int fd);
void					ft_putlist(t_list **sl);
void					ft_putlist_fd(t_list **sl, int fd);

/*
** character string related functions
*/

char					*ft_strcat(char *dst, const char *src);
char					*ft_strchr(char *str, int c);
void					ft_strclr(char *s);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *dst, const char *src);
void					ft_strdel(char **as);
char					*ft_strdup(const char *s1);
char					*ft_strndup(const char *s1, const int end);
int						ft_strequ(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strncat(char *dst, const char *src, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t					ft_strlen(const char *s);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
									char));
int						ft_strncmp(char *s1, char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t n);
char					*ft_strnew(size_t size);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strnstr(char *str1, char *str2, size_t n);
char					*ft_strrchr(const char *str, int c);
char					**ft_strsplit(char const *s, char c);
char					*ft_strstr(char *str1, char *str2);
char					*ft_strsub(char const *s, unsigned int start,
									size_t len);
char					*ft_strtrim(char const *s);
int						ft_strcntc(char const *str, char c);
int						ft_strcntw(char const *str);
t_list					**ft_strlsplit(char *s, char c);
int						ft_tolower(int c);
int						ft_toupper(int c);
char					*ft_lsttostr(t_list *lst);
char					*ft_strnw(char *str);

/*
** files related functions
*/

char					*ft_readfile(int fd);

/*
** coordinal points related functions
*/

t_point					ft_ptinit(t_point *p, int x, int y);
t_point					*ft_ptnew(int x, int y);
t_point					ft_point(int x, int y);

/*
** math functions
*/

double					ft_sin(double x);
double					ft_cos(double x);
double					ft_tan(double x);
double					ft_asin(double x);
double					ft_acos(double x);
double					ft_pow10d(int p);
float					ft_pow10f(int p);
double					ft_sqrtd(double v);
float					ft_sqrtf(float v);
int						ft_sqrti(int v);

/*
** bitmap related functions
*/

t_ubmp					*ft_bmp_to_ubmp(t_bitmap *bitmap);
t_bitmap				*ft_bitmap_file_load(char *path);

/*
** wrapper functions for file acces
*/

t_ft_fd					ft_open(const char *path, int flags);
int						ft_close(t_ft_fd *fd);
t_ft_fd					ft_reopen(t_ft_fd *fd);
ssize_t					ft_write(t_ft_fd *fd, const void *buf, size_t count);
ssize_t					ft_read(t_ft_fd *fd, void *buf, size_t count);
off_t					ft_lseek(t_ft_fd *fd, off_t offset, int whence);

/*
** vector (double3) functions
*/

t_vector				ft_vector(const double x, const double y,
													const double z);
t_vector				ft_vector_negate(const t_vector v);
t_vector				ft_vector_add(const t_vector a, const t_vector b);
t_vector				ft_vector_substract(const t_vector a, const t_vector b);
t_vector				ft_vector_scale(const t_vector v, const double s);
double					ft_vector_magnitude(const t_vector v);
t_vector				ft_vector_normalize(const t_vector v);
double					ft_vector_distance(const t_vector a, const t_vector b);
double					ft_vector_dot_product(const t_vector a,
												const t_vector b);
double					ft_vector_angle(const t_vector a, const t_vector b);
t_vector				ft_vector_projection(const t_vector a,
												const t_vector b);
t_vector				ft_vector_cross_product(const t_vector a,
												const t_vector b);

/*
** matrix functions
*/

t_matrix				*ft_matrix_new(const int x, const int y);
void					ft_matrix_free(t_matrix *m);
t_matrix				*ft_matrix_multply(const t_matrix *a,
											const t_matrix *b);

/*
** complex (imaginary composed numbers) functions
*/

t_complex				ft_complex(const double r, const double i);
t_complex				ft_complex_rotor(const double r);
t_complex				ft_complex_add(const t_complex a, const t_complex b);
t_complex				ft_complex_substract(const t_complex a,
											const t_complex b);
t_complex				ft_complex_scale(const t_complex c, const double s);
t_complex				ft_complex_multiply(const t_complex a,
											const t_complex b);
double					ft_complex_norm(const t_complex c);
t_complex				ft_complex_conjugate(const t_complex c);
t_complex				ft_complex_divide(const t_complex a, const t_complex b);
t_complex				ft_complex_power(const t_complex c, int power);
t_complex				ft_complex_normalize(const t_complex c);

/*
** quaternion functions
*/

t_quaternion			ft_quat(const double r, const double i, const double j,
																const double k);
t_quaternion			ft_quat_add(const t_quaternion a, const t_quaternion b);
t_quaternion			ft_quat_substract(const t_quaternion a,
											const t_quaternion b);
t_quaternion			ft_quat_multiply(const t_quaternion a,
											const t_quaternion b);
t_quaternion			ft_quat_conjugate(const t_quaternion q);
double					ft_quat_norm(const t_quaternion q);
t_quaternion			ft_quat_inverse(const t_quaternion q);
t_quaternion			ft_quat_divide(const t_quaternion a,
										const t_quaternion b);
t_quaternion			ft_quat_scale(const t_quaternion q, const double s);
t_quaternion			ft_quat_normalize(const t_quaternion q);
double					ft_quat_dot_product(const t_quaternion a,
											const t_quaternion b);
t_quaternion			ft_quat_rotation_build(double angle,
												const t_vector vector);

/*
** conversion functions
*/

t_matrix				*ft_quat_rotation_to_matrix(t_quaternion q);
int						ft_matrix_multply_vector(t_vector *v, t_matrix *m);

#endif
