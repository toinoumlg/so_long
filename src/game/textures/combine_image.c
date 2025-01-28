/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:06:51 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 15:07:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

unsigned int	get_pixel_color(t_image *image, t_coords i)
{
	return (*(unsigned int *)(image->addr + (i.y * image->size_l + i.x
				* (image->bpp / 8))));
}

void	put_pixel(t_image *image, t_coords i, unsigned int color)
{
	char	*pixel;

	pixel = image->addr + (i.y * image->size_l + i.x * (image->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	set_background_color(t_image *background, t_image *combined)
{
	t_coords	i;

	i.y = 0;
	while (i.y < background->wh.y)
	{
		i.x = -1;
		while (i.x++ < background->wh.x)
			put_pixel(combined, i, get_pixel_color(background, i));
		i.y++;
	}
}

void	set_front_color(t_image *front, t_image *combined)
{
	unsigned int	front_color;
	t_coords		i;

	i.y = -1;
	while (i.y++ < front->wh.y)
	{
		i.x = -1;
		while (i.x++ < front->wh.x)
		{
			front_color = get_pixel_color(front, i);
			if ((front_color & 0xFF000000) == 0)
				put_pixel(combined, i, front_color);
		}
	}
}

void	combine_image(t_image front, t_image background, void *mlx,
		t_window window, t_coords i)
{
	t_image combined;

	combined.image = mlx_new_image(mlx, background.wh.x, background.wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = background.wh;
	set_background_color(&background, &combined);
	set_front_color(&front, &combined);
	mlx_put_image_to_window(mlx, window.ptr, combined.image, i.x
		* PIXEL_PADDING, i.y * PIXEL_PADDING);
	mlx_destroy_image(mlx, combined.image);
}