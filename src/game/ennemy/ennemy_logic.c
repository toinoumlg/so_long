/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:45:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_logic(t_vector2 start, t_vector2 end, t_a_star_struct *logic,
		t_data *data)
{
	logic->start = start;
	logic->end = end;
	logic->closed_list = init_closed_list(data->window.max);
	logic->cell_details = init_and_set_cell_details(start, data->window.max);
	logic->open_list = init_list(0, start.x, start.y);
}

t_vector2	get_next_coords(t_vector2 start, t_vector2 end, t_data *data)
{
	t_a_star_struct	logic;
	t_vector2		coords;

	init_logic(start, end, &logic, data);
	a_star_loop(&logic, data->window.screen, data->game.moves);
	coords = logic.cell_details[end.y][end.x].parent;
	free_a_star_search(logic, data->window.max.y);
	return (coords);
}

void	destroy_ennemy(t_ennemy **ennemies, t_vector2 coords, t_data *data)
{
	t_ennemy	*previous;
	t_ennemy	*ennemy;

	ennemy = *ennemies;
	if (ennemy->coords.x == coords.x && ennemy->coords.y == coords.y)
	{
		*ennemies = ennemy->next_ennemy;
		mlx_put_image_to_window(data->mlx, data->window.ptr,
			data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
			* PIXEL_PADDING);
		free(ennemy);
		return ;
	}
	while (ennemy != NULL && (ennemy->coords.x != coords.x
			|| ennemy->coords.y != coords.y))
	{
		previous = ennemy;
		ennemy = ennemy->next_ennemy;
	}
	previous->next_ennemy = ennemy->next_ennemy;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(ennemy);
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
		ennemy_list = ennemy_list->next_ennemy;
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
			ennemy->got_hit = 1;
		}
		sword = next_sword;
	}
}

void	update_ennemies(t_data *data)
{
	t_ennemy *ennemy;

	ennemy = data->game.ennemies;
	while (ennemy)
	{
		if (data->frames % 18 == 0 && !ennemy->got_hit)
		{
			ennemy->next_coords = get_next_coords(data->window.actual,
					ennemy->coords, data);
			did_get_hit(data, ennemy);
			is_ennemy_on_next(data, ennemy);
			if (ennemy->next_coords.y == data->window.actual.y
				&& ennemy->next_coords.x == data->window.actual.x)
			{
				ennemy->next_coords = set_vector2(0, 0);
				data->game.player.health--;
				if (data->game.player.health == 0)
				{
					data->game.game_finished = 3;
					if (data->game.collectibles)
						free_collectibles(data->game.collectibles);
					return ;
				}
			}
		}
		ennemy = ennemy->next_ennemy;
	}
}