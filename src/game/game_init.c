/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:13:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:53:58 by amalangu         ###   ########.fr       */
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
	data->game.is_exit_printed = 0;
	data->game.moves = set_move();
}

void	init_hud(t_data *data)
{
	print_hud(data);
	print_hud_time(data);
	print_hud_move(data);
	print_hud_health(data);
	print_hud_swords(data);
}

int	init_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_collectibles(data->map->collectibles),
			free_ennemies(data->map->ennemies), free_map(data->map), -1);
	if (set_textures(data))
		return (free_failed_textures_init(*data), -1);
	set_timer(data);
	init_player(data);
	if (init_window(data->map, &data->window, data->mlx, data->textures))
		return (free_failed_window_init(*data), -1);
	update_collectible_coords(data->game.collectibles, data->window.min);
	update_ennemies_coords(data->game.ennemies, data->window.min);
	init_hud(data);
	return (0);
}
