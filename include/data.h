/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:59:58 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:53:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef unsigned long		t_pxl;

typedef struct s_vector2
{
	int						x;
	int						y;
}							t_vector2;

# ifndef POSSIBLE_DIRECTIONS
#  define POSSIBLE_DIRECTIONS

static const t_vector2		DIR_UP = {-1, 0};
static const t_vector2		DIR_DOWN = {1, 0};
static const t_vector2		DIR_RIGHT = {0, 1};
static const t_vector2		DIR_LEFT = {0, -1};

# endif


typedef struct s_vector2_list
{
	t_vector2				vector;
	struct s_vector2_list	*next;
	struct s_vector2_list	*prev;
}							t_vector2_list;

typedef struct s_input
{
	bool					w;
	bool					a;
	bool					s;
	bool					d;
	bool					attack;
}							t_input;

typedef struct s_a_star_values
{
	t_vector2				coords;
	float					g;
	float					h;
	float					f;
}							t_a_star_values;

typedef struct s_open_list
{
	t_a_star_values			values;
	struct s_open_list		*next;
	struct s_open_list		*prev;
}							t_open_list;

typedef struct s_collectible
{
	t_vector2				coords;
	int						i_image;
	int						is_printed;
	struct s_collectible	*next;
}							t_collectible;

typedef struct s_ennemy
{
	t_vector2				coords;
	t_vector2				next_coords;
	int						is_printed;
	int						i_image;
	int						got_hit;
	struct s_ennemy			*next;
}							t_ennemy;

typedef struct s_map
{
	char					**array;
	t_vector2				min;
	t_vector2				max;
	t_vector2				exit;
	t_collectible			*collectibles;
	t_ennemy				*ennemies;
}							t_map;

typedef struct s_a_star
{
	t_a_star_values			**cell_details;
	t_open_list				*open_list;
	signed char				**closed_list;
	t_vector2				start;
	t_vector2				end;
	t_vector2				max;
	char					found_end;
	char					**map;
	int						**final_path;
	struct s_a_star			*next;
	struct s_a_star			*prev;
}							t_a_star;

typedef struct s_img
{
	void					*ptr;
	t_pxl					*addr;
	int						lenght;
	int						bpp;
	int						endian;
	int						width;
	int						height;
}							t_img;

typedef struct s_window
{
	void					*ptr;
	t_vector2				screen_size;
}							t_window;

typedef struct s_textures
{
	t_img					*ground;
	t_img					*water;
	t_img					*walls;
	t_img					*borders;
	t_img					*player;
	t_img					*sword;
	t_img					*coins;
	t_img					*exit;
	t_img					*ennemies;
	t_img					*hud;
	t_img					*heart;
}							t_textures;

typedef struct s_sword
{
	t_vector2				coords;
	t_vector2				next_coords;
	t_vector2				direction;
	int						to_destroy;
	int						sword_timer;
	int						is_printed;
	int						index;
	struct s_sword			*next_sword;
}							t_sword;

// status 0 idle 1;
typedef struct s_player
{
	const t_vector2			*move_dir;
	t_vector2				coords;
	int						health;
	int						status;
	int						index;
	int						attack_cd;
	int						move_buffer;
	int						moves;
	t_sword					*swords;
}							t_player;

typedef struct s_game
{
	t_collectible			*collectibles;
	t_ennemy				*ennemies;
	t_player				player;
	int						actual_sword;
	int						game_finished;
	int						is_exit_printed;

}							t_game;

typedef struct s_timer
{
	struct timeval			last_frame;
	struct timeval			current_time;
	double					time;
	double					frame_target;
	double					delta_time;
}							t_timer;

typedef struct s_key_hook_routine
{
	void					*mlx;
	t_a_star				*pathfinding;
	t_window				*window;
	t_img					screen;

}							t_key_hook_routine;

typedef struct screen_unit
{
	int						color;
	int						*pixel_array;
	char					c;
	int						is_new;
}							t_screen_unit;

typedef struct s_pthread_locks
{
	pthread_mutex_t			draw_mutex;
	pthread_mutex_t			logic_mutex;
	pthread_mutex_t			key_mutex;
	pthread_cond_t			draw_cond;
	pthread_cond_t			logic_cond;
	int						drawing;
	int						draw_count;
	int						draw_goal;
	int						logic_done;
	int						key;
}							t_pthread_locks;

typedef struct s_worker_routine
{
	t_screen_unit			**screen_array;
	t_vector2				index;
	t_vector2				screen_res;
	t_vector2				start_unit;
	t_vector2				end_unit;
	int						region_id;
	t_pthread_locks			*locks_data;
}							t_worker_routine;

typedef struct s_data
{
	int						frames;
	void					*mlx;
	t_textures				textures;
	t_window				window;
	t_game					game;
	t_map					map;
	t_timer					timer;
	t_player				player;
	t_ennemy				*ennemies;
	t_collectible			*collectibles;
	t_a_star				*pathfinding;
	t_pthread_locks			*locks_data;
	t_vector2				screen_res;
	t_screen_unit			**screen_array;
}							t_data;

typedef struct s_mlx_routine
{
	void					*ptr;
	t_img					screen_image;
	t_vector2				screen_res;
	t_window				*window;
	t_pthread_locks			*locks_data;
	t_data					*data;
}							t_mlx_routine;
#endif