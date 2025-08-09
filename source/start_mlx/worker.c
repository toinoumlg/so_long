/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:24:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/27 12:18:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <pthread.h>
#define UNIT_SIZE 4
#define SQRT_THREAD_NBRS 4

int	create_rgb(int t, int r, int g, int b)
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
	return (0);
}

t_screen_unit	set_screen_array(t_vector2 index, int *pixel_array,
		t_vector2 screen_res)
{
	t_screen_unit	new;
	int				offset;

	offset = index.y * UNIT_SIZE * screen_res.x + index.x * UNIT_SIZE;
	new.pixel_array = pixel_array + offset;
	if (index.y == screen_res.y / UNIT_SIZE - 1)
		new.c = '1';
	else
		new.c = 0;
	new.color = set_color(new.c);
	new.is_new = 1;
	return (new);
}

static t_screen_unit	**init_screen_array(t_vector2 screen_res,
		int *pixel_array)
{
	t_screen_unit	**screen_array;
	t_vector2		index;

	int row, col;
	row = screen_res.y / UNIT_SIZE;
	col = screen_res.x / UNIT_SIZE;
	screen_array = malloc(sizeof(t_screen_unit *) * (row + 1));
	index.y = 0;
	while (index.y < row)
	{
		screen_array[index.y] = malloc(sizeof(t_screen_unit) * (col + 1));
		index.x = 0;
		while (index.x < col)
		{
			screen_array[index.y][index.x] = set_screen_array(index,
					pixel_array, screen_res);
			index.x++;
		}
		index.y++;
	}
	return (screen_array);
}

t_worker_routine	*init_workers(t_vector2 screen_res,
		t_pthread_locks *locks_data, t_image screen_image, t_data *data)
{
	t_worker_routine	*workers;
	t_screen_unit		**screen_array;
	int					i;
	t_vector2			index;
	int					workers_rows;
	int					workers_cols;

	screen_array = init_screen_array(screen_res, (int *)screen_image.addr);
	workers_rows = screen_res.y / UNIT_SIZE / SQRT_THREAD_NBRS;
	workers_cols = screen_res.x / UNIT_SIZE / SQRT_THREAD_NBRS;
	i = 0;
	workers = malloc(sizeof(t_worker_routine) * 16);
	ft_memset(workers, 0, sizeof(t_worker_routine) * 16);
	while (i < 16)
	{
		index = set_vector2(i / 4, i % 4);
		workers[i].screen_array = screen_array;
		workers[i].locks_data = locks_data;
		workers[i].index = index;
		workers[i].start_unit = set_vector2(index.y * workers_rows, index.x
				* workers_cols);
		workers[i].end_unit = set_vector2((index.y + 1) * workers_rows, (index.x
					+ 1) * workers_cols);
		workers[i].region_id = i;
		workers[i++].screen_res = screen_res;
	}
	data->screen_array = screen_array;
	return (workers);
}
