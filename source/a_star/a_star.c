/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/10 13:48:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "print_colors.h"
#include "so_long.h"

t_vector2	set_start(t_vector2 start, t_vector2 coords)
{
	if (coords.y < start.y)
	{
		if (coords.x < start.x)
			return (set_vector2(coords.y, coords.x));
		else
			return (set_vector2(coords.y, start.x));
	}
	else
	{
		if (coords.x < start.x)
			return (set_vector2(start.y, coords.x));
		else
			return (set_vector2(start.y, start.x));
	}
}

t_vector2	set_end(t_vector2 start, t_vector2 coords)
{
	if (coords.y < start.y)
	{
		if (coords.x < start.x)
			return (set_vector2(start.y, start.x));
		else
			return (set_vector2(start.y, coords.x));
	}
	else
	{
		if (start.x > coords.x)
			return (set_vector2(coords.y, start.x));
		else
			return (set_vector2(coords.y, coords.x));
	}
}

void	delete_open_list(t_open_list **open_list, t_open_list *list_to_remove)
{
	t_open_list	*tmp;

	tmp = *open_list;
	if (tmp == list_to_remove)
	{
		tmp = tmp->next;
		free(list_to_remove);
		tmp->prev = NULL;
		*open_list = tmp;
		return ;
	}
	while (tmp != list_to_remove)
		tmp = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	free(tmp);
}

void	remove_open_list(t_vector2 start, t_vector2 end,
		t_open_list **open_list)
{
	t_open_list	*tmp;
	int			i;

	i = 0;
	tmp = *open_list;
	while (tmp)
	{
		if (((tmp->values.coords.x > start.x && tmp->values.coords.x < end.x)
				&& (tmp->values.coords.y > start.y
					&& tmp->values.coords.y < end.y)))
			return (delete_open_list(open_list, tmp), remove_open_list(start,
					end, open_list));
		i++;
		tmp = tmp->next;
	}
}

void	fill_closed_list(t_vector2 start, t_vector2 end,
		signed char **closed_list)
{
	int	i;

	while (start.y < end.y)
	{
		i = start.x;
		while (i < end.x)
		{
			closed_list[start.y][i] = '1';
			i++;
		}
		start.y++;
	}
}

void	close_open_list(t_a_star *a_star, t_vector2 coords)
{
	t_vector2	end;
	t_vector2	start;

	start = set_start(a_star->start, coords);
	end = set_end(a_star->start, coords);
	remove_open_list(start, end, &a_star->open_list);
}

int	is_a_map_border(t_vector2 max, t_vector2 coords)
{
	return (coords.y == 0 || coords.x == 0 || coords.x == max.x
		|| coords.y == max.y);
}

void	a_star_neighbor_direction(t_a_star *a_star, t_data *data,
		t_vector2 direction, t_vector2 actual)
{
	t_a_star_values	new;

	new.coords = set_vector2(actual.y + direction.y, actual.x + direction.x);
	if (is_destination(new.coords, a_star->end))
		return (found_destination(new.coords, actual, a_star));
	else if (a_star->closed_list[new.coords.y][new.coords.x] == '0'
		&& !is_blocked(data->map.array, new.coords))
		find_new_f(new, actual, a_star);
	else if (is_blocked(data->map.array, new.coords)
		&& is_a_map_border(data->map.max, new.coords))
		close_open_list(a_star, new.coords);
}

t_a_star_values	first_open_list(t_open_list **open_list)
{
	t_a_star_values	values;
	t_open_list		*tmp;
	t_open_list		*next;

	tmp = *open_list;
	values = tmp->values;
	next = tmp->next;
	free(tmp);
	if (next)
		next->prev = NULL;
	*open_list = next;
	return (values);
}

void	a_star_neighbor(t_a_star *a_star, t_data *data)
{
	t_a_star_values			actual;
	t_possible_directions	directions;

	directions = data->directions;
	actual = first_open_list(&a_star->open_list);
	a_star->closed_list[actual.coords.y][actual.coords.x] = '1';
	a_star_neighbor_direction(a_star, data, directions.up, actual.coords);
	a_star_neighbor_direction(a_star, data, directions.down, actual.coords);
	a_star_neighbor_direction(a_star, data, directions.left, actual.coords);
	a_star_neighbor_direction(a_star, data, directions.right, actual.coords);
	sort_open_list(&a_star->open_list);
}

int	end_is_locked(t_vector2 end, char **array, t_possible_directions directions)
{
	if (array[end.y + directions.up.y][end.x + directions.up.x] == '1'
		&& array[end.y + directions.down.y][end.x + directions.down.x] == '1'
		&& array[end.y + directions.left.y][end.x + directions.left.x] == '1'
		&& array[end.y + directions.right.y][end.x + directions.right.x] == '1')
		return (1);
	return (0);
}

void	a_star_search(t_vector2 start, t_vector2 end, t_data *data)
{
	t_a_star	a_star;

	if (end_is_locked(end, data->map.array, data->directions))
		exit(parsing_error(data, NO_PATH_AVAILABLE));
	init_a_star(data, start, end, &a_star);
	while (!a_star.found_end && a_star.open_list)
		a_star_neighbor(&a_star, data);
	free_a_star_search(&a_star, data->map.max.y);
	if (!a_star.found_end)
		exit(parsing_error(data, NO_PATH_AVAILABLE));
}

void	check_valid_paths(t_data *data)
{
	t_vector2		start;
	t_collectible	*collectibles;

	data->directions = set_move();
	collectibles = data->collectibles;
	start = data->player->coords;
	while (collectibles)
	{
		a_star_search(start, collectibles->coords, data);
		start = collectibles->coords;
		collectibles = collectibles->next;
	}
	a_star_search(start, data->map.exit, data);
}
