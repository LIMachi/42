/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 13:50:07 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 01:17:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** return the path to the file passed in arg (no name, no extension)
** return NULL on error
** note: the path might be a file
** note: this function malloc his return
*/

char	*ft_path_get_path(const char *path)
{
	char *end;

	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strdup(path));
	if ((end = ft_strrchr(path, '/')) == NULL)
		return (ft_strdup(path));
	return (ft_strndup(path, (size_t)end - (size_t)path));
}

/*
** return the full name (no path, but extension) of the file path passed in arg,
** return NULL on error or invalid path (invalid path ends with '/')
** note: the file might be a directory
** note: this function malloc his return
*/

char	*ft_path_get_full_name(const char *path)
{
	char *start;

	if (path[ft_strlen(path) - 1] == '/')
		return (NULL);
	if ((start = ft_strrchr(path, '/')) == NULL)
		start = (char*)path;
	return (ft_strdup(start));
}

/*
** return the name (no path to file, no extension) of the file path passed in
** arg, return NULL on error or invalid path (invalid path ends with '/')
** note: the file might be a directory
** note: this function malloc his return
*/

char	*ft_path_get_name(const char *path)
{
	char	*out;
	char	*start;
	char	*end;
	int		i;

	start = NULL;
	end = NULL;
	i = ft_strlen(path);
	if (path[i - 1] == '/')
		return (NULL);
	while (--i && (start == NULL || end == NULL))
	{
		if (end == NULL && path[i] == '.')
			end = (char*)&path[i];
		if (start == NULL && path[i] == '/')
			start = (char*)&(path[i + 1]);
	}
	if (start == NULL)
		start = (char*)path;
	if (end != NULL)
		return (ft_strndup(start, (size_t)end - (size_t)start));
	return (ft_strdup(start));
}

/*
** return the number of first bytes of s that are not in reject
*/

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;
	int	l;

	l = ft_strlen(reject);
	i = -1;
	while (s[++i] && (j = -1))
		while (reject[++j])
			if (reject[j] == s[i])
				return (i);
	return (i);
}

/*
** return the number of first bytes of s that are in accept
*/

size_t	ft_strspn(const char *s, const char *accept)
{
	int	i;
	int	j;
	int	l;
	int	ok;

	l = ft_strlen(accept);
	i = -1;
	ok = 1;
	while (ok == 1 && s[++i] && (j = -1))
	{
		ok = 0;
		while (ok == 0 && accept[++j])
			if (accept[j] == s[i])
				ok = 1;
	}
	return (i);
}

/*
** first will parse src to a writable text file (will escape special chars) and
** store the parsed has a temporary file
** then will parse the temporary file into a 42's norm compliant function
** note: if the temporary or the dst file already exist, they will be replaced
** note: this function works byte by byte, so it's not compatible with non ascii
** text and might be slow on big files
*/

int	sf_write_escaped_char(int fd, char c)
{
	if (c == '\\')
		return (write(fd, "\\\\", 2));
	else if (c == '\n')
		return (write(fd, "\\n", 2));
	else if (c == '\t')
		return (write(fd, "\\t", 2));
	else if (c == '"')
		return (write(fd, "\\\"", 2));
	else
		return (write(fd, &c, 1));
}

#include <stdio.h>

int		sf_normalize0(int fd_dst, int *rd, int len, char *buff)
{
	int	lines;
	int	cw;
	int count;

	count = 34;
	lines = -1;
	while (*rd < len && ++lines < 24 && !(cw = 0))
	{
		count = 3 + write(fd_dst, "\twrite(fd, \"", 12);
		while (*rd < len && count < 73)
			if (++count && !(count >= 72 && buff[*rd] == '\\'))
			{
				write(fd_dst, &buff[*rd], 1);
				cw += 1 - (ft_strspn(&buff[*rd], "\\") % 2);
				++(*rd);
			}
		write(fd_dst, "\", ", 3);
		ft_putnbr_fd(cw, fd_dst);
		write(fd_dst, ");\n", 3);
	}
}

int		sf_normalize(int fd_dst, int fd_src, char function, int len)
{
	char	*buff;
	int		rd;

	buff = ft_malloc(len + 1);
	len = read(fd_src, buff, len);
	rd = 0;
	while (rd < len)
	{
		write(fd_dst, "inline static void\tsf_", 22);
		write(fd_dst, &function, 1);
		write(fd_dst, "(int fd)\n{\n", 11);
		++function;
		sf_normalize0(fd_dst, &rd, len, buff);
		if (rd < len)
		{
			write(fd_dst, "\tsf_", 4);
			write(fd_dst, &function, 1);
			write(fd_dst, "();\n}\n\n", 7);
		}
		else
			write(fd_dst, "}\n", 3);
	}
	ft_free(buff);
}

int		ft_file_to_normed_write_file(const char *dst, const char *src)
{
	int		fd1;
	int		fd2;
	char	name[1024];
	char	c;
	int		len;

	if (src == NULL || dst == NULL)
		return (-1);
	ft_bzero(name, 1024);
	ft_strncat(ft_strcat(ft_strncpy(name, src, 508), "->"), dst, 508);
	if ((fd1 = open(src, O_RDONLY)) == -1)
		return (-1);
	fd2 = open(ft_strcat(name, ".tmp"), O_CREAT | O_TRUNC | O_WRONLY, S_IDEFAULT);
	if (fd2 == -1)
		return (-1 + !0 * close(fd1));
	len = 0;
	while ((name[1023] = read(fd1, &c, 1)) == 1)
		len += sf_write_escaped_char(fd2, c);
	name[1023] |= close(fd1) | close(fd2);
	if (name[1023] == -1 || (fd2 = open(name, O_RDONLY)) == -1)
		return (-1);
	if ((fd1 = open(dst, O_CREAT | O_TRUNC | O_WRONLY, S_IDEFAULT)) == -1)
		return (-1 + !0 * close(fd2));
	sf_normalize(fd1, fd2, '0', len);
	return (close(fd1) | close(fd2));
}


int	main(int argc, char **argv)
{
	if (argc < 3)
		return (0);
	ft_file_to_normed_write_file(argv[2], argv[1]);
}


/*
int	ft_default_config_file(void);

int main()
{
	ft_default_config_file();
}
*/
