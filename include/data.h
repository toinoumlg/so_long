/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:59:58 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/27 12:20:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_vector2
{
	int						x;
	int						y;
}							t_vector2;

typedef struct s_vector2_list
{
	t_vector2				vector;
	struct s_vector2_list	*next;
	struct s_vector2_list	*prev;
}							t_vector2_list;

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

typedef struct s_possible_directions
{
	t_vector2				up;
	t_vector2				down;
	t_vector2				left;
	t_vector2				right;
	t_vector2				zero;
}							t_possible_directions;

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
	char					*file_path;
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
	t_possible_directions	directions;
	int						**final_path;
	struct s_a_star			*next;
	struct s_a_star			*prev;
}							t_a_star;

typedef struct s_image
{
	void					*image;
	char					*addr;
	t_vector2				wh;
	int						size_l;
	int						bpp;
	int						endian;
}							t_image;

typedef struct s_window
{
	void					*ptr;
	t_vector2				screen_size;
}							t_window;

typedef struct s_textures
{
	t_image					*ground;
	t_image					*water;
	t_image					*walls;
	t_image					*borders;
	t_image					*player;
	t_image					*sword;
	t_image					*coins;
	t_image					*exit;
	t_image					*ennemies;
	t_image					*hud;
	t_image					*heart;
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
	t_vector2				move_dir;
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
	t_possible_directions	moves;
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
	t_image					screen;

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
	t_player				*player;
	t_ennemy				*ennemies;
	t_collectible			*collectibles;
	t_a_star				*pathfinding;
	t_possible_directions	directions;
	t_pthread_locks			*locks_data;
	t_vector2				screen_res;
	t_screen_unit			**screen_array;
}							t_data;

typedef struct s_mlx_routine
{
	void					*ptr;
	t_image					screen_image;
	t_vector2				screen_res;
	t_window				*window;
	t_pthread_locks			*locks_data;
	t_data					*data;
}							t_mlx_routine;
#endif