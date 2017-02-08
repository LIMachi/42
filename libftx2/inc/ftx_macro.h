/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_macro.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:10:19 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 18:53:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTX_MACRO_H
# define FTX_MACRO_H

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

# if defined(__WINDOWS__)
#  define OS WINDOWS
# elif defined(__MACH__) || defined(__APPLE__)
#  define OS MACINTOCH
# elif defined (__FreeBSD__)
#  define OS FREEBSD
# else
#  define OS LINUX
# endif

# define GDX_NEW 1
# define GDX_FREE 2
# define GDX_ACCES 4

/*
** UNASCII is a 8 * 8 bmp used to print unrecognized characters
*/

# define UNASCII (0ll)

/*
** NOMASK is a mask set to full bites, so & operation with NOMASK on other mask
** should not modify the other mask
*/

# define NOMASK (!0ll)

# define CRSIZE 12

# define WHITE 0xFFFFFF
# define GRAY 0x777777
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define CIAN 0x00FFFF
# define YELLOW 0xFFFF00
# define MAGENTA 0xFF00FF

# if OS == LINUX
#  define KEYMAP_SIZE 65535
#  define KEY_EXIT 65307
#  define KEY_UP 65362
#  define KEY_LEFT 65361
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
#  define KEY_PAD_PLUS 65451
#  define KEY_PAD_MINUS 65453
#  define KEY_ENTER 65293
#  define KEY_PAD_0 65438
#  define KEY_CTRL_RIGHT 65508
#  define KEY_CTRL_LEFT 65507
#  define KEY_SPACE 32
#  define KEY_0 48
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_6 54
#  define KEY_7 55
#  define KEY_8 56
#  define KEY_9 57
#  define KEY_A 97
#  define KEY_B 98
#  define KEY_C 99
#  define KEY_D 100
#  define KEY_E 101
#  define KEY_F 102
#  define KEY_G 103
#  define KEY_H 104
#  define KEY_I 105
#  define KEY_J 106
#  define KEY_K 107
#  define KEY_L 108
#  define KEY_M 109
#  define KEY_N 110
#  define KEY_O 111
#  define KEY_P 112
#  define KEY_Q 113
#  define KEY_R 114
#  define KEY_S 115
#  define KEY_T 116
#  define KEY_U 117
#  define KEY_V 118
#  define KEY_W 119
#  define KEY_X 120
#  define KEY_Y 121
#  define KEY_Z 122
#  define KEY_SHIFT_LEFT 65505
#  define KEY_SHIFT_RIGHT 65506
# elif OS == MACINTOCH
#  define KEYMAP_SIZE 280
#  define KEY_PAD_PLUS 69
#  define KEY_PAD_MINUS 78
#  define KEY_CTRL_LEFT 256
#  define KEY_PAD_0 82
#  define KEY_B 11
#  define KEY_R 15
#  define KEY_L 37
#  define KEY_X 7
#  define KEY_Y 16
#  define KEY_Z 6
#  define KEY_P 35
#  define KEY_EXIT 53
#  define KEY_UP 126
#  define KEY_LEFT 123
#  define KEY_DOWN 125
#  define KEY_RIGHT 124
#  define KEY_SHIFT_LEFT 257
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_C 8
#  define KEY_H 4
#  define KEY_SPACE 49
#  define KEY_E 14
#  define KEY_Q 12
#  define KEY_I 34
# else
#  error "currently unsuported OS"
# endif

# define MICE_LEFT	1
# define MICE_CENTER 2
# define MICE_RIGHT 3
# define MICE_SCROLL_UP 4
# define MICE_SCROLL_DOWN 5

# define FTX_KEY_STATUS_PRESSED 1
# define FTX_KEY_STATUS_HOLD 2
# define FTX_KEY_STATUS_RELEASED 0
# define FTX_KEY_STATUS_DOUBLED 3

# define FTX_BUTTON 0
# define FTX_BUTTON_CLICK 1
# define FTX_BUTTON_MAINTAIN 2
# define FTX_BUTTON_TOGGLE 3
# define FTX_BUTTON_SLIDER 4
# define FTX_BUTTON_TEXT_BOX 5

# define FTX_DOUBLETAP_TICK 20

#endif
