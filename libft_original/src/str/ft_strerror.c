/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 15:07:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strerror(int error)
{
	static const char *strerror_ref[35] = {"No error",
		"Operation not permitted", "No such file or directory",
		"No such process", "Interrupted system call", "I/O error",
		"No such device or address", "Argument list too long",
		"Exec format error", "Bad file number", "No child processes",
		"Try again", "Out of memory", "Permission denied", "Bad address",
		"Block device required", "Device or resource busy", "File exists",
		"Cross-device link", "No such device", "Not a directory",
		"Is a directory", "Invalid argument", "File table overflow",
		"Too many open files", "Not a typewriter", "Text file busy",
		"File too large", "No space left on device", "Illegal seek",
		"Read-only file system", "Too many links", "Broken pipe",
		"Math argument out of domain of func", "Math result not representable"};

	if (error <= 34)
		return ((char*)strerror_ref[error]);
	else
		return ("Unknown error");
}
