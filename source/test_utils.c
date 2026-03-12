/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:19:23 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:30:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_colors.h"
#include "so_long.h"
#include <pthread.h>
#define SQRT_THREAD_MAX 4
#define MAP_PIXEL_SIZE 8

typedef struct s_pthread_window
{
	t_vector2				min;
	t_vector2				max;
	t_img					*image;
	unsigned int			color;
	t_a_star				*a_star;
	t_vector2				map_offset[2];
	struct s_pthread_window	*next;
}							t_pthread_window;

int	print_open_list(t_open_list *open_list, int y, int x)
{
	while (open_list)
	{
		if (open_list->values.coords.y == y && open_list->values.coords.x == x)
			return (1);
		open_list = open_list->next;
	}
	return (0);
}

void	append_data(t_pthread_window **pthread_data, t_pthread_window *ret)
{
	t_pthread_window	*tmp;

	ret->next = NULL;
	if (!*pthread_data)
	{
		*pthread_data = ret;
		return ;
	}
	tmp = *pthread_data;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ret;
}

unsigned int	set_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	set_window_data(t_pthread_window **pthread_data, t_vector2 screen_size,
		t_img *image, t_a_star *a_star)
{
	t_pthread_window	*new;
	t_vector2			index;
	t_vector2			map_offset[2];

	map_offset[0].y = screen_size.y / 2 - (a_star->max.y * MAP_PIXEL_SIZE / 2);
	map_offset[0].x = screen_size.x / 2 - (a_star->max.x * MAP_PIXEL_SIZE / 2);
	map_offset[1].x = map_offset[0].x + (a_star->max.x + 1) * MAP_PIXEL_SIZE;
	map_offset[1].y = map_offset[0].y + ((a_star->max.y + 1) * MAP_PIXEL_SIZE);
	index.y = 0;
	while (index.y * (screen_size.y / SQRT_THREAD_MAX) < screen_size.y)
	{
		index.x = 0;
		while (index.x * (screen_size.x / SQRT_THREAD_MAX) < screen_size.x)
		{
			new = malloc(sizeof(t_pthread_window));
			ft_memset(new, 0, sizeof(t_pthread_window));
			new->image = image;
			new->min = set_vector2(index.y * (screen_size.y / SQRT_THREAD_MAX),
					index.x * (screen_size.x / SQRT_THREAD_MAX));
			new->max = set_vector2((index.y + 1) * (screen_size.y
						/ SQRT_THREAD_MAX), (index.x + 1) * (screen_size.x
						/ SQRT_THREAD_MAX));
			new->a_star = a_star;
			if (a_star->found_end)
				new->color = set_color(0, 0, 0, 255);
			else
				new->color = set_color(0, 255, 0, 0);
			new->map_offset[0] = map_offset[0];
			new->map_offset[1] = map_offset[1];
			append_data(pthread_data, new);
			index.x++;
		}
		index.y++;
	}
}

void	free_pthread_data(t_pthread_window *pthread_data)
{
	t_pthread_window	*next;

	while (pthread_data)
	{
		next = pthread_data->next;
		free(pthread_data);
		pthread_data = next;
	}
}

int	is_in_final_path(t_pthread_window *data, t_vector2 index,
		t_vector2 map_index)
{
	int	i;

	i = data->a_star->final_path[map_index.y][map_index.x];
	if (i >= 0)
	{
		put_pixel(data->image, index, set_color(0, i, 255 - (i << 1), 255 - i));
		return (1);
	}
	return (0);
}

void	put_pixel_in_map(t_pthread_window *data, t_vector2 index)
{
	t_vector2	map_index;
	char		c;

	map_index = set_vector2((index.y - (data->map_offset[0].y))
			/ MAP_PIXEL_SIZE, (index.x - data->map_offset[0].x)
			/ MAP_PIXEL_SIZE);
	if (is_in_final_path(data, index, map_index))
		return ;
	c = data->a_star->map[map_index.y][map_index.x];
	if (c == 'C')
		put_pixel(data->image, index, set_color(0, 255, 0, 255));
	if (c == '1' || c == '2' || c == 'P' || c == 'E')
		put_pixel(data->image, index, set_color(0, 255, 0, 0));
	if (c == '0')
		put_pixel(data->image, index, set_color(0, 255, 255, 255));
}

void	*image_routine(void *args)
{
	t_pthread_window	*data;
	t_vector2			index;

	data = (t_pthread_window *)args;
	index = data->min;
	while (index.y < data->max.y)
	{
		index.x = data->min.x;
		while (index.x < data->max.x)
		{
			if (index.y >= data->map_offset[0].y
				&& index.y < data->map_offset[1].y
				&& index.x >= data->map_offset[0].x
				&& index.x < data->map_offset[1].x)
				put_pixel_in_map(data, index);
			else
				put_pixel(data->image, index, data->color);
			index.x++;
		}
		index.y++;
	}
	pthread_exit(data);
}



// void	print_a_star(t_key_hook_routine *kh)
// {
// 	t_pthread_window	*pthread_data;
// 	pthread_t			*threads;
// 	t_pthread_window	*current;
// 	int					i;

// 	i = 0;
// 	threads = malloc(sizeof(pthread_t) * (SQRT_THREAD_MAX * SQRT_THREAD_MAX
// 				+ 1));
// 	pthread_data = NULL;
// 	pthread_mutex_lock(kh->image_pushed);
// 	i = kh->window->to_push;
// 	pthread_mutex_unlock(kh->image_pushed);
// 	if (!i)
// 	{
// 		set_window_data(&pthread_data, kh->window->screen_size,
// 			&kh->window->screen, kh->pathfinding);
// 		i = 0;
// 		ft_memset(threads, 0, sizeof(pthread_t) * (SQRT_THREAD_MAX
// 				* SQRT_THREAD_MAX + 1));
// 		current = pthread_data;
// 		while (current)
// 		{
// 			pthread_create(&threads[i++], NULL, image_routine, (void *)current);
// 			current = current->next;
// 		}
// 		i = 0;
// 		while (threads[i])
// 			pthread_join(threads[i++], NULL);
// 		free_pthread_data(pthread_data);
// 		pthread_mutex_lock(kh->image_pushed);
// 		kh->window->to_push = 1;
// 		pthread_mutex_unlock(kh->image_pushed);
// 	}
// 	free(threads);
// }
