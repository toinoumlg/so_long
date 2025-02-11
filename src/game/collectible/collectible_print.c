/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:14:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 14:58:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	collectible_and_ennemy_move_print(t_data *data,
		t_collectible *collectible, t_ennemy *ennemy)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, ennemy->coords.x * PIXEL_PADDING,
		ennemy->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color(&data->textures.ennemies[ennemy->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		ennemy->next_coords.x * PIXEL_PADDING, ennemy->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	ennemy->coords = ennemy->next_coords;
	ennemy->next_coords = set_vector2(0, 0);
	collectible->is_printed = 1;
	ennemy->is_printed = 1;
}

void	collectible_and_sword_move_print(t_data *data,
		t_collectible *collectible, t_sword *sword)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, sword->coords.x * PIXEL_PADDING,
		sword->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color(&data->textures.player_axe[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		sword->next_coords.x * PIXEL_PADDING, sword->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	sword->coords = sword->next_coords;
	sword->next_coords = set_vector2(0, 0);
	collectible->is_printed = 1;
	sword->is_printed = 1;
}

void	collectible_and_sword_print(t_data *data, t_collectible *collectible,
		t_sword *sword)
{
	t_image	combined;

	if (sword->next_coords.x || sword->next_coords.y)
	{
		print_collectibles(data, collectible);
		sword->coords = sword->next_coords;
		sword->next_coords = set_vector2(0, 0);
		print_sword(data, sword);
		return ;
	}
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color_offset(&data->textures.player_axe[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		collectible->coords.x * PIXEL_PADDING, collectible->coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	sword->is_printed = 1;
	collectible->is_printed = 1;
}

void	collectible_and_ennemy_print(t_data *data, t_collectible *collectible,
		t_ennemy *ennemy)
{
	t_image	combined;

	if (ennemy->next_coords.x || ennemy->next_coords.y)
	{
		print_collectibles(data, collectible);
		ennemy->coords = ennemy->next_coords;
		ennemy->next_coords = set_vector2(0, 0);
		print_ennemies(data, ennemy);
		return ;
	}
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color(&data->textures.ennemies[ennemy->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		collectible->coords.x * PIXEL_PADDING, collectible->coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	ennemy->is_printed = 1;
	collectible->is_printed = 1;
}

void	print_collectibles(t_data *data, t_collectible *tmp)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->coords.x * PIXEL_PADDING, tmp->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	tmp->is_printed = 1;
}

void	is_collectible_printed(t_data *data)
{
	t_collectible *collectible;

	collectible = data->game.collectibles;
	while (collectible)
	{
		is_ennemy_on_collectible(data, collectible);
		is_sword_on_collectible(data, collectible);
		if (!collectible->is_printed)
			print_collectibles(data, collectible);
		collectible = collectible->next_collectible;
	}
}