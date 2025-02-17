/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:42:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:46:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

int	set_sword_index(t_vector2 direction)
{
	if (direction.y == 1)
		return (1);
	if (direction.y == -1)
		return (3);
	if (direction.x == 1)
		return (0);
	if (direction.x == -1)
		return (2);
	return (0);
}

int	check_sword_on_collectible(t_sword *sword, t_collectible *collectible)
{
	while (collectible)
	{
		if (sword->coords.y == collectible->coords.y
			&& sword->coords.x == collectible->coords.x)
		{
			free(sword);
			return (1);
		}
		collectible = collectible->next_collectible;
	}
	return (0);
}
