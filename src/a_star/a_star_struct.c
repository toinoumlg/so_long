/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 23:30:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_a_star(t_map *map, t_coords start, t_coords end,
		t_a_star_struct *a_star)
{
	a_star->start = start;
	a_star->end = end;
	a_star->closed_list = init_closed_list(map);
	a_star->cell_details = init_and_set_cell_details(start, map);
	a_star->open_list = init_list(0, start.x, start.y);
}

void	find_new_f(t_new_values new, t_coords actual, t_a_star_struct *a_star)
{
	new.g = a_star->cell_details[actual.y][actual.x].g + 1;
	new.h = calculate_new_h_value(new.parent.y, new.parent.x, a_star->end);
	new.f = new.g + new.h;
	if (a_star->cell_details[new.parent.y][new.parent.x].f == 100000
		|| a_star->cell_details[new.parent.y][new.parent.x].f >= new.f)
	{
		a_star->open_list = add_to_list(a_star->open_list, new.f, new.parent.y, new.parent.x);
		a_star->cell_details[new.parent.y][new.parent.x] = set_cell_details(new, actual);
	}
}

void	found_destination(t_coords new, t_coords actual,
		t_a_star_struct *a_star)
{
	a_star->cell_details[new.y][new.x].parent.x = actual.x;
	a_star->cell_details[new.y][new.x].parent.y = actual.y;
	a_star->found_end = 1;
}
