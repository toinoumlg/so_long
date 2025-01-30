/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:06:51 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 22:41:57 by amalangu         ###   ########.fr       */
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

void	set_front_color_offset(t_image *front, t_image *combined)
{
	unsigned int	front_color;
	t_coords		i;
	t_coords		c_comb;
	t_coords		offset;

	offset.x = front->wh.x / 2;
	offset.y = front->wh.y / 2;
	i.y = 0;
	c_comb.y = 0;
	while (i.y < combined->wh.y)
	{
		c_comb.x = 0;
		i.x = 0;
		while (i.x < combined->wh.x)
		{
			if ((i.x < offset.x || i.y < offset.y) || (i.x >= offset.x
					+ front->wh.x || i.y >= offset.y + front->wh.y))
			{
				front_color = get_pixel_color(combined, i);
				put_pixel(combined, i, front_color);
			}
			else
			{
				c_comb.x = i.x - offset.x;
				c_comb.y = i.y - offset.y;
				front_color = get_pixel_color(front, c_comb);
				if ((front_color & 0xFF000000) == 0)
					put_pixel(combined, i, front_color);
			}
			i.x++;
		}
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
			if ((front_color & 0xFF000000) == 0 && i.x < front->size_l / 4
				&& i.y < front->size_l / 4)
				put_pixel(combined, i, front_color);
		}
	}
}

void	combine_image(t_image front, t_image background, void *mlx,
		t_window window)
{
	t_image	combined;

	combined.image = mlx_new_image(mlx, background.wh.x, background.wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = background.wh;
	set_background_color(&background, &combined);
	set_front_color(&front, &combined);
	mlx_put_image_to_window(mlx, window.ptr, combined.image, window.actual.x
		* PIXEL_PADDING, window.actual.y * PIXEL_PADDING);
	mlx_destroy_image(mlx, combined.image);
}
