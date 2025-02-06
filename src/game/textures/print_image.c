/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 00:08:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/07 00:13:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	spawn_exit(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.exit[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		data->window.exit.x * PIXEL_PADDING, data->window.exit.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	data->game.game_finished = 2;
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
}

void	print_ennemies_move(t_data *data, t_ennemy *tmp)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, tmp->coords.x * PIXEL_PADDING,
		tmp->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.ennemies[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->next_coords.x * PIXEL_PADDING, tmp->next_coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	tmp->coords = tmp->next_coords;
	tmp->next_coords = set_vector2(0, 0);
}

void	print_ennemies(t_data *data, t_ennemy *tmp)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.ennemies[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->coords.x * PIXEL_PADDING, tmp->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
}
