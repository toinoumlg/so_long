/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/13 18:45:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <pthread.h>

int	init_a_star(t_a_star *a_star)
{
	init_closed_list(a_star);
	init_and_set_cell_details(a_star);
	init_open_list(a_star);
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

int	has_a_lower_float(t_a_star_values **cell_details, t_a_star_values new)
{
	return (cell_details[new.coords.y][new.coords.x].f == __INT_MAX__
		|| cell_details[new.coords.y][new.coords.x].f > new.f);
}

void	find_new_f(t_a_star_values new, t_vector2 actual, t_a_star *a_star)
{
	t_open_list	*existing;
	float		weight;

	weight = 4;
	new.g = a_star->cell_details[actual.y][actual.x].g + 1;
	new.h = calculate_new_h_value(new.coords.y, new.coords.x, a_star->end);
	new.f = new.g + new.h *weight;
	existing = find_in_open_list(a_star->open_list, new.coords);
	if (!existing && has_a_lower_float(a_star->cell_details, new))
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

t_vector2_list	*set_new_vector2_list(t_vector2 coords)
{
	t_vector2_list	*new;

	new = malloc(sizeof(t_vector2_list));
	if (!new)
		pthread_exit(NULL);
	ft_memset(new, 0, sizeof(t_vector2_list));
	new->vector = set_vector2(coords.y, coords.x);
	return (new);
}

void	append_new_vector2_list(t_vector2_list **final_path,
		t_vector2_list *new)
{
	t_vector2_list	*tmp;
	t_vector2_list	*prev;

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

int	**set_final_path_list(t_a_star *a_star)
{
	t_vector2	tmp;
	int			**final_path;
	int			i;

	final_path = malloc(sizeof(int *) * (a_star->max.y + 1));
	ft_memset(final_path, 0, sizeof(int *) * (a_star->max.y + 1));
	i = 0;
	while (i <= a_star->max.y)
	{
		final_path[i] = malloc(sizeof(int) * (a_star->max.x + 1));
		ft_memset(final_path[i++], -1, sizeof(int) * (a_star->max.x + 1));
	}
	i = 0;
	while (!(a_star->cell_details[a_star->end.y][a_star->end.x].coords.x == a_star->end.x
			&& a_star->cell_details[a_star->end.y][a_star->end.x].coords.y == a_star->end.y))
	{
		final_path[a_star->end.y][a_star->end.x] = i;
		tmp = a_star->cell_details[a_star->end.y][a_star->end.x].coords;
		a_star->end = tmp;
		i++;
	}
	a_star->end = a_star->cell_details[a_star->end.y][a_star->end.x].coords;
	final_path[a_star->end.y][a_star->end.x] = i;
	return (final_path);
}

void	found_destination(t_vector2 new, t_vector2 actual, t_a_star *a_star)
{
	a_star->cell_details[new.y][new.x].coords = set_vector2(actual.y, actual.x);
	a_star->found_end = 1;
	a_star->final_path = set_final_path_list(a_star);
	pthread_exit(a_star);
}
