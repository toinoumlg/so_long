/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:17:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 16:09:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_player_idle(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.player[data->game.player.index],
		&combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		data->window.actual.x * PIXEL_PADDING, data->window.actual.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_player_moving(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.player[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, data->window.actual.x * PIXEL_PADDING,
		data->window.actual.y * PIXEL_PADDING);
	data->window.actual.y += data->game.player.move_dir.y;
	data->window.actual.x += data->game.player.move_dir.x;
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		data->window.actual.x * PIXEL_PADDING, data->window.actual.y
		* PIXEL_PADDING);
	data->game.player.status = 0;
	data->game.player.moves++;
	print_hud_move(data);
	data->game.player.move_buffer = 3;
	data->game.player.move_dir = data->game.moves.zero;
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_player(t_data *data)
{
	if (data->game.player.status == 1)
		print_player_moving(data);
	if (data->game.player.status == 0 && data->frames % 2 == 0)
		print_player_idle(data);
}
