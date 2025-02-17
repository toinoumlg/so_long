/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:45:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:27:03 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update_index_collectibles(t_data *data)
{
	t_collectible	*collectible;

	collectible = data->game.collectibles;
	while (collectible)
	{
		if (collectible->i_image == 12)
			collectible->i_image = 0;
		collectible->i_image++;
		collectible = collectible->next_collectible;
	}
}

void	update_index_ennemies(t_data *data)
{
	t_ennemy	*ennemy;
	t_ennemy	*ennemy_next;

	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy_next = ennemy->next_ennemy;
		if (ennemy->got_hit && data->frames % 2 == 0)
		{
			if (ennemy->i_image++ < 15)
				ennemy->i_image = 15;
		}
		else if (!ennemy->got_hit && data->frames % 2 == 0)
		{
			if (ennemy->i_image++ == 4)
				ennemy->i_image = 0;
		}
		if (ennemy->i_image == 21)
			destroy_ennemy(&data->game.ennemies, ennemy->coords, data);
		ennemy = ennemy_next;
	}
}

void	update_index_swords(t_data *data)
{
	t_sword	*sword;

	sword = data->game.player.swords;
	while (sword)
	{
		if (sword->index == 3)
			sword->index = 0;
		sword->index++;
		sword = sword->next_sword;
	}
}

void	update_index_player(t_data *data)
{
	data->game.player.index++;
	if (data->game.player.index > 4)
		data->game.player.index = 0;
}

void	update_index(t_data *data)
{
	update_index_collectibles(data);
	update_index_ennemies(data);
	update_index_swords(data);
	update_index_player(data);
}
