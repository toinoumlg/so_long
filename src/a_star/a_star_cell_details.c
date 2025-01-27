/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_cell_details.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:45:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/26 16:16:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_cell	set_cell_details(t_new_values new, t_coords coords)
{
	t_cell	cell_details;

	cell_details.f = new.f;
	cell_details.h = new.h;
	cell_details.g = new.g;
	cell_details.parent.x = coords.x;
	cell_details.parent.y = coords.y;
	return (cell_details);
}

t_cell	set_cells_detail_init(float fhg, int y, int x)
{
	t_cell			cell_details;
	t_new_values	new;
	t_coords		coords;

	new.f = fhg;
	new.h = fhg;
	new.g = fhg;
	coords.x = x;
	coords.y = y;
	cell_details = set_cell_details(new, coords);
	return (cell_details);
}

t_cell	**init_and_set_cell_details(t_coords start, t_map *map)
{
	t_coords	coords;
	t_cell		**cell_details;

	coords.y = 0;
	cell_details = ft_calloc(sizeof(t_cell *), map->height);
	while (coords.y < map->height)
		cell_details[coords.y++] = ft_calloc(sizeof(t_cell), map->width);
	coords.y = 0;
	while (coords.y < map->height)
	{
		coords.x = 0;
		while (coords.x < map->width)
			cell_details[coords.y][coords.x++] = set_cells_detail_init(100000,
					-1, -1);
		coords.y++;
	}
	cell_details[start.y][start.x] = set_cells_detail_init(0, start.y, start.x);
	return (cell_details);
}
