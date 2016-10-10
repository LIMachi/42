/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/11 02:19:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# if defined(__unix__) || defined(__unix) || defined(unix)
#  define UNIX 1
# endif

# define BIG_ENDIAN __ORDER_BIG_ENDIAN__
# define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
# define LOCAL_ENDIAN __BYTE_ORDER__

# define MACINTOCH 1
# define LINUX 2
# define FREEBSD 4

# if defined(__MACH__) || defined(__APPLE__)
#  define OS MACINTOCH
# elif defined (__FreeBSD__)
#  define OS FREEBSD
# else
#  define OS LINUX
# endif

# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>

/*
** OP is an optimisation flag to replace some code with macros
*/

/*
** # define OP
*/

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

/*
** trigonometrical defines
*/

# define PI (3.1415926535897932)
# define RADIAN(x) (PI * (((double)(x)) / (double)180))
# define DEGRE(x) ((double)180 * (((double)(x)) / PI))

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

typedef struct			s_point3d
{
	double				x;
	double				y;
	double				z;
}						t_point3d;

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
t_point3d				ft_point3d(double x, double y, double z);

/*
** trigonometrical related functions
*/

double					ft_sin(double x);
double					ft_cos(double x);
double					ft_tan(double x);

#endif
