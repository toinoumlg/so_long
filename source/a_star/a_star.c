/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/12 10:43:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "print_colors.h"
#include "so_long.h"
#include <pthread.h>

typedef struct s_pthread_a_star
{
	t_vector2				start;
	t_vector2				end;
	t_data					*data;
	struct s_pthread_a_star	*next;
}							t_pthread_a_star;

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
		*open_list = NULL;
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

	tmp = *open_list;
	while (tmp)
	{
		if (((tmp->values.coords.x > start.x && tmp->values.coords.x < end.x)
				&& (tmp->values.coords.y > start.y
					&& tmp->values.coords.y < end.y)))
			return (delete_open_list(open_list, tmp), remove_open_list(start,
					end, open_list));
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

void	a_star_neighbor_direction(t_a_star *a_star, t_vector2 direction)
{
	t_a_star_values	new;
	t_vector2		actual;

	actual = a_star->open_list->values.coords;
	new.coords = set_vector2(actual.y + direction.y, actual.x + direction.x);
	if (is_destination(new.coords, a_star->end))
		found_destination(new.coords, actual, a_star);
	else if (a_star->closed_list[new.coords.y][new.coords.x] == '0'
		&& !is_blocked(a_star->map, new.coords))
		find_new_f(new, actual, a_star);
	// else if (is_blocked(data->map.array, new.coords)
	// 	&& is_a_map_border(data->map.max, new.coords))
	// 	close_open_list(a_star, new.coords);
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

void	a_star_neighbor(t_a_star *a_star)
{
	t_possible_directions	directions;
	t_vector2				coords;

	coords = a_star->open_list->values.coords;
	directions = a_star->directions;
	a_star->closed_list[coords.y][coords.x] = '1';
	a_star_neighbor_direction(a_star, directions.up);
	a_star_neighbor_direction(a_star, directions.down);
	a_star_neighbor_direction(a_star, directions.left);
	a_star_neighbor_direction(a_star, directions.right);
	first_open_list(&a_star->open_list);
	swap_lowest_f(&a_star->open_list);
}

int	end_is_locked(t_a_star *a_star)
{
	t_possible_directions	directions;
	char					**map;
	t_vector2				end;

	directions = a_star->directions;
	map = a_star->map;
	end = a_star->end;
	return (map[end.y + directions.up.y][end.x + directions.up.x] == '1'
		&& map[end.y + directions.down.y][end.x + directions.down.x] == '1'
		&& map[end.y + directions.left.y][end.x + directions.left.x] == '1'
		&& map[end.y + directions.right.y][end.x + directions.right.x] == '1');
}

void	*a_star_routine(void *args)
{
	t_a_star	*a_star;

	a_star = (t_a_star *)args;
	if (end_is_locked(a_star))
		pthread_exit(a_star);
	init_a_star(a_star);
	while (!a_star->found_end && a_star->open_list)
		a_star_neighbor(a_star);
	pthread_exit(a_star);
}

void	append_ret_ptr(t_a_star **ret_list, t_a_star *ret)
{
	t_a_star	*tmp;

	if (!*ret_list)
	{
		*ret_list = ret;
		return ;
	}
	tmp = *ret_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ret;
	ret->next = NULL;
}

t_a_star	*join_threads(pthread_t *threads)
{
	int			i;
	void		*ret_ptr;
	t_a_star	*ret_list;

	ret_list = NULL;
	i = 0;
	while (threads[i])
	{
		pthread_join(threads[i++], &ret_ptr);
		append_ret_ptr(&ret_list, (t_a_star *)ret_ptr);
	}
	free(threads);
	return (ret_list);
}

void	*set_new_thread_data(t_data *data)
{
	t_a_star	*a_star;

	a_star = malloc(sizeof(t_a_star));
	if (!a_star)
		exit(1);
	memset(a_star, 0, sizeof(t_a_star));
	a_star->map = data->map.array;
	a_star->max = data->map.max;
	a_star->directions = data->directions;
	return (a_star);
}

void	set_threads_data(t_a_star **thread_data, pthread_t **threads,
		t_data *data)
{
	t_collectible	*collectibles;
	t_a_star		*tmp;
	int				i;

	i = 0;
	tmp = set_new_thread_data(data);
	i++;
	*thread_data = tmp;
	collectibles = data->collectibles;
	tmp->start = data->player->coords;
	while (collectibles)
	{
		tmp->end = collectibles->coords;
		tmp->next = set_new_thread_data(data);
		i++;
		tmp = tmp->next;
		tmp->start = collectibles->coords;
		collectibles = collectibles->next;
	}
	tmp->end = data->map.exit;
	*threads = malloc(sizeof(pthread_t) * (i + 1));
	if (!*threads)
		exit(parsing_error(data, ALLOC_ERROR));
	memset(*threads, 0, sizeof(pthread_t) * (i + 1));
}

void	start_threads_pathinding(t_a_star *thread_data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (thread_data)
	{
		pthread_create(&threads[i++], NULL, a_star_routine,
			(void *)thread_data);
		thread_data = thread_data->next;
	}
}

void	check_valid_paths(t_data *data)
{
	t_a_star	*thread_data;
	pthread_t	*threads;

	data->directions = set_move();
	set_threads_data(&thread_data, &threads, data);
	start_threads_pathinding(thread_data, threads);
	thread_data = join_threads(threads);
	free_a_star_routine(thread_data);
}
