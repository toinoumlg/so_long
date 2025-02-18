/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 16:24:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_keys(int key_stroked, t_data *data)
{
	if (key_stroked == 65307)
		return (free_collectibles(data->game.collectibles),
			mlx_loop_end(data->mlx), 0);
	if (can_player_move(key_stroked, data))
		player_move(key_stroked, data);
	if (can_player_attack(key_stroked, data))
		player_attack(key_stroked, data);
	return (0);
}

int	on_destroy(t_data *data)
{
	return (free_collectibles(data->game.collectibles), mlx_loop_end(data->mlx),
		0);
}

int	update(t_data *data)
{
	get_current_time(data);
	if (data->timer.delta_time >= data->timer.frame_target)
	{
		update_frames(data);
		update_index(data);
		update_entities(data);
		if (data->game.game_finished == 3)
			return (mlx_loop_end(data->mlx), 0);
		print_object_on_map(data);
		if (data->frames % 12 == 0)
			print_hud_time(data);
		if (data->game.game_finished == 1)
			spawn_exit(data);
		data->timer.last_frame = data->timer.current_time;
	}
	return (0);
}

void	game(t_data data)
{
	init_game(&data);
	mlx_hook(data.window.ptr, 2, (1L << 0), handle_keys, &data);
	mlx_hook(data.window.ptr, 17, 0, on_destroy, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
	free_game(data);
}
