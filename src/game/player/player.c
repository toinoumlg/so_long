/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:23:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:42:31 by amalangu         ###   ########.fr       */
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
	set_player_direction(key_stroked, data);
	if (is_next_coords_blocked(data))
	{
		while (ennemy)
		{
			if (is_ennemy_on_next_coords(data, ennemy))
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
