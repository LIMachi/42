/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_print_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:50:25 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/21 02:43:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

inline static void	sf_bmp_print_info(t_bitmap *bmp)
{
	ft_putstr("\n\t\tMask red: ");
	ft_putnbr_hex(bmp->info.red_bmask);
	ft_putstr("\n\t\tMask green: ");
	ft_putnbr_hex(bmp->info.green_bmask);
	ft_putstr("\n\t\tMask blue: ");
	ft_putnbr_hex(bmp->info.blue_bmask);
	ft_putstr("\n\t\tMask alpha: ");
	ft_putnbr_hex(bmp->info.alpha_bmask);
	ft_putstr("\n\t\tColor space type: ");
	ft_putnbr(bmp->info.color_space_type);
	ft_putstr("\n\t\tGamma red: ");
	ft_putnbr_hex(bmp->info.gamma_red);
	ft_putstr("\n\t\tGamma green: ");
	ft_putnbr_hex(bmp->info.gamma_green);
	ft_putstr("\n\t\tGamma blue: ");
	ft_putnbr_hex(bmp->info.gamma_blue);
	ft_putstr("\n\t\tIntent: ");
	ft_putnbr(bmp->info.intent);
	ft_putstr("\n\t\tICC profile data: ");
	ft_putnbr(bmp->info.icc_profile_data);
	ft_putstr("\n\t\tICC profile size: ");
	ft_putnbr(bmp->info.icc_profile_size);
	ft_putchar('\n');
}

void				ft_bmp_print_info(t_bitmap *bmp)
{
	if (bmp == NULL)
		ft_error(EINVAL, "ft_bmp_print_info got NULL\n");
	ft_putstr("Bitmap info:\n\tDIB Header:\n\t\tDIB Size: ");
	ft_putnbr(bmp->info.dib_size);
	ft_putstr("\n\t\tImage size (pixels): ");
	ft_putnbr(bmp->info.width);
	ft_putstr(", ");
	ft_putnbr(bmp->info.height);
	ft_putstr("\n\t\tPlanes: ");
	ft_putnbr(bmp->info.planes);
	ft_putstr("\n\t\tBit count: ");
	ft_putnbr(bmp->info.bit_count);
	ft_putstr("\n\t\tBit compression: ");
	ft_putnbr(bmp->info.bit_compression);
	ft_putstr("\n\t\tImage size (bytes): ");
	ft_putnbr(bmp->info.size_image);
	ft_putstr("\n\t\tPixels per meter: ");
	ft_putnbr(bmp->info.x_pixels_meter);
	ft_putstr(", ");
	ft_putnbr(bmp->info.y_pixels_meter);
	ft_putstr("\n\t\tColors in table: ");
	ft_putnbr(bmp->info.colors_in_tab);
	ft_putstr("\n\t\tImportant colors: ");
	ft_putnbr(bmp->info.color_important);
	sf_bmp_print_info(bmp);
}
