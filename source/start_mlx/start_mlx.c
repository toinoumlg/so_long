/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:17:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:48:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_routine.h"
#include "so_long.h"
#include <pthread.h>
#define UNIT_SIZE 4
#define SQRT_THREAD_NBRS 4

t_vector2	get_screen_size(void *mlx)
{
	t_vector2	screen_size;

	mlx_get_screen_size(mlx, &screen_size.y, &screen_size.y);
	if (screen_size.x != screen_size.y * (16.0 / 9.0))
		screen_size.x = (screen_size.y * (16.0 / 9.0)) * 0.8;
	screen_size.y = (screen_size.y * 0.8);
	screen_size.y = screen_size.y - (screen_size.y % PIXEL_PADDING);
	screen_size.x = screen_size.x - (screen_size.x % PIXEL_PADDING);
	return (screen_size);
}

t_pthread_locks	*init_locks_data(void)
{
	t_pthread_locks	*locks_data;

	locks_data = malloc(sizeof(t_pthread_locks));
	locks_data->drawing = 1;
	locks_data->draw_count = 0;
	locks_data->draw_goal = 16;
	locks_data->logic_done = 0;
	pthread_mutex_init(&locks_data->draw_mutex, NULL);
	pthread_cond_init(&locks_data->draw_cond, NULL);
	pthread_cond_init(&locks_data->logic_cond, NULL);
	pthread_mutex_init(&locks_data->key_mutex, NULL);
	pthread_mutex_init(&locks_data->logic_mutex, NULL);
	return (locks_data);
}

t_img	set_screen_images(void *mlx, t_vector2 screen_res)
{
	t_img	screen_image;

	screen_image.ptr = mlx_new_image(mlx, screen_res.x, screen_res.y);
	screen_image.addr = (t_pxl *)mlx_get_data_addr(screen_image.ptr,
			&screen_image.bpp, &screen_image.lenght, &screen_image.endian);
	return (screen_image);
}

t_mlx_routine	*set_mlx_routine(t_data *data)
{
	t_mlx_routine	*mlx;

	mlx = malloc(sizeof(t_mlx_routine));
	ft_memset(mlx, 0, sizeof(t_mlx_routine));
	data->mlx = mlx_init();
	mlx->locks_data = init_locks_data();
	data->locks_data = mlx->locks_data;
	mlx->data = data;
	mlx->ptr = data->mlx;
	mlx->screen_res = get_screen_size(mlx->ptr);
	data->screen_res = mlx->screen_res;
	data->window.ptr = mlx_new_window(data->mlx, mlx->screen_res.x,
			mlx->screen_res.y, "caca");
	mlx->window = &data->window;
	mlx->screen_image = set_screen_images(mlx->ptr, mlx->screen_res);
	return (mlx);
}

void	start_mlx(t_data *data)
{
	t_mlx_routine	*mlx;
	pthread_t		thread;

	mlx = set_mlx_routine(data);
	pthread_create(&thread, NULL, mlx_routine, (void *)mlx);
}
