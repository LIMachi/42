/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 04:38:17 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 11:35:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

/*
** a button is an interactive immage (can be clicked, toggle, holded, slided,
** etc)
*/

/*
** s_button (type = 0, unknown button type) is a cast to get common values from
** any type of button and easily race a multi-type linked list of buttons (note
** that the more buttons there is in a window, the longer will the update be)
*/

#define BUTTON 0
typedef struct	s_button
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	struct s_button		*prev_button;
	struct s_button		*next_button;
}				t_button;

/*
** t_button_click (type = 1) send an update to trigger when released
*/

#define BUTTON_CLICK 1
typedef struct	s_button_click
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*released;
	t_ubmp				*hover;
	t_ubmp				*click;
	t_int_func_undef	trigger;
}				t_button_click;

/*
** t_button_maintain (type = 2) send an update to trigger has long has it is
** maintained
*/

#define BUTTON_MAINTAIN 2
typedef struct	s_button_maintain
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*released;
	t_ubmp				*hover;
	t_ubmp				*maintained;
	t_int_func_undef	trigger;
}				t_button_maintain;

/*
** t_button_toggle (type = 3) change state when released and send an update to
** the corresponding function for his new state
*/

#define BUTTON_TOGGLE 3
typedef struct	s_button_toggle
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*off;
	t_ubmp				*hover_off;
	t_ubmp				*hover_on;
	t_ubmp				*on;
	uint8_t				state;
	t_int_func_undef	toggled_on;
	t_int_func_undef	toggled_off;
}				t_button_toggle;

/*
** t_button_slider (type = 4) whil triger slider_moved if a click or maintained
** slide is made in his hitbox and will send the position of the slider to
** slider_moved
*/

#define BUTTON_SLIDER 4
typedef struct	s_button_slider
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*back;
	t_ubmp				*slider;
	uint8_t				constraints;
	t_point				slider_position;
	t_int_func_undef	slider_moved;
}				t_button_slider;

/*
** t_button_text_box (type = 5) is particular, it will catch keyboard updates
** and write the input to a box, waiting to get an "enter key" signal to send
** the stored text to his function. a click update will change the position
** of the cursor, and so the way the text is input
*/

#define BUTTON_TEXT_BOX 5
typedef struct	s_button_text_box
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*back;
	t_ubmp				*back_hover;
//	t_font				*font;
	char				*str;
	char				cursor_symbol;
	uint32_t			color;
	t_point				cursor_position;
	uint32_t			max_text;
	t_int_func_undef	get_text;
}				t_button_text_box;

/*
** ftx_new_button will create a new button of any type (don't be fooled by the
** return type), and set his position and hitbox (position is relative to the
** top left of the window storing the button, and hitbox is relative to the top
** left of the position, so both position and hitbox should have positive x and
** y values), type should be set via macros (more secured)
** will return NULL in case of error (either malloc error or invalid parameter)
*/

t_button	*ftx_new_button(const uint8_t type, const t_point position,
							const t_point hitbox, const t_button *prev_button)
{
	size_t		size;
	t_button	*out;

	size = 0;
	if (type == BUTTON_CLICK)
		size = sizeof(t_button_click);
	if (type == BUTTON_MAINTAIN)
		size = sizeof(t_button_maintain);
	if (type == BUTTON_TOGGLE)
		size = sizeof(t_button_toggle);
	if (type == BUTTON_SLIDER)
		size = sizeof(t_button_slider);
	if (type == BUTTON_TEXT_BOX)
		size = sizeof(t_button_text_box);
	if (size == 0 || (out = (t_button*)ft_malloc(size)) == NULL)
		return (NULL);
	*(uint8_t*)(&out->type) = type;
	out->position = position;
	out->hitbox = hitbox;
	out->prev_button = (t_button*)prev_button;
	out->next_button = NULL;
	return (out);
}

/*
** will link the button before and after the on passed in, eventually free the
** string hold by t_button_text_box and then free the button itself
*/

void		*ftx_free_button(t_button *button)
{
	if (button->prev_button)
		button->prev_button->next_button = button->next_button;
	if (button->next_button)
		button->next_button->prev_button = button->prev_button;
	if (button->type == BUTTON_TEXT_BOX &&
			((t_button_text_box*)button)->str != NULL)
		(void)ft_free(((t_button_text_box*)button)->str);
	return (ft_free(button));
}
