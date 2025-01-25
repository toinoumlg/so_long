/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 01:06:41 by amalangu         ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct coords
{
	int						x;
	int						y;
}							t_coords;

typedef struct a_star_list
{
	float					f;
	t_coords				coords;
	struct a_star_list		*next;
}							t_a_star_list;

typedef struct possible_directions
{
	int						tmp_index;
	t_coords				*possible_directions;
}							t_possible_directions;

typedef struct cell
{
	float					f;
	float					h;
	float					g;
	t_coords				parent;
}							t_cell;

typedef struct s_collectibles
{
	t_coords				coords;
	struct s_collectibles	*next_collectible;
}							t_collectibles;

typedef struct s_map
{
	char					**array;
	char					**screen_res;
	char					*file_name;
	int						width;
	int						max_width;
	int						min_width;
	int						height;
	int						max_height;
	int						min_height;
	t_coords				player_start;
	t_coords				exit;
	t_collectibles			*collectibles;
}							t_map;

typedef struct s_new_values
{
	int						y;
	int						x;
	float					g;
	float					h;
	float					f;
}							t_new_values;

typedef struct s_a_star_struct
{
	t_cell					**cell_details;
	t_a_star_list			*open_list;
	signed char				**closed_list;
	t_a_star_list			*first;
	t_coords				start;
	t_coords				end;
	t_possible_directions	*possible_directions;
}							t_a_star_struct;

int							set_map(t_map *map);
int							check_map(t_map *map);
int							a_star(t_map *map);
void						start(t_map *map);

int							is_destination(int y, int x, t_coords end);
int							is_blocked(char **array, int y, int x);
float						calculate_new_h_value(int y, int x, t_coords end);

void						add_new_collectible(t_map *map, int x, int y);
t_coords					*init_possible_directions(void);
signed char					**init_closed_list(t_map *map);
t_a_star_list				*init_list(float f, int x, int y);
t_a_star_list				*add_to_list(t_a_star_list *open_list, float f,
								int y, int x);
t_cell						set_cell_details(t_new_values new, t_coords coords);
t_cell						**init_and_set_cell_details(t_coords start,
								t_map *map);
t_a_star_struct				found_destination(t_new_values new, t_coords actual,
								t_a_star_struct a_star);
t_a_star_struct				find_new_f(t_new_values new, t_coords actual,
								t_a_star_struct a_star);
t_a_star_struct				init_a_star(t_map *map, t_coords start,
								t_coords end,
								t_possible_directions *possible_directions);

void						free_memory(t_map *map);
void						free_a_star_search(signed char **closed_list,
								t_cell **cell_details, int map_height);
void						free_closed_list(signed char **closed_list,
								int map_height);
void						free_cell_details(t_cell **cell_details,
								int map_height);
// utils
void						print_array(t_map *map);
void						print_final_path(t_cell **cell_details,
								t_coords end);

#endif
