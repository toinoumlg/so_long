/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_cell_details.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:45:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/12 10:05:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"
#include <pthread.h>

t_a_star_values	set_cell_details(t_a_star_values new, t_vector2 parents)
{
	t_a_star_values	cell_details;

	cell_details = new;
	cell_details.coords = set_vector2(parents.y, parents.x);
	return (cell_details);
}

void	set_new_cells_details(t_a_star_values *cell_details)
{
	cell_details->f = __INT_MAX__;
	cell_details->h = __INT_MAX__;
	cell_details->g = __INT_MAX__;
	cell_details->coords = set_vector2(-1, -1);
}

t_a_star_values	*set_new_cells(t_a_star *a_star)
{
	t_a_star_values	*new;

	new = malloc(sizeof(t_a_star_values) * (a_star->max.x + 1));
	if (!new)
		pthread_exit(a_star);
	memset(new, 0, sizeof(t_a_star_values) * (a_star->max.x + 1));
	return (new);
}

void	set_start_cell_details(t_a_star *a_star)
{
	t_a_star_values	*cell_details;

	cell_details = &a_star->cell_details[a_star->start.y][a_star->start.x];
	cell_details->coords = set_vector2(a_star->start.y, a_star->start.x);
	cell_details->f = 0;
	cell_details->h = 0;
	cell_details->f = 0;
}

void	init_and_set_cell_details(t_a_star *a_star)
{
	t_vector2	coords;

	coords.y = 0;
	a_star->cell_details = malloc(sizeof(t_a_star_values *) * (a_star->max.y
				+ 2));
	if (!a_star->cell_details)
		pthread_exit(a_star);
	memset(a_star->cell_details, 0, (sizeof(t_a_star_values *) * (a_star->max.y
				+ 2)));
	while (coords.y < a_star->max.y)
	{
		coords.x = 0;
		a_star->cell_details[coords.y] = set_new_cells(a_star);
		while (coords.x < a_star->max.x)
			set_new_cells_details(&a_star->cell_details[coords.y][coords.x++]);
		coords.y++;
	}
	set_start_cell_details(a_star);
}
