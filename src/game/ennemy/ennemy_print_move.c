/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_print_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:44:16 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 17:46:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_ennemies_move_empty(t_data *data, t_ennemy *tmp)
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

void	print_ennemy_on_exit_move(t_data *data, t_ennemy *ennemy)
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
	set_front_color_offset(&data->textures.exit[0], &combined);
	set_front_color(&data->textures.ennemies[ennemy->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		ennemy->next_coords.x * PIXEL_PADDING, ennemy->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	ennemy->coords = ennemy->next_coords;
	ennemy->next_coords = set_vector2(0, 0);
	data->game.is_exit_printed = 1;
}

void	print_ennemy_move(t_data *data, t_ennemy *ennemy)
{
	if ((ennemy->next_coords.y == data->window.exit.y
			&& ennemy->next_coords.x == data->window.exit.x)
		&& (data->game.game_finished == 1 || data->game.game_finished == 2))
		print_ennemy_on_exit_move(data, ennemy);
	else
		print_ennemies_move_empty(data, ennemy);
}
