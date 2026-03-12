/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:39:27 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:45:20 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_sword(t_data *data, t_sword *sword)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.sword[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		sword->coords.x * PIXEL_PADDING, sword->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	sword->is_printed = 1;
}

void	print_sword_move(t_data *data, t_sword *tmp)
{
	t_img	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].ptr, tmp->coords.x * PIXEL_PADDING,
		tmp->coords.y * PIXEL_PADDING);
	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.sword[tmp->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		tmp->next_coords.x * PIXEL_PADDING, tmp->next_coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	tmp->coords = tmp->next_coords;
	tmp->next_coords = set_vector2(0, 0);
	tmp->is_printed = 1;
}

void	is_sword_printed(t_data *data)
{
	t_sword	*sword;
	t_sword	*sword_next;

	sword = data->game.player.swords;
	while (sword)
	{
		sword_next = sword->next_sword;
		if (!sword->is_printed)
		{
			if (sword->next_coords.y || sword->next_coords.x)
				print_sword_move(data, sword);
			else
				print_sword(data, sword);
		}
		sword = sword_next;
	}
}
