/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/30 02:41:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_actual_arrays(t_data *data)
{
	int	i;

	i = 0;
	ft_printf("actual %d %d\nscreen:\n", data->window.actual.x,
		data->window.actual.y);
	while (data->window.screen[i])
	{
		ft_printf("[%d]-%s\n", i, data->window.screen[i]);
		i++;
	}
}

void	update_screen_array(t_data *data)
{
	t_coords	new_coords;

	new_coords.x = data->window.actual.x + data->window.move.x;
	new_coords.y = data->window.actual.y + data->window.move.y;
	data->window.screen[data->window.actual.y][data->window.actual.x] = '0';
	if (data->window.screen[new_coords.y][new_coords.x] == 'C')
	{
		destroy_collectible(&data->game.collectibles, new_coords);
		if (!data->game.collectibles)
			data->game.game_finished = 1;
	}
	if ((new_coords.x == data->window.exit.x
			&& new_coords.y == data->window.exit.y)
		&& data->game.game_finished == 1)
		data->game.game_finished = 2;
	data->window.screen[new_coords.y][new_coords.x] = 'P';
	data->game.player_moves++;
	ft_printf("player move:%d\n", data->game.player_moves);
}

void	move_player(int key_stroked, t_data *data)
{
	if (key_stroked == 119)
		data->window.move = data->game.move.up;
	if (key_stroked == 97)
		data->window.move = data->game.move.left;
	if (key_stroked == 115)
		data->window.move = data->game.move.down;
	if (key_stroked == 100)
		data->window.move = data->game.move.right;
	if (data->window.screen[data->window.actual.y
		+ data->window.move.y][data->window.actual.x
		+ data->window.move.x] != '1')
		update_screen_array(data);
	else
		data->window.move = data->game.move.zero;
}

int	handle_keys(int key_stroked, t_data *data)
{
	if ((key_stroked == 119 || key_stroked == 97 || key_stroked == 115
			|| key_stroked == 100) && data->window.move.x == 0
		&& data->window.move.y == 0)
		move_player(key_stroked, data);
	if (key_stroked == 65307)
		return (free_collectibles(data->game.collectibles),
			mlx_loop_end(data->mlx), 0);
	return (0);
}

// int	handle_mouse(int button, int x, int y, t_data *data)
// {
// 	return (0);
// 	(void)data;
// }

int	on_destroy(t_data *data)
{
	return (free_collectibles(data->game.collectibles), mlx_loop_end(data->mlx),
		0);
}

void	update_collectibles(t_data *data)
{
	t_collectibles	*tmp;

	tmp = data->game.collectibles;
	while (tmp)
	{
		print_collectibles(data, tmp);
		tmp->i_image++;
		if (tmp->i_image > 12)
			tmp->i_image = 0;
		tmp = tmp->next_collectible;
	}
}

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
}

int	update(t_data *data)
{
	data->frames++;
	if ((data->window.move.x != 0 || data->window.move.y != 0) && data->frames
		% 1000 == 0)
		print_player(data);
	if (data->frames % 1300 == 0 && data->game.collectibles)
		update_collectibles(data);
	if (data->game.game_finished == 1)
		spawn_exit(data);
	if (data->game.game_finished == 2)
		return (mlx_loop_end(data->mlx), 0);
	return (0);
}

void	start_game(t_data data)
{
	mlx_hook(data.window.ptr, 2, (1L << 0), handle_keys, &data);
	// mlx_mouse_hook(data.window.ptr, handle_mouse, &data);
	// mlx_key_hook(data.window.ptr, handle_keys, &data);
	mlx_hook(data.window.ptr, 17, 0, on_destroy, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
}

void	init_game(t_data *data)
{
	data->game.player_moves = 0;
	data->frames = 0;
	data->window.move.x = 0;
	data->window.move.y = 0;
	data->game.game_finished = 0;
	data->game.move = set_move();
	set_textures(data);
	init_window(data->map, &data->window, data->mlx, data->textures);
	update_collectible_coords(data->game.collectibles, data->window.min);
}

void	game(t_data data)
{
	init_game(&data);
	start_game(data);
	free_game(data);
}
