/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:14:22 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:01:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	collectible_and_sword_print(t_data *data, t_collectible *collectible,
		t_sword *sword)
{
	t_img	combined;

	if (sword->next_coords.x || sword->next_coords.y)
	{
		print_collectibles(data, collectible);
		sword->coords = sword->next_coords;
		sword->next_coords = set_vector2(0, 0);
		print_sword(data, sword);
		return ;
	}
	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins[collectible->i_image],
		&combined);
	set_front_color_offset(&data->textures.sword[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		collectible->coords.x * PIXEL_PADDING, collectible->coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	sword->is_printed = 1;
	collectible->is_printed = 1;
}

void	collectible_and_ennemy_print(t_data *data, t_collectible *collectible,
		t_ennemy *ennemy)
{
	t_img	combined;

	if (ennemy->next_coords.x || ennemy->next_coords.y)
	{
		print_collectibles(data, collectible);
		ennemy->coords = ennemy->next_coords;
		ennemy->next_coords = set_vector2(0, 0);
		print_ennemies(data, ennemy);
		return ;
	}
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
		collectible->coords.x * PIXEL_PADDING, collectible->coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	ennemy->is_printed = 1;
	collectible->is_printed = 1;
}

void	print_collectibles(t_data *data, t_collectible *tmp)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		tmp->coords.x * PIXEL_PADDING, tmp->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	tmp->is_printed = 1;
}

void	is_collectible_printed(t_data *data)
{
	t_collectible	*collectible;

	collectible = data->game.collectibles;
	while (collectible)
	{
		is_ennemy_on_collectible(data, collectible);
		is_sword_on_collectible(data, collectible);
		if (!collectible->is_printed)
			print_collectibles(data, collectible);
		collectible = collectible->next;
	}
}
