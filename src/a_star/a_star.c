/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/04 20:20:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	a_star_neighbor_direction(t_a_star_struct *a_star, t_map *map,
		t_vector2 direction, t_vector2 actual)
{
	t_new_values	new;

	new.parent = set_vector2(actual.y + direction.y, actual.x + direction.x);
	if (is_destination(new.parent, a_star->end))
		return (found_destination(new.parent, actual, a_star));
	else if (a_star->closed_list[new.parent.y][new.parent.x] == -1
		&& is_blocked(map->array, new.parent))
		find_new_f(new, actual, a_star);
}

int	a_star_neighbor(t_a_star_struct *a_star, t_map *map)
{
	t_vector2	actual;

	actual = a_star->first->coords;
	if (a_star->closed_list[actual.y][actual.x] == 0)
		return (1);
	a_star->closed_list[actual.y][actual.x] = 0;
	free(a_star->first);
	a_star_neighbor_direction(a_star, map, map->direction.up, actual);
	a_star_neighbor_direction(a_star, map, map->direction.down, actual);
	a_star_neighbor_direction(a_star, map, map->direction.left, actual);
	a_star_neighbor_direction(a_star, map, map->direction.right, actual);
	return (0);
}

void	a_star_loop(t_a_star_struct *a_star, t_map *map)
{
	a_star->found_end = 0;
	while (a_star->open_list)
	{
		a_star->first = a_star->open_list;
		a_star->open_list = a_star->open_list->next;
		if (a_star_neighbor(a_star, map))
			return ;
		if (a_star->found_end)
			break ;
		a_star->open_list = move_lowest_f_to_front(&a_star->open_list);
	}
}

int	a_star_search(t_vector2 start, t_vector2 end, t_map *map)
{
	t_a_star_struct	a_star;

	init_a_star(map, start, end, &a_star);
	a_star_loop(&a_star, map);
	if (trace_path(a_star.cell_details, end, a_star.found_end))
		return (free_collectibles(map->collectibles), free_a_star_search(a_star,
				map->actual.y), -1);
	else
		return (free_a_star_search(a_star, map->actual.y), 0);
}

int	a_star(t_map *map)
{
	t_vector2		start;
	t_collectibles	*collectibles;

	map->direction = set_move();
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
