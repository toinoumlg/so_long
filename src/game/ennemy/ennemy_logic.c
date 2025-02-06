/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:45:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/07 00:16:50 by amalangu         ###   ########.fr       */
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

void	update_logic(t_data *data)
{
	t_ennemy *tmp;
	t_vector2 coords;

	tmp = data->game.ennemies;
	while (tmp)
	{
		coords = tmp->coords;
		tmp->next_coords = get_next_coords(data->window.actual, coords, data);
		// update_logic_array(data->window.screen, coords, tmp->next_coords);
		tmp = tmp->next_ennemy;
	}
}