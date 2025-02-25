/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:55:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:22:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_vector2	sword_next_pos(t_sword *sword)
{
	t_vector2	next_pos;

	next_pos.y = sword->coords.y + sword->direction.y;
	next_pos.x = sword->coords.x + sword->direction.x;
	return (next_pos);
}

void	did_sword_hit_ennemy(t_data *data, t_sword *sword)
{
	t_ennemy	*ennemy;

	ennemy = data->game.ennemies;
	sword->next_coords = sword_next_pos(sword);
	while (ennemy)
	{
		if ((sword->next_coords.y == ennemy->coords.y
				&& sword->next_coords.x == ennemy->coords.x)
			|| (sword->coords.y == ennemy->coords.y
				&& sword->coords.x == ennemy->coords.x))
		{
			ennemy->got_hit = 1;
			sword->to_destroy = 1;
			data->game.actual_sword--;
			print_hud_swords(data);
		}
		ennemy = ennemy->next_ennemy;
	}
}

void	update_swords(t_data *data)
{
	t_sword	*sword;
	t_sword	*next_sword;

	sword = data->game.player.swords;
	while (sword)
	{
		next_sword = sword->next_sword;
		if (sword->sword_timer % 6 == 0)
		{
			did_sword_hit_ennemy(data, sword);
			is_sword_blocked(data, sword);
			is_sword_ended(data, sword);
		}
		if (sword->to_destroy)
			destroy_sword(&data->game.player.swords, sword->coords, data);
		sword = next_sword;
	}
}
