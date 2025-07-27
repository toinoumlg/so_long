/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/27 10:20:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "start_mlx.h"
#define SPACE_BAR 32
#define GRAVITY 40 // m/s/s
#define RHO 0.75   // coefficient of restitution
#define HSTOP 0.01 // height where we stop bouncing
#define KEY_A 97
#define KEY_D 100
#define JUMP_FORCE 25.0
#define MOVE_SPEED 50.0
#define FRICTION 0.95

typedef struct s_fvector2
{
	float		y;
	float		x;
}				t_fvector2;

typedef struct ball
{
	t_fvector2	position;
	t_fvector2	velocity;
	double		h_max;
	int			freefall;
	double		v_max;
	int			on_ground;
}				t_ball;

t_fvector2	set_fvector2(float y, float x)
{
	t_fvector2	new;

	new.y = y;
	new.x = x;
	return (new);
}

static void	set_timer(t_timer *timer)
{
	gettimeofday(&timer->last_frame, NULL);
}

static void	get_current(t_timer *timer)
{
	gettimeofday(&timer->current_time, NULL);
	timer->delta_time = (timer->current_time.tv_sec - timer->last_frame.tv_sec)
		+ (timer->current_time.tv_usec - timer->last_frame.tv_usec) / 1000000.0;
	timer->last_frame = timer->current_time;
}

int	get_key_value(t_data *data)
{
	int	key;

	key = 0;
	pthread_mutex_lock(&data->locks_data->key_mutex);
	key = data->locks_data->key;
	if (key)
		data->locks_data->key = 0;
	pthread_mutex_unlock(&data->locks_data->key_mutex);
	return (key);
}

void	bounce_ball(t_ball *test_ball, double_t d_time)
{
	double	h_new;

	if (test_ball->freefall)
	{
		h_new = test_ball->position.y + test_ball->velocity.y * d_time - 0.5
			* GRAVITY * d_time * d_time;
		if (h_new <= 0)
		{
			test_ball->freefall = 0;
			test_ball->on_ground = 1;
			test_ball->position.y = 0;
			test_ball->v_max = test_ball->v_max * RHO;
			if (test_ball->v_max < HSTOP)
			{
				test_ball->velocity.y = 0;
				test_ball->v_max = 0;
			}
			else
				test_ball->velocity.y = test_ball->v_max;
		}
		else
		{
			test_ball->position.y = h_new;
			test_ball->velocity.y = test_ball->velocity.y - GRAVITY * d_time;
			test_ball->on_ground = 0;
		}
	}
	else if (test_ball->v_max > 0)
	{
		test_ball->freefall = 1;
		test_ball->position.y = 0;
		test_ball->on_ground = 0;
	}
	test_ball->position.x += test_ball->velocity.x * d_time;
	if (test_ball->on_ground)
	{
		test_ball->velocity.x *= FRICTION;
	}
	if (test_ball->position.x < 0)
	{
		test_ball->position.x = 0;
		test_ball->velocity.x = 0;
	}
	if (test_ball->v_max > 0)
		test_ball->h_max = 0.5 * test_ball->v_max * test_ball->v_max / GRAVITY;
}

void	handle_input(int key, t_ball *test_ball)
{
	if (key == SPACE_BAR && test_ball->on_ground)
	{
		test_ball->velocity.y = JUMP_FORCE;
		test_ball->freefall = 1;
		test_ball->on_ground = 0;
		test_ball->v_max = JUMP_FORCE;
	}
	if (key == KEY_A)
		test_ball->velocity.x -= MOVE_SPEED;
	if (key == KEY_D)
		test_ball->velocity.x += MOVE_SPEED;
}

void	update_game_logic(double_t d_time, t_data *data, t_ball *test_ball)
{
	int	key;

	key = get_key_value(data);
	if (key)
		handle_input(key, test_ball);
	bounce_ball(test_ball, d_time);
}

void	start_game_loop(t_data *data)
{
	double	d_time;
	double	accumulator;
	int		running;
	t_timer	timer;
	t_ball	test_ball;

	test_ball.position = set_fvector2(0, 0);
	test_ball.velocity = set_fvector2(0, 0);
	test_ball.freefall = 0;
	test_ball.on_ground = 1;
	test_ball.v_max = 0;
	test_ball.h_max = 0;
	d_time = 1.0 / 120.0;
	accumulator = 0.0;
	running = 1;
	set_timer(&timer);
	sleep(1);
	while (running)
	{
		get_current(&timer);
		accumulator += timer.delta_time;
		data->screen_array[0][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].c = 0;
		data->screen_array[1][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].c = 0;
		data->screen_array[0][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].is_new = 1;
		data->screen_array[1][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].is_new = 1;
		while (accumulator >= d_time)
		{
			update_game_logic(d_time, data, &test_ball);
			accumulator -= d_time;
		}
		data->screen_array[0][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].c = 'B';
		data->screen_array[1][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].c = 'B';
		data->screen_array[0][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].is_new = 1;
		data->screen_array[1][(data->screen_res.y - 5) / 4
			- (int)test_ball.position.y][(int)test_ball.position.x].is_new = 1;
		pthread_mutex_lock(&data->locks_data->logic_mutex);
		data->locks_data->logic_done = 1;
		pthread_cond_signal(&data->locks_data->logic_cond);
		pthread_mutex_unlock(&data->locks_data->logic_mutex);
	}
}

int	main(int ac, char **av)
{
	t_data data;

	map_parser(&data, av, ac);
	start_mlx(&data);
	start_game_loop(&data);
	// init_game(&data);
	// start_game(data);
}