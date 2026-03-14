/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:00:51 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:43:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar_globals.h"
#include "astar_internal.h"
#include "astar_struct.h"
#include "mem.h"
#include "str.h"
#include <stdio.h>

int	is_blocked(const t_vector2 *now, const char **map)
{
	return (map[now->y][now->x] == '1');
}

int	is_destination(const t_vector2 *now, const t_vector2 *end)
{
	return (now->y == end->y && now->x == end->x);
}

int	is_closed(t_closed **closed, const t_vector2 *coords)
{
	return (closed[coords->y][coords->x]);
}

void	a_star_neighbor_direction(t_astar *a_star, const t_vector2 *direction,
		t_thread_data *data)
{
	t_cell_astar	new;
	t_vector2		*now;

	now = &a_star->open->cell.coords;
	new.coords = (t_vector2){now->x + direction->x, now->y + direction->y};
	if (is_destination(&new.coords, &data->end))
		found_destination(&new.coords, now, a_star, data);
	if (!is_closed(a_star->closed, &new.coords) && !is_blocked(&new.coords,
			data->map))
		find_new_f(&new, now, a_star, data);
}

void	consume_open(t_open **open_list)
{
	t_open	*tmp;
	t_open	*next;

	tmp = *open_list;
	next = tmp->next;
	free(tmp);
	if (next)
		next->prev = NULL;
	*open_list = next;
}

void	a_star_neighbor(t_astar *a_star, t_thread_data *data)
{
	t_vector2	*coords;

	coords = &a_star->open->cell.coords;
	a_star->closed[coords->y][coords->x] = 1;
	a_star_neighbor_direction(a_star, &g_up, data);
	a_star_neighbor_direction(a_star, &g_down, data);
	a_star_neighbor_direction(a_star, &g_left, data);
	a_star_neighbor_direction(a_star, &g_right, data);
	consume_open(&a_star->open);
	swap_lowest_f(&a_star->open);
}

void	*a_star_routine(void *args)
{
	t_thread_data	*data;
	t_astar			local;

	data = (t_thread_data *)args;
	init_astar(&local, data);
	while (local.open)
		a_star_neighbor(&local, data);
	return (exit_thread(&local, data));
}

void	append_result(t_results **ret_list, t_vector2_list *final_path)
{
	t_results	*tmp;
	t_results	*new;

	new = malloc(sizeof(t_results));
	new->next = NULL;
	new->final_path = final_path;
	if (!*ret_list)
	{
		*ret_list = new;
		return ;
	}
	tmp = *ret_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_results	*join_threads(t_watcher *watcher)
{
	int			i;
	void		*final_path;
	t_results	*results;

	results = NULL;
	i = 0;
	while (i < watcher->started_thread)
	{
		pthread_join(watcher->threads[i++], &final_path);
		append_result(&results, final_path);
	}
	return (results);
}

void	push_thread(const t_vector2 *start, const t_vector2 *end,
		t_watcher *watcher)
{
	t_thread_data	*new;

	new = malloc(sizeof(t_thread_data));
	new->map = watcher->map;
	new->map_size = watcher->map_size;
	new->start = *start;
	new->end = *end;
	pthread_create(&watcher->threads[watcher->started_thread++], NULL,
		a_star_routine, (void *)new);
}

void	start_threads(t_vector2 start, t_watcher *watcher)
{
	int			y;
	int			x;
	t_vector2	end;

	y = 1;
	while (watcher->map[y])
	{
		x = 1;
		while (watcher->map[y][x])
		{
			if (watcher->map[y][x] == 'C' || watcher->map[y][x] == 'E')
			{
				end = (t_vector2){x, y};
				push_thread(&start, &end, watcher);
				start = end;
			}
			x++;
		}
		y++;
	}
}

bool	print_result(t_results *results)
{
	t_vector2_list	*final_path;
	bool			failed;

	failed = false;
	while (results)
	{
		final_path = results->final_path;
		if (!final_path)
		{
			printf("No path found for this collectible");
			failed = true;
		}
		else
		{
			while (final_path)
			{
				printf("%d %d \n", final_path->value.y, final_path->value.x);
				final_path = final_path->next;
			}
		}
		printf("\n");
		results = results->next;
	}
	return (failed);
}

void	free_results(t_results *result)
{
	t_vector2_list	*final_path;
	t_vector2_list	*next_path;
	t_results		*next_result;

	while (result)
	{
		next_result = result->next;
		final_path = result->final_path;
		while (final_path)
		{
			next_path = final_path->next;
			free(final_path);
			final_path = next_path;
		}
		free(result);
		result = next_result;
	}
}

bool	check_result(t_results *results)
{
	t_vector2_list	*final_path;

	while (results)
	{
		final_path = results->final_path;
		if (!final_path)
			return (true);
		results = results->next;
	}
	return (false);
}

/// @brief execute an astar algorith in multiple thread based on :
///  https://www.geeksforgeeks.org/dsa/a-search-algorithm/
/// @param map 2d array composed of '0' as empty space, '1' for walls
/// 'C' for collectibles to find
/// @param xy starting position inside map
/// @return 0 if all path were found else 1
bool	astar(const char **map, t_vector2 start, const t_vector2 *map_size)
{
	t_results	*result;
	bool		failed;
	t_watcher	watcher;

	failed = true;
	if (!map || !*map)
		return (failed);
	watcher.map = map;
	watcher.started_thread = 0;
	watcher.map_size = map_size;
	start_threads(start, &watcher);
	result = join_threads(&watcher);
	failed = check_result(result);
	free_results(result);
	return (failed);
}

t_vector2	*astar_single(const char **map, const t_vector2 *start,
		const t_vector2 *target, const t_vector2 *map_size)
{
	t_results *result;
	t_watcher watcher;

	if (!map || !*map)
		return (NULL);

	watcher.map = map;
	watcher.started_thread = 0;
	watcher.map_size = map_size;
	push_thread(start, target, &watcher);
	result = join_threads(&watcher);

	print_result(result);
	free_results(result);
	return (NULL);
}