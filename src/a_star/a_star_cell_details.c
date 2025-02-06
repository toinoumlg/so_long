/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_cell_details.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:45:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/06 23:16:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_cell	set_cell_details(t_new_values new, t_vector2 coords)
{
	t_cell	cell_details;

	cell_details.f = new.f;
	cell_details.h = new.h;
	cell_details.g = new.g;
	cell_details.parent = set_vector2(coords.y, coords.x);
	return (cell_details);
}

t_cell	set_cells_detail_init(float fhg, int y, int x)
{
	t_cell			cell_details;
	t_new_values	new;
	t_vector2		coords;

	new.f = fhg;
	new.h = fhg;
	new.g = fhg;
	coords = set_vector2(y, x);
	cell_details = set_cell_details(new, coords);
	return (cell_details);
}

t_cell	**init_and_set_cell_details(t_vector2 start, t_vector2 max)
{
	t_vector2	coords;
	t_cell		**cell_details;

	coords.y = 0;
	cell_details = ft_calloc(sizeof(t_cell *), max.y);
	while (coords.y < max.y)
		cell_details[coords.y++] = ft_calloc(sizeof(t_cell), max.x);
	coords.y = 0;
	while (coords.y < max.y)
	{
		coords.x = 0;
		while (coords.x < max.x)
			cell_details[coords.y][coords.x++] = set_cells_detail_init(100000,
					-1, -1);
		coords.y++;
	}
	cell_details[start.y][start.x] = set_cells_detail_init(0, start.y, start.x);
	return (cell_details);
}
