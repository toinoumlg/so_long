/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/06 23:30:04 by amalangu         ###   ########.fr       */
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

int	handle_keys(int key_stroked, t_data *data)
{
	if ((key_stroked == 119 || key_stroked == 97 || key_stroked == 115
			|| key_stroked == 100))
		move_player(key_stroked, data);
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

int	update(t_data *data)
{
	struct timeval	current_time;
	const double	target_fps = 30.0;
	const double	frame_target = 1.0 / target_fps;

	gettimeofday(&current_time, NULL);
	data->timer.delta_time = (current_time.tv_sec
			- data->timer.last_frame.tv_sec) + (current_time.tv_usec
			- data->timer.last_frame.tv_usec) / 1000000.0;
	if (data->timer.delta_time >= frame_target)
	{
		data->frames++;
		data->timer.time += data->timer.delta_time;
		if (data->game.player.is_moving == 1)
			print_player(data);
		if (data->game.collectibles && data->frames % 4 == 0)
			update_collectibles(data);
		if (data->game.ennemies && data->frames % 4 == 0)
			update_ennemies(data);
		if (data->game.ennemies && data->frames % 30 == 0)
			update_logic(data);
		if (data->game.game_finished == 1)
			spawn_exit(data);
		if (data->game.game_finished == 3)
			return (mlx_loop_end(data->mlx), 0);
		data->timer.last_frame = current_time;
	}
	return (0);
}

void	init_game(t_data *data)
{
	data->timer.time = 0.0;
	gettimeofday(&data->timer.last_frame, NULL);
	data->game.player.moves = 0;
	data->frames = 0;
	data->window.move = set_vector2(0, 0);
	data->game.game_finished = 0;
	data->game.player.is_moving = 0;
	data->game.moves = set_move();
	data->mlx = mlx_init();
	set_textures(data);
	init_window(data->map, &data->window, data->mlx, data->textures);
	update_collectible_coords(data->game.collectibles, data->window.min);
	update_ennemies_coords(data->game.ennemies, data->window.min);
	mlx_set_font(data->mlx, data->window.ptr,
		"-urw-urw gothic l-demibold-r-normal--0-0-0-0-p-0-iso8859-15");
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
