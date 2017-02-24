/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 04:38:17 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 16:09:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

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
