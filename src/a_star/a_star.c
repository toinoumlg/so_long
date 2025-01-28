/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 16:26:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	trace_path(t_cell **cell_details, t_coords end, char found)
{
	if (!found)
		return (-1);
	else
		test_print_final_path(cell_details, end);
	return (0);
}

void	a_star_neighbor(t_a_star_struct *a_star, t_map *map)
{
	t_coords		possible_direction;
	t_coords		actual;
	int				i;
	t_new_values	new;

	i = 0;
	actual = a_star->first->coords;
	a_star->closed_list[actual.y][actual.x] = 0;
	free(a_star->first);
	while (i < 4)
	{
		possible_direction = map->possible_directions[i];
		new.y = actual.y + possible_direction.y;
		new.x = actual.x + possible_direction.x;
		if (is_destination(new.y, new.x, a_star->end))
			return (found_destination(new, actual, a_star));
		else if (a_star->closed_list[new.y][new.x] == -1
			&& is_blocked(map->array, new.y, new.x))
			find_new_f(new, actual, a_star);
		i++;
	}
}

void	a_star_loop(t_a_star_struct *a_star, t_map *map)
{
	a_star->found_end = 0;
	while (a_star->open_list)
	{
		a_star->first = a_star->open_list;
		a_star->open_list = a_star->open_list->next;
		a_star_neighbor(a_star, map);
		if (a_star->found_end)
			break ;
		a_star->open_list = move_lowest_f_to_front(&a_star->open_list);
	}
}

int	a_star_search(t_coords start, t_coords end, t_map *map)
{
	t_a_star_struct	a_star;

	init_a_star(map, start, end, &a_star);
	a_star_loop(&a_star, map);
	if (trace_path(a_star.cell_details, end, a_star.found_end))
		return (free_a_star_search(a_star, map->height), -1);
	else
		return (free_a_star_search(a_star, map->height), 0);
}

int	a_star(t_map *map)
{
	t_coords		start;
	t_collectibles	*collectibles;

	init_possible_directions(map);
	collectibles = map->collectibles;
	start = map->player_start;
	while (collectibles)
	{
		if (a_star_search(start, collectibles->coords, map))
			return (-1);
		start = collectibles->coords;
		collectibles = collectibles->next_collectible;
	}
	if (a_star_search(start, map->exit, map))
		return (-1);
	return (0);
}
