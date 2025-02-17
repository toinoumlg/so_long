/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:13:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 12:27:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_timer(t_data *data)
{
	double	target_fps;

	target_fps = 12.0;
	data->timer.frame_target = 1.0 / target_fps;
	data->timer.time = 0.0;
	gettimeofday(&data->timer.last_frame, NULL);
}

void	init_player(t_data *data)
{
	data->game.player.health = 3;
	data->game.player.move_buffer = 0;
	data->game.player.index = 0;
	data->game.player.status = 0;
	data->game.player.swords = NULL;
	data->game.player.moves = 0;
	data->game.player.attack_cd = 0;
	data->game.actual_sword = 0;
	data->frames = 0;
	data->game.game_finished = 0;
	data->game.moves = set_move();
}

void	init_game(t_data *data)
{
	data->mlx = mlx_init();
	init_player(data);
	set_timer(data);
	set_textures(data);
	init_window(data->map, &data->window, data->mlx, data->textures);
	update_collectible_coords(data->game.collectibles, data->window.min);
	update_ennemies_coords(data->game.ennemies, data->window.min);
	mlx_set_font(data->mlx, data->window.ptr,
		"-urw-urw gothic l-demibold-r-normal--0-0-0-0-p-0-iso8859-15");
	// print_move_string(data);
}
