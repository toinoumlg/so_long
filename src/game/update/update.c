/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:13:12 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:27:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update_entities(t_data *data)
{
	update_swords(data);
	update_ennemies(data);
}

void	update_frames(t_data *data)
{
	t_sword	*sword;

	if (data->game.player.attack_cd > 0)
		data->game.player.attack_cd--;
	data->frames++;
	data->timer.time += data->timer.delta_time;
	if (data->game.player.move_buffer > 0)
		data->game.player.move_buffer--;
	sword = data->game.player.swords;
	while (sword)
	{
		sword->sword_timer++;
		sword = sword->next_sword;
	}
}

void	reset_print(t_data *data)
{
	t_collectible	*collectible;
	t_ennemy		*ennemy;
	t_sword			*sword;

	collectible = data->game.collectibles;
	while (collectible)
	{
		collectible->is_printed = 0;
		collectible = collectible->next_collectible;
	}
	sword = data->game.player.swords;
	while (sword)
	{
		sword->is_printed = 0;
		sword = sword->next_sword;
	}
	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy->is_printed = 0;
		ennemy = ennemy->next_ennemy;
	}
}

void	get_current_time(t_data *data)
{
	gettimeofday(&data->timer.current_time, NULL);
	data->timer.delta_time = (data->timer.current_time.tv_sec
			- data->timer.last_frame.tv_sec) + (data->timer.current_time.tv_usec
			- data->timer.last_frame.tv_usec) / 1000000.0;
}

void	print_object_on_map(t_data *data)
{
	reset_print(data);
	is_collectible_printed(data);
	is_ennemy_printed(data);
	is_sword_printed(data);
	print_player(data);
}
