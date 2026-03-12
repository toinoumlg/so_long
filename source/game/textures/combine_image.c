/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:06:51 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:45:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_background_color(t_img *background, t_img *combined)
{
	t_vector2	i;

	i.y = 0;
	while (i.y < background->height)
	{
		i.x = -1;
		while (i.x++ < background->width)
			put_pixel(combined, i, get_pixel_color(background, i));
		i.y++;
	}
}

void	set_front_color(t_img *front, t_img *combined)
{
	unsigned int	front_color;
	t_vector2		i;

	i.y = -1;
	while (i.y++ < front->height)
	{
		i.x = -1;
		while (i.x++ < front->width)
		{
			front_color = get_pixel_color(front, i);
			if ((front_color & 0xFF000000) == 0 && i.x < front->lenght / 4
				&& i.y < front->lenght / 4)
				put_pixel(combined, i, front_color);
		}
	}
}

void	combine_image(t_img front, t_img background, void *mlx, t_window window)
{
	t_img	combined;

	(void)window;
	combined.ptr = mlx_new_image(mlx, background.width, background.height);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = background.width;
	combined.height = background.height;
	set_background_color(&background, &combined);
	set_front_color(&front, &combined);
	// mlx_put_img_to_window(mlx, window.ptr, combined.image, window.actual.x
	// 	* PIXEL_PADDING, window.actual.y * PIXEL_PADDING);
	mlx_destroy_image(mlx, combined.ptr);
}
