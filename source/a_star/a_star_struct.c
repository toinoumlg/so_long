/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/10 13:47:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	init_a_star(t_data *data, t_vector2 start, t_vector2 end, t_a_star *a_star)
{
	ft_memset(a_star, 0, sizeof(t_a_star));
	a_star->start = start;
	a_star->end = end;
	init_closed_list(a_star, data);
	init_and_set_cell_details(a_star, start, data);
	init_list(a_star, 0, start.x, start.y);
	return (0);
}

t_open_list	*find_in_open_list(t_open_list *open_list, t_vector2 coords)
{
	while (open_list)
	{
		if (open_list->values.coords.x == coords.x
			&& open_list->values.coords.y == coords.y)
			return (open_list);
		open_list = open_list->next;
	}
	return (NULL);
}

void	find_new_f(t_a_star_values new, t_vector2 actual, t_a_star *a_star)
{
	t_open_list	*existing;
	float		weight;

	weight = 4;
	new.g = (a_star->cell_details[actual.y][actual.x].g + 1);
	new.h = calculate_new_h_value(new.coords.y, new.coords.x, a_star->end);
	new.f = new.g + (new.h *weight);
	existing = find_in_open_list(a_star->open_list, new.coords);
	if (!existing
		&& (a_star->cell_details[new.coords.y][new.coords.x].f == __INT_MAX__
			|| a_star->cell_details[new.coords.y][new.coords.x].f > new.f))
	{
		add_to_list(&a_star->open_list, new);
		a_star->cell_details[new.coords.y][new.coords.x] = set_cell_details(new,
				actual);
	}
	if (existing && (new.f < existing->values.f))
	{
		existing->values = new;
		a_star->cell_details[new.coords.y][new.coords.x] = set_cell_details(new,
				actual);
	}
}

void	found_destination(t_vector2 new, t_vector2 actual, t_a_star *a_star)
{
	a_star->cell_details[new.y][new.x].coords = set_vector2(actual.y, actual.x);
	a_star->found_end = 1;
}
