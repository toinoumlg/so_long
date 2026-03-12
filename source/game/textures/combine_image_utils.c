/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_image_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:21:17 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:48:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

unsigned int	get_pixel_color(t_img *image, t_vector2 i)
{
	return (image->addr[i.y * image->width + i.x]);
}

void	put_pixel(t_img *image, t_vector2 i, t_pxl color)
{
	image->addr[i.y * image->width + i.x] = color;
}

void	print_front_or_back_offset(t_img *front, t_img *combined, t_vector2 i)
{
	t_vector2		offset;
	unsigned int	front_color;
	t_vector2		c_comb;

	offset = set_vector2(front->height / 2, front->width / 2);
	if ((i.x < offset.x || i.y < offset.y) || (i.x >= offset.x + front->width
			|| i.y >= offset.y + front->height))
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

void	set_front_color_offset(t_img *front, t_img *combined)
{
	t_vector2	i;

	i.y = 0;
	while (i.y < combined->height)
	{
		i.x = 0;
		while (i.x < combined->width)
		{
			print_front_or_back_offset(front, combined, i);
			i.x++;
		}
		i.y++;
	}
}
