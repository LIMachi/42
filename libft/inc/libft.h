/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 13:51:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define CC_CLANG 1
# if defined(__clang__)
#  define COMPILER CC_CLANG
# endif

# define CC_GCC 2
# if !defined(COMPILER) && (defined(__GNUC__) || defined(__GNUG__))
#  define COMPILER CC_GCC
# endif

# define CC_UNKNOWN 0
# ifndef COMPILER
#  define COMPILER CC_UNKNOWN
# endif

# if defined(__STDC__)
#  if defined(__STDC__VERSION__)
#   if __STDC__VERSION__ >= 199409L
#    if __STDC__VERSION__ >= 199901L
#     if __STDC__VERSION__ >= 201112L
#      define STD_VER 2011
#     else
#      define STD_VER 1999
#     endif
#    else
#     define STD_VER 1994
#    endif
#   else
#    define STD_VER 1989
#   endif
#  else
#   define STD_VER 0
#  endif
# else
#  define STD_VER -1
# endif

# ifndef __ULONG_LONG_MAX__
#  define __ULONG_LONG_MAX__ (__LONG_LONG_MAX__ << 1 | 1)
# endif

# ifndef __ULONG_MAX__
#  define __ULONG_MAX__ (__LONG_MAX__ << 1 | 1)
# endif

# ifndef __UINT_MAX__
#  define __UINT_MAX__ (__INT_MAX__ << 1 | 1)
# endif

# ifndef __USHRT_MAX__
#  define __USHRT_MAX__ (__SHRT_MAX__ << 1 | 1)
# endif

# ifndef __CHAR_MAX__
#  ifdef __CHAR_BIT__
#   define __CHAR_MAX__ ((1 << (__CHAR_BIT__ - 1)) - 1)
#  elif defined(__SIZEOF_CHAR__)
#   define __CHAR_MAX__ ((1 << ((__SIZEOF_CHAR__ << 3) - 1)) - 1)
#  else
#   define __CHAR_MAX__ 127
#  endif
# endif

# ifndef __UCHAR_MAX__
#  define __UCHAR_MAX__ (__CHAR_MAX__ << 1 | 1)
# endif

/*
** # include <limits.h>
*/

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

/*
** used to get precise int size
*/

# include <stdint.h>

/*
** sys/stat.h: for rights of file creation
*/

/*
** # include <sys/stat.h>
*/

# ifdef S_IDEFAULT
#  undef S_IDEFAULT
# endif
# define S_IDEFAULT (S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)

# define NORM_LIBFT 0

# ifndef FT_USE_FINAL_FREE
#  define FT_USE_FINAL_FREE 1
# endif

# ifndef FT_LOG_FINAL_FREE
#  define FT_LOG_FINAL_FREE 0
# endif

# ifndef NORM_LIBFT
#  define NORM_LIBFT 1
# endif

# ifndef USE_DEBUG
#  define USE_DEBUG 0
# endif

# if USE_DEBUG != 0
#  define DEBUG ft_printf("[%s]: %d\n", __func__, __LINE__);
# else
#  define DEBUG
# endif

/*
** intern flags to modify the beaving of certain functions
*/

# define GF_USE_LOG (0x0000000000000001ull)
# define GF_FORCE_LOG (GF_USE_LOG | 0x0000000000000002ull)

# define DEFAULT_FLAGS (GF_FORCE_LOG)

/*
** *****************************************************************************
*/

# if 1
#  define EXIT(v) exit (v)
# else
#  define EXIT(v) return (v)
# endif

/*
** optimisation flags to replace code with macro, assembler or other code
*/

/*
** # define OP 1
*/
# define ASM 0
# define BSWAPA 0

/*
** standard errno defines
*/

# ifndef _ASM_GENERIC_ERRNO_BASE_H
#  define _ASM_GENERIC_ERRNO_BASE_H
#  define EPERM		1
#  define ENOENT	2
#  define ESRCH		3
#  define EINTR		4
#  define EIO		5
#  define ENXIO		6
#  define E2BIG		7
#  define ENOEXEC	8
#  define EBADF		9
#  define ECHILD	10
#  define EAGAIN	11
#  define ENOMEM	12
#  define EACCES	13
#  define EFAULT	14
#  define ENOTBLK	15
#  define EBUSY		16
#  define EEXIST	17
#  define EXDEV		18
#  define ENODEV	19
#  define ENOTDIR	20
#  define EISDIR	21
#  define EINVAL	22
#  define ENFILE	23
#  define EMFILE	24
#  define ENOTTY	25
#  define ETXTBSY	26
#  define EFBIG		27
#  define ENOSPC	28
#  define ESPIPE	29
#  define EROFS		30
#  define EMLINK	31
#  define EPIPE		32
#  define EDOM		33
#  define ERANGE	34
#  define EINTERN	(-1u)
#  define ENOENV	(-2u)
# endif

# define MAXERRNOD 34

/*
** standard unions for BIG/LITTLE endian compatibility
*/

typedef union			u_float4c
{
	float		f;
	char		c[4];
}						t_float4c;

typedef union			u_double8c
{
	double		d;
	char		c[8];
}						t_double8c;

typedef	union			u_ldouble16c
{
	long double	ld;
	char		c[16];
}						t_ldouble16c;

/*
** pseudo posix defines
*/

# if !(defined (READ_MAX) && (READ_MAX <= (4294967296ull)))
#  ifdef READ_MAX
#   undef READ_MAX
#  endif
#  if defined(SSIZE_MAX) && (SSIZE_MAX <= (4294967296ull))
#   define READ_MAX SSIZE_MAX
#  else
#   define READ_MAX (4294967295ul)
#  endif
# endif

# if defined(__unix__) || defined(__unix) || defined(unix)
#  define UNIX 1
# endif

# if !defined(__BYTE_ORDER__) || !defined(__ORDER_LITTLE_ENDIAN__)
#  error "Endian macros are undefined!"
#  error "(Check \"<COMPILER> -E -dM - < /dev/null | grep ORDER\")"
# endif
# if !defined(__ORDER_BIG_ENDIAN__)
#  error "Endian macros are undefined!"
#  error "(Check \"<COMPILER> -E -dM - < /dev/null | grep ORDER\")"
# endif

# ifdef BIG_ENDIAN
#  undef BIG_ENDIAN
# endif
# ifdef LITTLE_ENDIAN
#  undef LITTLE_ENDIAN
# endif
# ifdef LOCAL_ENDIAN
#  undef LOCAL_ENDIAN
# endif
# define BIG_ENDIAN __ORDER_BIG_ENDIAN__
# define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
# define LOCAL_ENDIAN __BYTE_ORDER__

# ifndef LINUX
#  define LINUX 1
# endif

# if defined(MACINTOCH) && MACINTOCH == LINUX
#  undef MACINTOCH
# endif

# ifndef MACINTOCH
#  define MACINTOCH (LINUX + 1)
# endif

# if defined(FREEBSD) && (FREEBSD == LINUX || FREEBSD == MACINTOCH)
#  undef FREEBSD
# endif

# ifndef FREEBSD
#  define FREEBSD (MACINTOCH + 1)
# endif

# ifdef WINDOWS
#  if WINDOWS == LINUX || WINDOWS == MACINTOCH || WINDOWS == FREEBSD
#   undef WINDOWS
#  endif
# endif

# ifndef WINDOWS
#  define WINDOWS (FREEBSD + 1)
# endif

# ifdef OS
#  undef OS
# endif

# ifndef OS
#  if defined(__WINDOWS__)
#   define OS WINDOWS
#  elif defined(__MACH__) || defined(__APPLE__)
#   define OS MACINTOCH
#  elif defined (__FreeBSD__)
#   define OS FREEBSD
#  else
#   define OS LINUX
#  endif
# endif

/*
** windows compatibility
*/

# if (OS != WINDOWS)
#  define WORD uint16_t
#  define DWORD uint32_t
#  define LONG uint32_t
#  define O_BINARY 0
# endif

/*
** memory related defines
*/

# define MEM_K 1024
# define MEM_M (MEM_K * MEM_K)
# define MEM_G (MEM_M * MEM_K)
# define MEM_T (MEM_G * MEM_K)
# define BUFF_SIZE MEM_K
# define PAGE_SIZE MEM_G

/*
** debug and protection related defines
*/

# define ERROR_MODE 0
# define DEBUG_MODE 0

# ifndef FD_LIMIT
#  define FD_LIMIT 12288
# endif

# define XT_RDONLY 1

/*
** simple matematical defines
*/

# define MIN(x, y) ((x) > (y) ? (y) : (x))
# define MAX(x, y) ((x) < (y) ? (y) : (x))
# define ABS(x) ((x) < 0 ? -(x) : (x))
# define SIGN(x) ((x) < 0 ? -1 : ((x) > 0))
# define FRAC(x) ((double)(x) - (double)(long long)(x))
# define FLOOR(x) ((double)(x) - FRAC(x))
# define CEIL(x) ((double)(x) - FRAC(x) + (FRAC(x) != 0.0))
# define ROUND(x) ((double)(x) - FRAC(x) + (FRAC(x) >= 0.5))
# define SQR(x) ((x) * (x))

/*
** mathematical precision defines
*/

# define DOUBLE_PRECISION 15
# define FLOAT_PRECISION 7

/*
** math defines
*/

# if !defined(_MATH_H) && !defined(FT_FLOAT_H)
#  if LOCAL_ENDIAN == BIG_ENDIAN
#   define __QNAN_BYTES		{0x7f, 0xc0, 0, 0}
#  endif
#  if LOCAL_ENDIAN == LITTLE_ENDIAN
#   define __QNAN_BYTES		{0, 0, 0xc0, 0x7f}
#  endif
#  define NAN	(((t_float4c){.c = __QNAN_BYTES}).f)

#  if LOCAL_ENDIAN == BIG_ENDIAN
#   define __HUGE_VALF_BYTES	{0x7f, 0x80, 0, 0}
#  endif
#  if LOCAL_ENDIAN == LITTLE_ENDIAN
#   define __HUGE_VALF_BYTES	{0, 0, 0x80, 0x7f}
#  endif
#  define HUGE_VALF	(((t_float4c){.c = __HUGE_VALF_BYTES}).f)

#  if LOCAL_ENDIAN == BIG_ENDIAN
#   define __HUGE_VAL_BYTES	{0x7f, 0xf0, 0, 0, 0, 0, 0, 0}
#  endif
#  if LOCAL_ENDIAN == LITTLE_ENDIAN
#   define __HUGE_VAL_BYTES	{0, 0, 0, 0, 0, 0, 0xf0, 0x7f}
#  endif
#  define HUGE_VAL	(((t_double8c){.c = __HUGE_VAL_BYTES}).d)

#  define __HUGE_VALL_BYTES	{ 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f, 0, 0 }
#  define HUGE_VALL	(((t_ldouble16c){.c = __HUGE_VALL_BYTES}).ld)

#  define INFINITY	HUGE_VALF
# endif

# define M_E			2.71828182845904523536
# define M_LOG2E		1.44269504088896340736
# define M_LOG10E		0.43429448190325182765
# define M_LN2			0.69314718055994530942
# define M_LN10			2.30258509299404568402
# define M_PI			3.14159265358979323846
# define M_PI_2			1.57079632679489661923
# define M_PI_4			0.78539816339744830962
# define M_PI_180		0.01745329251994329547
# define M_1_PI			0.31830988618379067154
# define M_2_PI			0.63661977236758134308
# define M_180_PI		57.29577951308232286464
# define M_2_SQRTPI		1.12837916709551257390
# define M_SQRT2		1.41421356237309504880
# define M_SQRT1_2		0.70710678118654752440
# define M_LOG10_2		0.30102999566398119523
# define M_EL			2.718281828459045235360287471352662498L
# define M_LOG2EL		1.442695040888963407359924681001892137L
# define M_LOG10EL		0.434294481903251827651128918916605082L
# define M_LN2L			0.693147180559945309417232121458176568L
# define M_LN10L		2.302585092994045684017991454684364208L
# define M_PIL			3.141592653589793238462643383279502884L
# define M_PI_2L		1.570796326794896619231321691639751442L
# define M_PI_4L		0.785398163397448309615660845819875721L
# define M_PI_180L		0.017453292519943295769139146242365789L
# define M_1_PIL		0.318309886183790671537767526745028724L
# define M_2_PIL		0.636619772367581343075535053490057448L
# define M_180_PIL		57.295779513082320876654618402312735270L
# define M_2_SQRTPIL	1.128379167095512573896158903121545172L
# define M_SQRT2L		1.414213562373095048801688724209698079L
# define M_SQRT1_2L		0.707106781186547524400844362104849039L
# define M_LOG10_2L		0.301029995663981195225646428359489448L
# define RADIAN(x) (M_PI_180 * (x))
# define DEGRE(x) (M_180_PI * (x))

/*
** extended fd structure, used in wrapers ft_open, ft_close, ft_write, ft_read,
** ft_lseek
*/

typedef	struct			s_ft_fd
{
	int			fd;
	int			pos;
	char		*path;
	int			flags;
	int			rights;
}						t_ft_fd;

/*
** page structure, only to be used by ft_malloc_pgc, ft_free_pgc, ft_realloc_pgc
*/

typedef struct			s_page_3gs
{
	void	*p0;
	void	*p1;
	void	*p2;
	void	*stack;
	int		stack_free_pos;
	int		stack_used_pos;
}						t_page_3gs;

/*
** typedef of a classic int function pointer with undefined parameters
*/

typedef int				(*t_int_func_undef)();

/*
** structures of type coordinal points
*/

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

/*
** structure to manipulate complex numbers
*/

typedef struct			s_complex
{
	double				r;
	double				i;
}						t_complex;

/*
** structure to manipulate quaternion
*/

typedef struct			s_quaternion
{
	double				r;
	double				i;
	double				j;
	double				k;
}						t_quaternion;

/*
** structure to manipulate vectors and 3d coordinates
*/

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

/*
** structure to manipulate nm size matrixes
*/

typedef struct			s_matrix
{
	double				**mat;
	t_point				size;
}						t_matrix;

/*
** structure to manipulate first in last out piles
*/

typedef struct			s_pile
{
	void				**data;
	unsigned int		size;
	unsigned int		head;
}						t_pile;

/*
** structure to manipulate first in first out piles (or also named files)
*/

typedef struct			s_queue
{
	void				**data;
	unsigned int		size;
	unsigned int		head;
	unsigned int		tail;
}						t_queue;

/*
** stores the default alignement in a pile then set the alignement to 1
** changing the alignement might change the padding of struct/union/enum/etc
*/

# pragma pack(push, 1)

/*
** file header of a standard bitmap
*/

typedef struct			s_bitmap_file_header
{
	WORD		file_type;
	DWORD		file_size;
	DWORD		reserved;
	DWORD		offset;
}						t_bitmap_file_header;

/*
** standard bitmap header
*/

typedef struct			s_dib_header
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
}						t_dib_header;

/*
** restores the padding/alignement from the last call of #pragma pack(push)
*/

# pragma pack(pop)

/*
** pair of bitmap header and raw data
*/

typedef struct			s_bitmap
{
	t_dib_header		info;
	unsigned char		*bmp;
}						t_bitmap;

/*
** ubmp stands for uncompressed bitmap, size should contain the size in pixels
** and data all the pixels ARGB code stored in a X + size.y * Y patern
** (left to right and top to bottom)
*/

typedef	struct			s_ubmp
{
	t_point				size;
	int					*data;
}						t_ubmp;

/*
** set of polymorphic list objects, each have 4 data container common, and
** x more containers depending on the type of object.
** -type (object_type) should be unique and constant for each type of list
** -function (object_functions) should be a mask of up to 64 basic functions
**   common to all/most types of objects
** -data should be a void pointer containing any data set by and with the
**  discretion of the user (list global function should not change data
**  unless forced to)
** -next (pointer) should be a pointer to the next object in the list
**  (might be used without casting the object it is in, or casted to void)
** note: each const variable in those structures should only modified
** by functions, never by the user himself (but free should work on pointer
** pointing to an object without errors)
*/

# define OBJECT 0
# define OBJECT_FUNCTION 0

typedef struct s_object	t_object;
struct					s_object
{
	const uint32_t		type;
	const uint64_t		functions;
	void				*data;
	t_object			*next;
};

# define OBJECT_LIST 1
# define OBJECT_FUNCTIONS_LIST 0

typedef struct s_list	t_list;
struct					s_list
{
	const uint32_t	object_type;
	const uint64_t	object_functions;
	void			*data;
	t_list			*next;
	size_t			content_size;
};

# define OBJECT_DLLIST 2
# define OBJECT_FUNCTION_DLLIST 0

typedef struct s_2list	t_2list;
struct					s_2list
{
	const uint32_t	object_type;
	const uint64_t	object_functions;
	void			*data;
	t_2list			*next;
	t_2list			*prev;
	uint64_t		id;
	size_t			content_size;
};

# define OBJECT_XTREE 3
# define OBJECT_FUNCTION_XTREE 0

typedef struct s_xtree	t_xtree;
struct					s_xtree
{
	const uint32_t		object_type;
	const uint64_t		object_functions;
	void				*data;
	t_xtree				*next;
	t_xtree				*prev;
	uint64_t			id;
	unsigned int		type;
	unsigned int		security;
	t_xtree				**root;
	t_xtree				*up;
	t_xtree				*down;
};

# if LOCAL_ENDIAN == LITTLE_ENDIAN
#  define DBG_SUBT1 uint16_t
#  define DBG_SUBT2 int16_t
#  define FIX_INT sub.f2
#  define FIX_FRAC sub.f1
#  ifdef OP
#   define INTFIX(x) (x << 16)
#   define FIXINT(x) (x >> 16)
#  endif
# elif LOCAL_ENDIAN == BIG_ENDIAN
#  define DBG_SUBT1 int16_t
#  define DBG_SUBT2 uint16_t
#  define FIX_INT sub.f1
#  define FIX_FRAC sub.f2
#  ifdef OP
#   define INTFIX(x) ((x) >> 16)
#   define FIXINT(x) ((x) << 16)
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

typedef struct			s_xorshift1024star
{
	int					p;
	unsigned long long	s[16];
}						t_xorshift1024star;

# define TIME_DEFAULT_WEEKDAY_0 "Sunday"
# define TIME_DEFAULT_WEEKDAY_1 "Monday"
# define TIME_DEFAULT_WEEKDAY_2 "Tuesday"
# define TIME_DEFAULT_WEEKDAY_3 "Wednesday"
# define TIME_DEFAULT_WEEKDAY_4 "Thursday"
# define TIME_DEFAULT_WEEKDAY_5 "Friday"
# define TIME_DEFAULT_WEEKDAY_6 "Saturday"

# define TIME_SHORT_WEEKDAY_0 "Sun"
# define TIME_SHORT_WEEKDAY_1 "Mon"
# define TIME_SHORT_WEEKDAY_2 "Tue"
# define TIME_SHORT_WEEKDAY_3 "Wed"
# define TIME_SHORT_WEEKDAY_4 "Thu"
# define TIME_SHORT_WEEKDAY_5 "Fri"
# define TIME_SHORT_WEEKDAY_6 "Sat"

# define TIME_DEFAULT_MONTH_0  "January"
# define TIME_DEFAULT_MONTH_1  "February"
# define TIME_DEFAULT_MONTH_2  "March"
# define TIME_DEFAULT_MONTH_3  "April"
# define TIME_DEFAULT_MONTH_4  "May"
# define TIME_DEFAULT_MONTH_5  "June"
# define TIME_DEFAULT_MONTH_6  "July"
# define TIME_DEFAULT_MONTH_7  "August"
# define TIME_DEFAULT_MONTH_8  "September"
# define TIME_DEFAULT_MONTH_9  "October"
# define TIME_DEFAULT_MONTH_10 "November"
# define TIME_DEFAULT_MONTH_11 "December"

# define TIME_SHORT_MONTH_0  "Jan"
# define TIME_SHORT_MONTH_1  "Feb"
# define TIME_SHORT_MONTH_2  "Mar"
# define TIME_SHORT_MONTH_3  "Apr"
# define TIME_SHORT_MONTH_4  "May"
# define TIME_SHORT_MONTH_5  "Jun"
# define TIME_SHORT_MONTH_6  "Jul"
# define TIME_SHORT_MONTH_7  "Aug"
# define TIME_SHORT_MONTH_8  "Sep"
# define TIME_SHORT_MONTH_9  "Oct"
# define TIME_SHORT_MONTH_10 "Nov"
# define TIME_SHORT_MONTH_11 "Dec"

# define TIME_VALUES_MASK				0x00000FFF
# define TIME_YEAR						0x00000001
# define TIME_MONTH						0x00000002
# define TIME_MONTH_NAME				0x00000004
# define TIME_MONTH_BOTH				0x00000006
# define TIME_WEEK						0x00000008
# define TIME_WEEKDAY					0x00000010
# define TIME_WEEKDAY_NAME				0x00000020
# define TIME_WEEKDAY_BOTH				0x00000030
# define TIME_DAY						0x00000040
# define TIME_HOUR						0x00000080
# define TIME_MINUTE					0x00000100
# define TIME_SECOND					0x00000200
# define TIME_MILISECOND				0x00000400
# define TIME_NANOSECOND				0x00000800
# define TIME_VALUES_DEFAULT_DATE		0x00000065
# define TIME_VALUES_DEFAULT_TIME		0x00000380
# define TIME_VALUES_DEFAULT_EXTENDED	0x00000780
# define TIME_FORMAT_MASK				0xFFFFF000
# define TIME_FORMAT_DEFAULT			0x00001000
# define TIME_FORMAT_SHORT				0x00002000

typedef struct			s_time
{
	long			year;
	long			month;
	long			week;
	long			weekday;
	long			day;
	long			hour;
	long			minute;
	long			second;
	long			milisecond;
	long			nanosecond;
}						t_time;

char					*ft_time_to_str(t_time time, int verbose);

/*
** structure used by the get_next_line function
*/

typedef struct			s_gnl_tcf
{
	char				**ptr;
	char				*str;
}						t_gnl_tcf;

int						get_next_line(const int fd, char **line);

/*
** type conversion function
*/

int						ft_atoi(const char *str);
int						ft_atoi_extended(const char *str);
int						ft_atoi_base(const char *str, const int size_base,
															const char *base);
char					*ft_itoa(int n);
char					*ft_itoa_base(int n, const int size_base,
															const char *base);

/*
** memory acces and modification function
*/

void					*ft_malloc(size_t size);
void					*ft_free(void *ptr);
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
void					*ft_memdup(const void *src, size_t n);

/*
** condition check functions, usually returns 1 on succes and 0 on failure
*/

int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_isspace(int c);
int						ft_isupper(int c);
int						ft_islower(int c);
int						ft_ishexa(int c);
int						ft_isunix(int c);

/*
** evaluation funstions
*/

size_t					ft_evaluate_b128_size(__uint128_t v);
size_t					ft_evaluate_i128_size(__int128_t v);
size_t					ft_evaluate_o128_size(__uint128_t v);
size_t					ft_evaluate_u128_size(__uint128_t v);
size_t					ft_evaluate_x128_size(__uint128_t v);

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

t_2list					*ft_2lstnew(const uint64_t *id, void *content,
									size_t content_size);
void					ft_2lstadd(t_2list **lst, t_2list *new);
void					ft_2lstdel(t_2list *lst, void (*del)(void *, size_t));
void					ft_2lstdelone(t_2list *lst, void (*del)(void *,
										size_t));
void					ft_2lstappend(t_2list *lst, t_2list *new);
void					ft_2lstiter(t_2list *lst, void (*f)(t_2list *elem));
t_2list					*ft_2lstmap(t_2list *lst, t_2list *(*f)(t_2list *elem));
t_2list					*ft_2lsttop(t_2list *lst);
t_2list					*ft_2lstbot(t_2list *lst);
t_2list					*ft_2lstsearchid(const uint64_t *id, t_2list *lst);
t_2list					*ft_2lstdeltop(t_2list *lst, void (*del)(void *,
										size_t));
t_2list					*ft_2lstdelbot(t_2list *lst, void (*del)(void *,
										size_t));
t_2list					*ft_2lstdelnode(t_2list *lst, void (*del)(void *,
										size_t));

/*
** table related functions
*/

void					**ft_tab_alloc(int x, int y, size_t block);
void					ft_tab_free(void **tab, int y);
void					***ft_tab3d_alloc(int x, int y, int z, size_t block);

/*
** terminal and fd output functions
*/

void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putnbr_hex(unsigned long n);
void					ft_putnbr_hex_fd(unsigned long n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					ft_puttab(char **tab);
void					ft_puttab_fd(char **tab, int fd);
void					ft_putlist(t_list **sl);
void					ft_putlist_fd(t_list **sl, int fd);
int						ft_putnstr(char *str, int n);
int						ft_putnstr_fd(char *str, int n, int fd);

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
char					*ft_strnw(char *str);
char					*ft_strerror(int error);
char					*ft_stracat(char *str1, char *str2);
char					*ft_strndup(const char *s, size_t n);
char					*ft_strpdup(const char *s, const char *e);
int						ft_strcchr(const char *str, int c);

/*
** files related functions
*/

char					*ft_readfile(int fd);

/*
** coordinal points related functions
*/

t_point					*ft_point_init(t_point *p, const int x, const int y);
t_point					*ft_point_new(const int x, const int y);
t_point					ft_point(const int x, const int y);
t_point					ft_point_substract(const t_point a, const t_point b);
t_point					ft_point_add(const t_point a, const t_point b);
int						ft_point_equal(const t_point a, const t_point b);
double					ft_point_magnitude(const t_point point);
t_point					ft_point_difference(const t_point a, const t_point b);
double					ft_point_distance(const t_point a, const t_point b);
t_point					ft_point_middle(const t_point a, const t_point b);

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
int						ft_powi(int nbr, int exp);
float					ft_powf(float nbr, int exp);
double					ft_powd(double nbr, int exp);

/*
** bitmap related functions
*/

t_ubmp					*ft_bmp_to_ubmp(t_bitmap *bitmap);
t_bitmap				*ft_bitmap_file_load(char *path);
int						ft_bitmap_file_save(char *path, t_bitmap *bmp);
t_bitmap				*ft_ubmp_to_bmp(t_ubmp *ubmp);
void					ft_bmp_print_info(t_bitmap *bmp);

/*
** wrapper functions for file acces
*/

t_ft_fd					ft_open(const char *path, int flags, int rights);
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
t_vector				*ft_vector_new(const double x, const double y,
																const double z);
t_vector				*ft_vector_init(t_vector *vector, const double x,
											const double y, const double z);
int						ft_vector_equal(t_vector a, t_vector b);
t_vector				ft_vector_difference(t_vector a, t_vector b);
t_vector				ft_vector_middle(const t_vector a, const t_vector b);
t_vector				ft_vector_from_a_to_b(t_vector a, t_vector b);

/*
** matrix functions
*/

t_matrix				*ft_matrix_new(const int x, const int y);
t_matrix				*ft_matrix_unit(const int size);
void					ft_matrix_free(t_matrix *m);
t_matrix				*ft_matrix_multply(const t_matrix *a,
											const t_matrix *b);
t_matrix				*ft_matrix_add(const t_matrix *a, const t_matrix *b);
t_matrix				*ft_matrix_substract(const t_matrix *a,
											const t_matrix *b);
t_matrix				*ft_matrix_turn(const t_matrix *matrix);

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
t_complex				ft_complex_square(const t_complex z);

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
int						ft_quat_equal(const t_quaternion a,
									const t_quaternion b);

/*
** conversion functions
*/

t_matrix				*ft_quat_rotation_to_matrix(t_matrix *mat,
													t_quaternion q);
t_vector				ft_matrix_multply_vector(const t_vector v,
												const t_matrix *m);
t_vector				*ft_matrix_multply_vector_array(t_vector *va,
										size_t size, const t_matrix *m);
char					*ft_lsttostr(t_list *lst);

/*
** bit and byte manipulation functions
*/

unsigned short int		ft_bswap16(const unsigned short int x);
unsigned long int		ft_bswap32(const unsigned long int x);
unsigned long long int	ft_bswap64(const unsigned long long int x);

/*
** piles functions
*/

t_pile					*ft_pile_new(unsigned int size);
int						ft_pile_is_empty(t_pile *pile);
t_pile					*ft_pile_push(t_pile *pile, void *data);
t_pile					*ft_pile_look(t_pile *pile, void **data);
t_pile					*ft_pile_pull(t_pile *pile, void **data);
void					ft_pile_free(t_pile *pile);

/*
** queue functions
*/

t_queue					*ft_queue_new(unsigned int size);
int						ft_queue_is_empty(t_queue *queue);
t_queue					*ft_queue_push(t_queue *queue, void *data);
t_queue					*ft_queue_look(t_queue *queue, void **data);
t_queue					*ft_queue_pull(t_queue *queue, void **data);
void					ft_queue_free(t_queue *queue);

/*
** error related defines (passed to ft_global_error)
*/

# define ERROR_CHECK	1
# define ERROR_SET		2
# define ERROR_CLEAR	4
# define ERROR_PRINT	8
# define ERROR_ERRNO	16

/*
** the following defines are single flags, they can't be mixed with standard
** flags or with each other (passed to ft_error)
*/

# define ERROR_SILENT_ON	-1
# define ERROR_SILENT_OFF	-2
# define ERROR_GET_SILENT	-4

/*
** log related defines (passed to ft_global_log)
*/

# define LOG_SET_PATH		1
# define LOG_SET			2
# define LOG_PRINT			4
# define LOG_STORE			8
# define LOG_END			16
# define LOG				(LOG_SET | LOG_PRINT | LOG_STORE)
# define DEFAULT_LOG_PATH	"./log.txt"

int						ft_global_error(int flag, long data);
long					ft_error(long error, char *string);
char					*ft_global_log(int flag, char *data);
char					*ft_log(char *str);

/*
** initialiser function, set default global data ()
*/

void					ft_init(char **env);

/*
** closing function used to free all global data and exit with code r
*/

void					ft_end(int r);

/*
** pseudo malloc trickery
*/

t_page_3gs				ft_page(void);

/*
** intern flags to modify the beaving of certain functions
*/

uint64_t				*ft_global_flags(void);
int						ft_env_init(char **env);
int						ft_putenv(char *string);
t_object				**ft_global_env(void);
char					*ft_getenv(const char *name);
t_object				*ft_object_search(t_object *lst, int (*f)(t_object
								*node, void *user_data), void *user_data);
t_object				*ft_object_new(void *data);
t_object				**ft_object_add(t_object **list, t_object *node);
void					*ft_object_free_node(t_object *node);

float					ft_modf(float v, float d);
double					ft_modd(double v, double d);
void					ft_env_clear(void);
char					*ft_pwd(void);
char					*ft_path_name(char *path);

extern int				ft_printf(const char *format, ...);

int						ft_isinset(const char c, const char *set);
size_t					ft_strcspn(const char *str, const char *reject);
size_t					ft_strspn(const char *str, const char *accept);

char					*ft_str_clear_commentaries(char *str);

# define FT_GLOBAL_MALLOC_STACK_SIZE (4 * MEM_M)
# define FT_GLOBAL_ATEND_STACK_SIZE 32
# define FT_STACK_LOOK 0
# define FT_STACK_PUT 1
# define FT_STACK_POP 2

t_pile					*ft_global_malloc_stack(void);
void					ft_final_free(void);
void					**ft_tab_block_alloc(size_t x, size_t y, size_t block);
t_pile					*ft_global_atend_stack(void);
int						ft_atend(void (*func)(void));
uint64_t				ft_str_to_id64(char *str);
double					ft_atod(const char *str);
int						ft_is_double(const char *str);
char					*ft_strmerge(char *a, char *b);
double					ft_clampd(double v, double min, double max);
int						ft_clampi(int v, int min, int max);
void					ft_swapd(double *p1, double *p2);
void					ft_swapi(int *p1, int *p2);

# define XORSHIFT1024STAR 1

# define RAND_MODE XORSHIFT1024STAR

unsigned long long		ft_xorshift1024star(void);
void					ft_srand(int seed);
t_xorshift1024star		*ft_global_xorshift1024star(void);
int						ft_rand(void);
char					*ft_dirname(char *path);
void					*ft_memrchr(const void *s, int c, size_t n);

# ifndef PATH_MAX

/*
** Posix-ly correct PATH_MAX (posix recommend at least 256)
*/

#  define PATH_MAX 1024
# endif

char					*ft_realpath(char *path, char resolved_path[PATH_MAX]);
char					*ft_path_clean_slashes(char *path);

void					*ft_reallocf(void *ptr, size_t size_original,
												size_t size_new);
void					ft_void(long long voidable_content);
void					ft_put_double_fd(double v, int precision, int fd);
void					ft_put_double(double v);
void					ft_putnbr_bin_fd(unsigned long nbr, int fd);
void					ft_putnbr_bin(unsigned long nbr);

#endif
