/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_details.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:39:32 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:43:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar_globals.h"
#include "astar_internal.h"
#include "astar_struct.h"
#include "mem.h"
#include <pthread.h>

static void	set_start_cell_details(t_astar *a_star, const t_thread_data *data)
{
	t_cell_astar	*cell;

	cell = &a_star->cells[data->start.y][data->start.x];
	cell->coords = (t_vector2){data->start.x, data->start.y};
	cell->f = 0.0f;
	cell->h = 0.0f;
	cell->g = 0.0f;
}

void	init_cells(t_astar *a_star, t_thread_data *data)
{
	int	y;
	int	x;

	y = 0;
	a_star->cells = ft_calloc(data->map_size->y + 1, sizeof(t_cell_astar *));
	if (!a_star->cells)
		exit_thread(a_star, data);
	while (y < data->map_size->y)
	{
		x = 0;
		a_star->cells[y] = ft_calloc(data->map_size->x, sizeof(t_cell_astar));
		if (!a_star->cells[y])
			exit_thread(a_star, data);
		while (x < data->map_size->x)
			a_star->cells[y][x++] = g_default_cell;
		y++;
	}
	set_start_cell_details(a_star, data);
}
