/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:59:58 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 22:02:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "bsp.h"
# include "types.h"
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define MAP_HEIGHT 60

typedef unsigned long		t_pxl;

typedef enum e_map_char
{
	PLAYER = 'P',
	END = 'E',
	ENNEMY = '2',
	COLLECTIBLE = 'C',
	TREASURE = 'T',
	WALL = '1',
	EMPTY = '0',
}							t_map_char;

typedef enum e_map_side
{
	TOP,
	BOT,
	LEFT,
	RIGTH,
}							t_map_side;

typedef enum e_min_max
{
	MIN,
	MAX,
}							t_min_max;

typedef struct s_input
{
	bool					w;
	bool					a;
	bool					s;
	bool					d;
	bool					attack;
}							t_input;

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
	t_float2				coords;
	t_input					inputs;
	char					health;
}							t_player;

typedef struct s_timer
{
	struct timeval			last_frame;
	struct timeval			current_time;
	double					time;
	double					frame_target;
	double					delta_time;
}							t_timer;

typedef struct s_map
{
	char					**array;
	t_room					*rooms;
	int						room_nbr;
	t_vector2				size;
	t_vector2				exit;
}							t_map;

typedef struct s_data
{
	int						frames;
	t_map					map;
	t_timer					timer;
	t_player				player;
	t_ennemy				*ennemies;
	t_collectible			*collectibles;
}							t_data;

#endif