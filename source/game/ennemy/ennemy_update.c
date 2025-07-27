/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:45:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/13 12:34:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_vector2	get_next_coords(t_vector2 start, t_vector2 end)
{
	t_a_star	logic;
	t_vector2	coords;

	logic.start = start;
	logic.end = end;
	init_closed_list(&logic);
	init_and_set_cell_details(&logic);
	init_open_list(&logic);
	while (logic.open_list)
	{
		a_star_neighbor(&logic);
		if (logic.found_end)
			break ;
	}
	coords = logic.cell_details[end.y][end.x].coords;
	free_a_star_routine(&logic);
	return (coords);
}

void	is_ennemy_on_next(t_data *data, t_ennemy *ennemy)
{
	t_ennemy	*ennemy_list;

	ennemy_list = data->game.ennemies;
	while (ennemy_list)
	{
		if (ennemy_list->coords.y == ennemy->next_coords.y
			&& ennemy_list->coords.x == ennemy->next_coords.x)
		{
			ennemy->next_coords = set_vector2(0, 0);
			return ;
		}
		ennemy_list = ennemy_list->next;
	}
}

void	did_get_hit(t_data *data, t_ennemy *ennemy)
{
	t_sword	*sword;
	t_sword	*next_sword;

	sword = data->game.player.swords;
	while (sword)
	{
		next_sword = sword->next_sword;
		if ((sword->coords.x == ennemy->coords.x
				&& sword->coords.y == ennemy->coords.y)
			|| (sword->coords.y == ennemy->next_coords.y
				&& sword->coords.x == ennemy->next_coords.x))
		{
			destroy_sword(&data->game.player.swords, sword->coords, data);
			data->game.actual_sword--;
			print_hud_swords(data);
			ennemy->got_hit = 1;
		}
		sword = next_sword;
	}
}

int	is_ennemy_on_player(t_data *data, t_ennemy *ennemy)
{
	// if (ennemy->next_coords.y == data->window.actual.y
	// 	&& ennemy->next_coords.x == data->window.actual.x)
	// {
	// 	ennemy->next_coords = set_vector2(0, 0);
	// 	data->game.player.health--;
	// 	print_hud_health(data);
	// 	if (data->game.player.health == 0)
	// 		return (data->game.game_finished = 3, 1);
	// }
	(void)data;
	(void)ennemy;
	return (0);
}

void	update_ennemies(t_data *data)
{
	t_ennemy	*ennemy;

	ennemy = data->game.ennemies;
	(void)ennemy;
	// while (ennemy)
	// {
	// 	if (data->frames % 18 == 0 && !ennemy->got_hit)
	// 	{
	// 		ennemy->next_coords = get_next_coords(data->window.actual,
	// 				ennemy->coords);
	// 		did_get_hit(data, ennemy);
	// 		is_ennemy_on_next(data, ennemy);
	// 		if (is_ennemy_on_player(data, ennemy))
	// 			return ;
	// 	}
	// 	ennemy = ennemy->next;
	// }
}
