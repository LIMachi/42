/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 00:13:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** global error function used in most of my ft_functions and programs.
** used like errno, but can also store strings to print detailed errors.
** note: this do not use any exit() or stop() or break(), you might have to
** stop your program with the calling of if (ft_error(FT_ERROR_CHECK)) return;
*/

/*
** list of flags:
**	FT_ERROR_CHECK: return 0 on no error, or a non null value for error stored
**					if data is set, will only check the error code of data
**	FT_ERROR_SET: uses data to set the global error
**	FT_ERROR_CLEAR: discard the last error (set it to 0)
**	FT_ERROR_PRINT: print the error and return the error code, if there is
**					if data is set, will only print the error if the stored
**					error is equal to data
**	FT_ERROR_ERRNO: catch the errno and store it, if there is a code, print it,
**	and return it
*/

#if 0
static const char *g_errno_str[256] = {
	[EPERM] = "Operation not permitted", [ESRCH] = "No such process",
	[ENOENT] = "No such file or directory", [EIO] = "I/O error",
	[EINTR] = "Interrupted system call", [ENOEXEC] = "Exec format error",
	[ENXIO] = "No such device or address", [EBADF] = "Bad file number",
	[E2BIG] = "Argument list too long", [ECHILD] = "No child processes",
	[EAGAIN] = "Try again", [ENOMEM] = "Out of memory",
	[EFAULT] = "Bad address", [EBUSY] = "Device or resource busy",
	[ENOTBLK] = "Block device required", [EACCES] = "Permission denied",
	[EEXIST] = "File exists", [EXDEV] = "Cross-device link",
	[ENODEV] = "No such device", [ENOTDIR] = "Not a directory",
	[EISDIR] = "Is a directory", [EINVAL] = "Invalid argument",
	[ENFILE] = "File table overflow", [EMFILE] = "Too many open files",
	[ENOTTY] = "Not a typewriter", [ETXTBSY] = "Text file busy",
	[EFBIG] = "File too large", [ENOSPC] = "No space left on device",
	[ESPIPE] = "Illegal seek", [EROFS] = "Read-only file system",
	[EMLINK] = "Too many links", [EPIPE] = "Broken pipe",
	[EDOM] = "Math argument out of domain of func",
	[ERANGE] = "Math result not representable",
	[EDEADLK] = "Resource deadlock would occur",
	[ENAMETOOLONG] = "File name too long",
	[ENOLCK] = "No record locks available",
	[ENOSYS] = "Invalid system call number",
	[ENOTEMPTY] = "Directory not empty",
	[ELOOP] = "Too many symbolic links encountered",
//	[EWOULDBLOCK] = "Operation would block",
	[ENOMSG] = "No message of desired type",
	[EIDRM] = "Identifier removed",
	[ECHRNG] = "Channel number out of range",
	[EL2NSYNC] = "Level 2 not synchronized",
	[EL3HLT] = "Level 3 halted",
	[EL3RST] = "Level 3 reset",
	[ELNRNG] = "Link number out of range",
	[EUNATCH] = "Protocol driver not attached",
	[ENOCSI] = "No CSI structure available",
	[EL2HLT] = "Level 2 halted",
	[EBADE] = "Invalid exchange",
	[EBADR] = "Invalid request descriptor",
	[EXFULL] = "Exchange full",
	[ENOANO] = "No anode",
	[EBADRQC] = "Invalid request code",
	[EBADSLT] = "Invalid slot",
//	[EDEADLOCK] = "Resource deadlock would occur",
	[EBFONT] = "Bad font file format",
	[ENOSTR] = "Device not a stream",
	[ENODATA] = "No data available",
	[ETIME] = "Timer expired",
	[ENOSR] = "Out of streams resources",
	[ENONET] = "Machine is not on the network",
	[ENOPKG] = "Package not installed",
	[EREMOTE] = "Object is remote",
	[ENOLINK] = "Link has been severed",
	[EADV] = "Advertise error",
	[ESRMNT] = "Srmount error",
	[ECOMM] = "Communication error on send",
	[EPROTO] = "Protocol error",
	[EMULTIHOP] = "Multihop attempted",
	[EDOTDOT] = "RFS specific error",
	[EBADMSG] = "Not a data message",
	[EOVERFLOW] = "Value too large for defined data type",
	[ENOTUNIQ] = "Name not unique on network",
	[EBADFD] = "File descriptor in bad state",
	[EREMCHG] = "Remote address changed",
	[ELIBACC] = "Can not access a needed shared library",
	[ELIBBAD] = "Accessing a corrupted shared library",
	[ELIBSCN] = ".lib section in a.out corrupted",
	[ELIBMAX] = "Attempting to link in too many shared libraries",
	[ELIBEXEC] = "Cannot exec a shared library directly",
	[EILSEQ] = "Illegal byte sequence",
	[ERESTART] = "Interrupted system call should be restarted",
	[ESTRPIPE] = "Streams pipe error",
	[EUSERS] = "Too many users",
	[ENOTSOCK] = "Socket operation on non-socket",
	[EDESTADDRREQ] = "Destination address required",
	[EMSGSIZE] = "Message too long",
	[EPROTOTYPE] = "Protocol wrong type for socket",
	[ENOPROTOOPT] = "Protocol not available",
	[EPROTONOSUPPORT] = "Protocol not supported",
	[ESOCKTNOSUPPORT] = "Socket type not supported",
	[EOPNOTSUPP] = "Operation not supported on transport endpoint",
	[EPFNOSUPPORT] = "Protocol family not supported",
	[EAFNOSUPPORT] = "Address family not supported by protocol",
	[EADDRINUSE] = "Address already in use",
	[EADDRNOTAVAIL] = "Cannot assign requested address",
	[ENETDOWN] = "Network is down",
	[ENETUNREACH] = "Network is unreachable",
	[ENETRESET] = "Network dropped connection because of reset",
	[ECONNABORTED] = "Software caused connection abort",
	[ECONNRESET] = "Connection reset by peer",
	[ENOBUFS] = "No buffer space available",
	[EISCONN] = "Transport endpoint is already connected",
	[ENOTCONN] = "Transport endpoint is not connected",
	[ESHUTDOWN] = "Cannot send after transport endpoint shutdown",
	[ETOOMANYREFS] = "Too many references: cannot splice",
	[ETIMEDOUT] = "Connection timed out",
	[ECONNREFUSED] = "Connection refused",
	[EHOSTDOWN] = "Host is down",
	[EHOSTUNREACH] = "No route to host",
	[EALREADY] = "Operation already in progress",
	[EINPROGRESS] = "Operation now in progress",
	[ESTALE] = "Stale file handle",
	[EUCLEAN] = "Structure needs cleaning",
	[ENOTNAM] = "Not a XENIX named type file",
	[ENAVAIL] = "No XENIX semaphores available",
	[EISNAM] = "Is a named type file",
	[EREMOTEIO] = "Remote I/O error",
	[EDQUOT] = "Quota exceeded",
	[ENOMEDIUM] = "No medium found",
	[EMEDIUMTYPE] = "Wrong medium type",
	[ECANCELED] = "Operation Canceled",
	[ENOKEY] = "Required key not available",
	[EKEYEXPIRED] = "Key has expired",
	[EKEYREVOKED] = "Key has been revoked",
	[EKEYREJECTED] = "Key was rejected by service",
	[EOWNERDEAD] = "Owner died",
	[ENOTRECOVERABLE] = "State not recoverable",
	[ERFKILL] = "Operation not possible due to RF-kill",
	[EHWPOISON] = "Memory page has hardware error",
};
#endif

int	ft_error(int flag, int data)
{
	static int	error = 0;

	if (flag == FT_ERROR_SET)
		error = data;
	if (flag == FT_ERROR_ERRNO)
		error = errno;
	if (flag == FT_ERROR_CLEAR)
		error = 0;
//	if ((flag == FT_ERROR_PRINT || flag == FT_ERROR_ERRNO) && error)
//		ft_putendl_fd(g_errno_str[error], 2);
	if (flag == FT_ERROR_CHECK || flag == FT_ERROR_PRINT ||
			flag == FT_ERROR_ERRNO)
		return (error);
	return (0);
}
