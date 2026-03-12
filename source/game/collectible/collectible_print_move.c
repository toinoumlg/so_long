/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_print_move.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:14:22 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:43:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update_ennemy_collectible_print(t_ennemy *ennemy,
		t_collectible *collectible)
{
	ennemy->coords = ennemy->next_coords;
	ennemy->next_coords = set_vector2(0, 0);
	collectible->is_printed = 1;
	ennemy->is_printed = 1;
}

void	collectible_and_ennemy_move_print(t_data *data,
		t_collectible *collectible, t_ennemy *ennemy)
{
	t_img	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].ptr, ennemy->coords.x * PIXEL_PADDING,
		ennemy->coords.y * PIXEL_PADDING);
	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins[collectible->i_image],
		&combined);
	set_front_color(&data->textures.ennemies[ennemy->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		ennemy->next_coords.x * PIXEL_PADDING, ennemy->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	update_ennemy_collectible_print(ennemy, collectible);
}

void	collectible_and_sword_move_print(t_data *data,
		t_collectible *collectible, t_sword *sword)
{
	t_img	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].ptr, sword->coords.x * PIXEL_PADDING,
		sword->coords.y * PIXEL_PADDING);
	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins[collectible->i_image],
		&combined);
	set_front_color(&data->textures.sword[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		sword->next_coords.x * PIXEL_PADDING, sword->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	sword->coords = sword->next_coords;
	sword->next_coords = set_vector2(0, 0);
	collectible->is_printed = 1;
	sword->is_printed = 1;
}
