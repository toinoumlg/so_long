/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:42:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

int	is_ennemy_on_next_coords(t_data *data, t_ennemy *ennemy)
{
	if ((ennemy->coords.y == data->window.actual.y
			+ data->game.player.move_dir.y)
		&& (ennemy->coords.x == data->window.actual.x
			+ data->game.player.move_dir.x))
		return (1);
	else
		return (0);
}

int	is_next_coords_blocked(t_data *data)
{
	if (data->window.screen[data->window.actual.y
			+ data->game.player.move_dir.y][data->window.actual.x
		+ data->game.player.move_dir.x] != '1')
		return (1);
	return (0);
}

void	set_player_direction(int key_stroked, t_data *data)
{
	if (key_stroked == 119)
		data->game.player.move_dir = data->game.moves.up;
	if (key_stroked == 97)
		data->game.player.move_dir = data->game.moves.left;
	if (key_stroked == 115)
		data->game.player.move_dir = data->game.moves.down;
	if (key_stroked == 100)
		data->game.player.move_dir = data->game.moves.right;
}
