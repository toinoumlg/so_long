/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:42:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_colors.h"
#include "so_long.h"

int	print_end(t_data data)
{
	if (data.game.player.health == 0)
		return (ft_putstr_fd(RED "Player is dead!\n" RESET, 1), 0);
	if (data.game.game_finished == 3)
		return (ft_putstr_fd(GREEN "Player won!\n" RESET, 1), 0);
	if (data.game.game_finished != 3)
		return (ft_putstr_fd(MAGENTA "Game aborted\n" RESET, 1), 0);
	return (-1);
}

int	on_destroy(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
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
		data->timer.last_frame = data->timer.current_time;
	}
	return (0);
}

// void	start_game(t_data data)
// {
// 	mlx_hook(data.window.ptr, 17, 0, on_destroy, &data);
// 	mlx_hook(data.window.ptr, 2, (1L << 0), handle_keys, &data);
// 	mlx_loop_hook(data.mlx, update, &data);
// 	mlx_loop(data.mlx);
// 	print_end(data);
// 	free_game(data);
// }
