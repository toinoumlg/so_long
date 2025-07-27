/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:19:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/27 09:46:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <pthread.h>
#define UNIT_SIZE 4
#define SQRT_THREAD_NBRS 4

static int	create_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	set_color(char c)
{
	if (c == '2')
		return (create_rgb(0, 255, 0, 0));
	if (c == 'P')
		return (create_rgb(0, 0, 0, 255));
	if (c == 'C')
		return (create_rgb(0, 255, 255, 0));
	if (c == 'E')
		return (create_rgb(0, 255, 0, 255));
	if (c == '0' || c == 0)
		return (create_rgb(0, 255, 255, 255));
	if (c == '1')
		return (create_rgb(0, 0, 0, 0));
	if (c == 'B')
		return (create_rgb(0, 255, 0, 0));
	return (0);
}

void	draw_square(t_worker_routine *worker, t_vector2 index, int current)
{
	int	line;
	int	*line_ptr;
	int	*pixel_array;
	int	color;
	int	i;

	if (!worker->screen_array[current][index.y][index.x].is_new)
		return ;
	color = set_color(worker->screen_array[current][index.y][index.x].c);
	pixel_array = worker->screen_array[current][index.y][index.x].pixel_array;
	line = 0;
	while (line < UNIT_SIZE)
	{
		line_ptr = pixel_array + line * worker->screen_res.x;
		i = 0;
		while (i < UNIT_SIZE)
			line_ptr[i++] = color;
		line++;
	}
	worker->screen_array[current][index.y][index.x].is_new = 0;
}

void	draw_region(t_worker_routine *worker, int current)
{
	t_vector2	index;

	index.y = worker->start_unit.y;
	while (index.y < worker->end_unit.y)
	{
		index.x = worker->start_unit.x;
		while (index.x < worker->end_unit.x)
		{
			draw_square(worker, index, current);
			index.x++;
		}
		index.y++;
	}
}

void	*workers_routine(void *args)
{
	t_worker_routine	*worker;
	int					current;

	current = 1;
	worker = (t_worker_routine *)args;
	draw_region(worker, current);
	draw_region(worker, current - 1);
	while (1)
	{
		pthread_mutex_lock(&worker->locks_data->logic_mutex);
		while (!worker->locks_data->logic_done)
			pthread_cond_wait(&worker->locks_data->logic_cond,
				&worker->locks_data->logic_mutex);
		pthread_mutex_unlock(&worker->locks_data->logic_mutex);
		draw_region(worker, current);
		pthread_mutex_lock(&worker->locks_data->draw_mutex);
		worker->locks_data->draw_count++;
		if (worker->locks_data->draw_count == worker->locks_data->draw_goal)
		{
			worker->locks_data->drawing = 0;
			pthread_cond_signal(&worker->locks_data->draw_cond);
		}
		pthread_mutex_unlock(&worker->locks_data->draw_mutex);
		current = current ^ 1;
	}
	return (NULL);
}
