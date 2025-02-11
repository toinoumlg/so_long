/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:55:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 15:35:35 by amalangu         ###   ########.fr       */
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
		}
		ennemy = ennemy->next_ennemy;
	}
}

void	is_sword_on_collectible(t_data *data, t_collectible *collectible)
{
	t_sword	*sword;
	t_sword	*sword_next;

	sword = data->game.player.swords;
	while (sword)
	{
		sword_next = sword->next_sword;
		if (sword->next_coords.y == collectible->coords.y
			&& sword->next_coords.x == collectible->coords.x)
			collectible_and_sword_move_print(data, collectible, sword);
		if (sword->coords.y == collectible->coords.y
			&& sword->coords.x == collectible->coords.x)
			collectible_and_sword_print(data, collectible, sword);
		sword = sword_next;
	}
}

void	is_sword_blocked(t_data *data, t_sword *sword)
{
	if (!is_blocked(data->window.screen, sword->next_coords))
	{
		sword->to_destroy = 1;
		data->game.actual_sword--;
	}
}

void	is_sword_ended(t_data *data, t_sword *sword)
{
	if (sword->sword_timer == 30)
	{
		sword->to_destroy = 1;
		data->game.actual_sword--;
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
