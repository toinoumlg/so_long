/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:45:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/09 17:36:32 by amalangu         ###   ########.fr       */
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
	t_vector2		tmp;

	init_logic(start, end, &logic, data);
	a_star_loop(&logic, data->window.screen, data->game.moves);
	tmp = logic.cell_details[end.y][end.x].parent;
	free_a_star_search(logic, data->window.max.y);
	return (tmp);
}

void	destroy_ennemy(t_ennemy **ennemies, t_vector2 coords, t_data *data)
{
	t_ennemy	*previous;
	t_ennemy	*tmp;

	tmp = *ennemies;
	if (tmp->coords.x == coords.x && tmp->coords.y == coords.y)
	{
		*ennemies = tmp->next_ennemy;
		mlx_put_image_to_window(data->mlx, data->window.ptr,
			data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
			* PIXEL_PADDING);
		free(tmp);
		return ;
	}
	while (tmp != NULL && (tmp->coords.x != coords.x
			|| tmp->coords.y != coords.y))
	{
		previous = tmp;
		tmp = tmp->next_ennemy;
	}
	previous->next_ennemy = tmp->next_ennemy;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(tmp);
}

void	update_logic(t_data *data)
{
	t_ennemy *tmp;
	t_ennemy *next_ennemy;
	t_vector2 coords;

	tmp = data->game.ennemies;
	while (tmp)
	{
		next_ennemy = tmp->next_ennemy;
		coords = tmp->coords;
		tmp->next_coords = get_next_coords(data->window.actual, coords, data);
		ft_printf("%d %d\n", tmp->next_coords.y, tmp->next_coords.x);
		if (tmp->next_coords.y == data->window.actual.y
			&& tmp->next_coords.x == data->window.actual.x)
		{
			tmp->next_coords = set_vector2(0, 0);
			data->game.player.health--;
			ft_printf("curent health:%d\n", data->game.player.health);
			if (data->game.player.health == 0)
			{
				free_collectibles(data->game.collectibles);
				data->game.game_finished = 3;
				return ;
			}
		}
		tmp = next_ennemy;
	}
}