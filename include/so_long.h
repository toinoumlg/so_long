/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/22 18:49:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef PIXEL_PADDING
#  define PIXEL_PADDING 32
# endif

# ifndef MAX_COLLECTIBLES
#  define MAX_COLLECTIBLES 30
# endif

# include "../libftprintf/include/ft_printf.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct coords
{
	int					x;
	int					y;
}						t_coords;

typedef struct a_star_list
{
	float				f;
	t_coords			coords;
	struct a_star_list	*next;
}						t_a_star_list;

typedef struct possible_directions
{
	int					tmp_index;
	t_coords			*possible_directions;
}						t_possible_directions;

typedef struct cell
{
	float				f;
	float				h;
	float				g;
	t_coords			parent;
}						t_cell;

typedef struct collectibles
{
	float				x;
	float				y;
	struct collectibles	*next_collectible;
}						t_collectibles;

typedef struct map
{
	char				**array;
	char				**screen_res;
	char				*file_name;
	int					width;
	int					max_width;
	int					min_width;
	int					height;
	int					max_height;
	int					min_height;
	float				player_start_x;
	float				player_start_y;
	float				exit_x;
	float				exit_y;
	t_collectibles		*collectibles;
}						t_map;

int						set_map(t_map *map);
int						check_map(t_map *map);

void					init_list(t_a_star_list *list, float f, int x, int y);
void					free_memory(t_map *map);
void					add_new_collectible(t_map *map, int x, int y);
void					set_list(t_a_star_list *list, float f, int x, int y);
int						a_star(t_map *map);

// utils
void					print_array(t_map *map);

#endif
