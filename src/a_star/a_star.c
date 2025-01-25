/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 19:33:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	trace_path(t_cell **cell_details, t_coords end, char found)
{
	if (!found)
		return (-1);
	else
		print_final_path(cell_details, end);
	return (0);
}

t_a_star_struct	a_star_neighbor(t_a_star_struct a_star, t_map *map)
{
	t_coords		possible_direction;
	t_coords		actual;
	int				i;
	t_new_values	new;

	i = 0;
	actual = a_star.first->coords;
	a_star.closed_list[actual.y][actual.x] = 0;
	free(a_star.first);
	while (i < 4)
	{
		possible_direction = a_star.possible_directions->possible_directions[i];
		new.y = actual.y + possible_direction.y;
		new.x = actual.x + possible_direction.x;
		if (is_destination(new.y, new.x, a_star.end))
			return (a_star = found_destination(new, actual, a_star));
		else if (a_star.closed_list[new.y][new.x] == -1
			&& is_blocked(map->array, new.y, new.x))
			a_star = find_new_f(new, actual, a_star);
		i++;
	}
	return (a_star);
}

t_a_star_list	*move_lowest_f_to_front(t_a_star_list **open_list)
{
	t_a_star_list	*lowest_prev;
	t_a_star_list	*current;
	t_a_star_list	*lowest;

	current = *open_list;
	lowest = *open_list;
	lowest_prev = NULL;
	while (current->next)
	{
		if (current->next->f < lowest->f)
		{
			lowest_prev = current;
			lowest = current->next;
		}
		current = current->next;
	}
	if (lowest == *open_list)
		return (*open_list);
	if (lowest_prev)
		lowest_prev->next = lowest->next;
	lowest->next = *open_list;
	*open_list = lowest;
	return (*open_list);
}

t_a_star_struct	a_star_loop(t_a_star_struct a_star, t_map *map)
{
	a_star.found_end = 0;
	while (a_star.open_list)
	{
		a_star.first = a_star.open_list;
		a_star.open_list = a_star.open_list->next;
		a_star = a_star_neighbor(a_star, map);
		if (a_star.found_end)
			break ;
		a_star.open_list = move_lowest_f_to_front(&a_star.open_list);
	}
	return (a_star);
}

int	a_star_search(t_coords start, t_coords end,
		t_possible_directions *possible_directions, t_map *map)
{
	t_a_star_struct	a_star;

	a_star = init_a_star(map, start, end, possible_directions);
	a_star = a_star_loop(a_star, map);
	if (trace_path(a_star.cell_details, end, a_star.found_end))
		return (free_a_star_search(a_star, map->height), -1);
	else
		return (free_a_star_search(a_star, map->height), 0);
}

int	a_star(t_map *map)
{
	t_coords				start;
	t_coords				end;
	t_possible_directions	possible_directions;
	t_collectibles			*collectibles;

	possible_directions.possible_directions = init_possible_directions();
	collectibles = map->collectibles;
	start = map->player_start;
	while (collectibles)
	{
		end = collectibles->coords;
		if (a_star_search(start, end, &possible_directions, map))
			return (free(possible_directions.possible_directions), -1);
		start = collectibles->coords;
		collectibles = collectibles->next_collectible;
	}
	end = map->exit;
	if (a_star_search(start, end, &possible_directions, map))
		return (free(possible_directions.possible_directions), -1);
	return (free(possible_directions.possible_directions), 0);
}
