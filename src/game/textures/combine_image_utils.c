/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_image_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:21:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/31 15:41:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

unsigned int	get_pixel_color(t_image *image, t_vector2 i)
{
	return (*(unsigned int *)(image->addr + (i.y * image->size_l + i.x
				* (image->bpp / 8))));
}

void	put_pixel(t_image *image, t_vector2 i, unsigned int color)
{
	char	*pixel;

	pixel = image->addr + (i.y * image->size_l + i.x * (image->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	print_front_or_back_offset(t_image *front, t_image *combined,
		t_vector2 i)
{
	t_vector2		offset;
	unsigned int	front_color;
	t_vector2		c_comb;

	offset = set_vector2(front->wh.y / 2, front->wh.x / 2);
	if ((i.x < offset.x || i.y < offset.y) || (i.x >= offset.x + front->wh.x
			|| i.y >= offset.y + front->wh.y))
	{
		front_color = get_pixel_color(combined, i);
		put_pixel(combined, i, front_color);
	}
	else
	{
		c_comb = set_vector2(i.y - offset.y, i.x - offset.x);
		front_color = get_pixel_color(front, c_comb);
		if ((front_color & 0xFF000000) == 0)
			put_pixel(combined, i, front_color);
	}
}

void	set_front_color_offset(t_image *front, t_image *combined)
{
	t_vector2	i;

	i.y = 0;
	while (i.y < combined->wh.y)
	{
		i.x = 0;
		while (i.x < combined->wh.x)
		{
			print_front_or_back_offset(front, combined, i);
			i.x++;
		}
		i.y++;
	}
}
