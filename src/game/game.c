/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 16:47:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_mouse(int button, int x, int y, t_data *data)
{
	return (0);
	(void)data;
	(void)y;
	(void)button;
	(void)x;
}

int	can_player_move(int key_stroked, t_data *data)
{
	if ((key_stroked == 119 || key_stroked == 97 || key_stroked == 115
			|| key_stroked == 100) && data->game.player.status == 0
		&& data->game.player.move_buffer == 0
		&& data->game.player.attack_cd == 0)
		return (1);
	else
		return (0);
}

int	can_player_attack(int key_stroked, t_data *data)
{
	if ((key_stroked == 65362 || key_stroked == 65364 || key_stroked == 65361
			|| key_stroked == 65363) && data->game.player.status == 0
		&& data->game.actual_sword < 2 && data->game.player.attack_cd == 0)
		return (1);
	else
		return (0);
}

int	handle_keys(int key_stroked, t_data *data)
{
	if (can_player_move(key_stroked, data))
		player_move(key_stroked, data);
	if (can_player_attack(key_stroked, data))
		player_attack(key_stroked, data);
	if (key_stroked == 65307)
		return (free_collectibles(data->game.collectibles),
			mlx_loop_end(data->mlx), 0);
	return (0);
}

int	on_destroy(t_data *data)
{
	return (free_collectibles(data->game.collectibles), mlx_loop_end(data->mlx),
		0);
}

void	reset_print(t_data *data)
{
	t_collectible	*collectible;
	t_ennemy		*ennemy;
	t_sword			*sword;

	collectible = data->game.collectibles;
	while (collectible)
	{
		collectible->is_printed = 0;
		collectible = collectible->next_collectible;
	}
	sword = data->game.player.swords;
	while (sword)
	{
		sword->is_printed = 0;
		sword = sword->next_sword;
	}
	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy->is_printed = 0;
		ennemy = ennemy->next_ennemy;
	}
}

void	print_object_on_map(t_data *data)
{
	reset_print(data);
	is_collectible_printed(data);
	is_ennemy_printed(data);
	is_sword_printed(data);
	print_player(data);
}


void	update_entities(t_data *data)
{
	update_swords(data);
	update_ennemies(data);
}

void	update_frames(t_data *data)
{
	t_sword	*sword;

	if (data->game.player.attack_cd > 0)
		data->game.player.attack_cd--;
	data->frames++;
	data->timer.time += data->timer.delta_time;
	if (data->game.player.move_buffer > 0)
		data->game.player.move_buffer--;
	sword = data->game.player.swords;
	while (sword)
	{
		sword->sword_timer++;
		sword = sword->next_sword;
	}
}

void	get_current_time(t_data *data)
{
	gettimeofday(&data->timer.current_time, NULL);
	data->timer.delta_time = (data->timer.current_time.tv_sec
			- data->timer.last_frame.tv_sec) + (data->timer.current_time.tv_usec
			- data->timer.last_frame.tv_usec) / 1000000.0;
}

int	update(t_data *data)
{
	get_current_time(data);
	if (data->timer.delta_time >= data->timer.frame_target)
	{
		update_frames(data);
		update_image_index(data);
		update_entities(data);
		if (data->game.game_finished == 3)
			return (mlx_loop_end(data->mlx), 0);
		print_object_on_map(data);
		if (data->frames % 4 == 0)
			print_move_string(data);
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
	mlx_mouse_hook(data.window.ptr, handle_mouse, &data);
	mlx_hook(data.window.ptr, 17, 0, on_destroy, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
	free_game(data);
}
