/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:23:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 13:20:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_attack(int key_stroked, t_data *data)
{
	if (key_stroked == 65362)
		spawn_sword(data, data->game.moves.up);
	if (key_stroked == 65364)
		spawn_sword(data, data->game.moves.down);
	if (key_stroked == 65361)
		spawn_sword(data, data->game.moves.left);
	if (key_stroked == 65363)
		spawn_sword(data, data->game.moves.right);
}

void	player_move(int key_stroked, t_data *data)
{
	t_ennemy	*ennemy;

	ennemy = data->game.ennemies;
	if (key_stroked == 119)
		data->game.player.move_dir = data->game.moves.up;
	if (key_stroked == 97)
		data->game.player.move_dir = data->game.moves.left;
	if (key_stroked == 115)
		data->game.player.move_dir = data->game.moves.down;
	if (key_stroked == 100)
		data->game.player.move_dir = data->game.moves.right;
	if (data->window.screen[data->window.actual.y
		+ data->game.player.move_dir.y][data->window.actual.x
		+ data->game.player.move_dir.x] != '1')
	{
		while (ennemy)
		{
			if ((ennemy->coords.y == data->window.actual.y
					+ data->game.player.move_dir.y)
				&& (ennemy->coords.x == data->window.actual.x
					+ data->game.player.move_dir.x))
			{
				data->game.player.move_dir = data->game.moves.zero;
				return ;
			}
			ennemy = ennemy->next_ennemy;
		}
		update_screen_array(data);
	}
	else
		data->game.player.move_dir = data->game.moves.zero;
}

