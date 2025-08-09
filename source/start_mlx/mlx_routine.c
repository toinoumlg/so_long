/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:21:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/27 12:20:57 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "worker.h"
#include "worker_routine.h"
#include <pthread.h>
#define UNIT_SIZE 4
#define SQRT_THREAD_NBRS 4
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

void	start_workers(t_worker_routine *workers)
{
	pthread_t	threads[16];
	int			i;

	i = -1;
	while (++i < 16)
		pthread_create(&threads[i], NULL, workers_routine, (void *)&workers[i]);
}

int	handle_keys(int key, t_mlx_routine *mlx)
{
	pthread_mutex_lock(&mlx->locks_data->key_mutex);
	mlx->locks_data->key = key;
	pthread_mutex_unlock(&mlx->locks_data->key_mutex);
	return (0);
}

void	*key_hooks_routine(void *args)
{
	t_mlx_routine	*mlx;

	mlx = (t_mlx_routine *)args;
	mlx_hook(mlx->window->ptr, 2, (1L << 0), handle_keys, mlx);
	mlx_loop(mlx->ptr);
	return (NULL);
}

void	start_key_hooks(t_mlx_routine *mlx)
{
	pthread_t	thread;

	pthread_mutex_lock(&mlx->locks_data->key_mutex);
	mlx->locks_data->key = 0;
	pthread_mutex_unlock(&mlx->locks_data->key_mutex);
	pthread_create(&thread, NULL, key_hooks_routine, (void *)mlx);
}

void	*mlx_routine(void *args)
{
	t_mlx_routine *mlx;
	t_worker_routine *workers;

	mlx = (t_mlx_routine *)args;
	workers = init_workers(mlx->screen_res, mlx->locks_data, mlx->screen_image,
			mlx->data);
	start_key_hooks(mlx);
	start_workers(workers);
	while (1)
	{
		pthread_mutex_lock(&mlx->locks_data->draw_mutex);
		while (mlx->locks_data->draw_count < mlx->locks_data->draw_goal)
			pthread_cond_wait(&mlx->locks_data->draw_cond,
				&mlx->locks_data->draw_mutex);
		mlx_put_image_to_window(mlx->ptr, mlx->window->ptr,
			mlx->screen_image.image, 0, 0);
		mlx_do_sync(mlx->ptr);
		mlx->locks_data->draw_count = 0;
		mlx->locks_data->drawing = 1;
		pthread_cond_broadcast(&mlx->locks_data->draw_cond);
		pthread_mutex_unlock(&mlx->locks_data->draw_mutex);
		pthread_mutex_lock(&mlx->locks_data->logic_mutex);
		mlx->locks_data->logic_done = 0;
		pthread_mutex_unlock(&mlx->locks_data->logic_mutex);
	}
}