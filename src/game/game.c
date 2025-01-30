/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/30 15:28:51 by amalangu         ###   ########.fr       */
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

// int	handle_mouse(int button, int x, int y, t_data *data)
// {
// 	return (0);
// 	(void)data;
// }

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
	
	data->game.player.moves = 0;
	data->frames = 0;
	data->window.move.x = 0;
	data->window.move.y = 0;
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
	start_game(data);
	free_game(data);
}
