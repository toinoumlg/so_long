/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_cell_details.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:45:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/09 18:42:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

t_a_star_values	set_cell_details(t_a_star_values new, t_vector2 coords)
{
	t_a_star_values	cell_details;

	cell_details.f = new.f;
	cell_details.h = new.h;
	cell_details.g = new.g;
	cell_details.coords = set_vector2(coords.y, coords.x);
	return (cell_details);
}

t_a_star_values	set_cells_detail_init(float fhg, int y, int x)
{
	t_a_star_values	cell_details;
	t_a_star_values	new;
	t_vector2		coords;

	new.f = fhg;
	new.h = fhg;
	new.g = fhg;
	coords = set_vector2(y, x);
	cell_details = set_cell_details(new, coords);
	return (cell_details);
}

t_a_star_values	*set_new_cell(t_data *data, t_a_star *a_star)
{
	t_a_star_values	*new;

	new = malloc(sizeof(t_a_star_values) * (data->map.max.x + 1));
	if (!new)
		exit(pathfinding_error(a_star, data, ALLOC_ERROR));
	memset(new, 0, sizeof(t_a_star_values));
	return (new);
}

void	init_and_set_cell_details(t_a_star *a_star, t_vector2 start,
		t_data *data)
{
	t_vector2	coords;
	t_vector2	max;

	max = data->map.max;
	coords.y = 0;
	a_star->cell_details = malloc(sizeof(t_a_star_values *) * (max.y) + 1);
	if (!a_star->cell_details)
		exit(pathfinding_error(a_star, data, ALLOC_ERROR));
	while (coords.y < max.y)
	{
		coords.x = 0;
		a_star->cell_details[coords.y] = set_new_cell(data, a_star);
		while (coords.x < max.x)
			a_star->cell_details[coords.y][coords.x++] = set_cells_detail_init(__INT_MAX__,
					-1, -1);
		coords.y++;
	}
	a_star->cell_details[start.y][start.x] = set_cells_detail_init(0, start.y,
			start.x);
}
