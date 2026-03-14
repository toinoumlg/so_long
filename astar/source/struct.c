/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:39:47 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:43:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar_internal.h"
#include "astar_struct.h"
#include "mem.h"
#include <math.h>

void	init_astar(t_astar *astar, t_thread_data *data)
{
	init_closed(astar, data);
	init_cells(astar, data);
	init_open(astar, data);
}

t_open	*find_in_open(t_open *open_list, t_vector2 *coords)
{
	while (open_list)
	{
		if (open_list->cell.coords.x == coords->x
			&& open_list->cell.coords.y == coords->y)
			return (open_list);
		open_list = open_list->next;
	}
	return (NULL);
}

int	has_a_lower_float(t_cell_astar **cells, t_cell_astar *new)
{
	return (cells[new->coords.y][new->coords.x].f == __FLT_NORM_MAX__
		|| cells[new->coords.y][new->coords.x].f > new->f);
}

float	calculate_new_h_value(int *y, int *x, t_vector2 *end)
{
	return (fabsf((float)*y - (float)end->y) + fabsf((float)*x
			- (float)end->x));
}

void	find_new_f(t_cell_astar *new, t_vector2 *actual, t_astar *astar,
		t_thread_data *data)
{
	t_open	*existing;
	float	weight;

	weight = 4;
	new->g = astar->cells[actual->y][actual->x].g + 1;
	new->h = calculate_new_h_value(&new->coords.y, &new->coords.x, &data->end);
	new->f = new->g + new->h *weight;
	existing = find_in_open(astar->open, &new->coords);
	if (!existing && has_a_lower_float(astar->cells, new))
	{
		add_to_open(&astar->open, new);
		astar->cells[new->coords.y][new->coords.x] = *new;
		astar->cells[new->coords.y][new->coords.x].coords = (t_vector2){actual->x,
			actual->y};
	}
	if (existing && (new->f < existing->cell.f))
	{
		existing->cell = *new;
		astar->cells[new->coords.y][new->coords.x].coords = (t_vector2){actual->x,
			actual->y};
	}
}

void	insert_vector2(t_vector2_list **final_path, t_vector2 value)
{
	t_vector2_list	*tmp;
	t_vector2_list	*new;
	t_vector2_list	*prev;

	new = ft_calloc(1, sizeof(t_vector2_list));
	new->value = value;
	if (!*final_path)
	{
		*final_path = new;
		return ;
	}
	tmp = *final_path;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	new->prev = prev;
	tmp->next = new;
}

t_vector2_list	*set_final_path_list(t_astar *astar, t_thread_data *data)
{
	t_vector2_list	*final_path;

	final_path = NULL;
	while (!(astar->cells[data->end.y][data->end.x].coords.x == data->end.x
			&& astar->cells[data->end.y][data->end.x].coords.y == data->end.y))
	{
		insert_vector2(&final_path,
			astar->cells[data->end.y][data->end.x].coords);
		data->end = astar->cells[data->end.y][data->end.x].coords;
	}
	return (final_path);
}

void	found_destination(t_vector2 *dest, t_vector2 *actual, t_astar *astar,
		t_thread_data *data)
{
	t_vector2_list	*final_path;

	astar->cells[dest->y][dest->x].coords = (t_vector2){actual->x, actual->y};
	final_path = set_final_path_list(astar, data);
	free_routine(astar, data);
	pthread_exit(final_path);
}
