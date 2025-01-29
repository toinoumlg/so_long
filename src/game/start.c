/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 22:43:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_player(t_data *data)
{
	ft_printf("actual %d %d", data->window.);
	
	
}

int	handle_keys(int key_stroked, t_data *data)
{
	// ft_printf("keystroked %d !\n", key_stroked);
	if (key_stroked == 119 || key_stroked == 97 || key_stroked == 115
		|| key_stroked == 100)
		move_player(data);
	if (key_stroked == 65307)
		return (mlx_loop_end(data->mlx), 0);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	ft_printf("%d %d %d\n", button, x, y);
	(void)data;
	return (0);
}

int	on_exposure(t_data *data)
{
	(void)data;
	ft_printf("EXPOSED");
	return (0);
}

int	on_destroy(t_data *data)
{
	return (mlx_loop_end(data->mlx), 0);
}

int	update(t_data *data)
{
	(void)data;
	return (0);
}

void	game_loop(t_data data)
{
	mlx_mouse_hook(data.window.ptr, handle_mouse, &data);
	mlx_key_hook(data.window.ptr, handle_keys, &data);
	mlx_expose_hook(data.window.ptr, on_exposure, &data);
	mlx_hook(data.window.ptr, 17, 0, on_destroy, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
}

void	start(t_data data)
{
	set_textures(&data.textures, data.mlx);
	init_window(data.map, &data.window, data.mlx, data.textures);
	game_loop(data);
	free_game(data);
}
