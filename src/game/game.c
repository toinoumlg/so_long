/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/04 17:37:50 by amalangu         ###   ########.fr       */
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
			|| key_stroked == 100) && data->game.player.is_moving == 0)
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
	data->frames++;
	data->timer.end = clock();
	data->timer.time += (double)(data->timer.end - data->timer.start)
		/ CLOCKS_PER_SEC;
	printf("%f\n", data->timer.time);
	data->timer.start = clock();
	if ((data->game.player.is_moving == 1) && data->frames % 5000 == 0)
		print_player(data);
	if (data->frames % 1300 == 0 && data->game.collectibles)
		update_collectibles(data);
	if (data->game.game_finished == 1)
		spawn_exit(data);
	if (data->game.game_finished == 3)
		return (mlx_loop_end(data->mlx), 0);
	return (0);
}

void	init_game(t_data *data)
{
	data->timer.time = 0;
	data->timer.start = clock();
	data->game.player.moves = 0;
	data->frames = 0;
	data->window.move = set_vector2(0, 0);
	data->game.game_finished = 0;
	data->game.player.is_moving = 0;
	data->game.moves = set_move();
	set_textures(data);
	init_window(data->map, &data->window, data->mlx, data->textures);
	update_collectible_coords(data->game.collectibles, data->window.min);
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
