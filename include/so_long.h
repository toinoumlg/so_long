/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 01:07:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef INCLUDES
#  include "../libftprintf/include/ft_printf.h"
#  include "../mlx/mlx.h"
#  include <X11/X.h>
#  include <X11/keysym.h>
#  include <fcntl.h>
#  include <math.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <time.h>
#  include <unistd.h>
# endif

# ifndef VARS
#  define PIXEL_PADDING 32
#  define SCREEN_HEIGHT 1056
#  define SCREEN_WIDTH 1920
#  define MAX_COLLECTIBLES 200
# endif

# ifndef FT_PRINTF_COLORS
#  define RESET "\x1B[0m"
#  define RED "\x1B[31m"
#  define GREEN "\x1B[32m"
#  define YELLOW "\x1B[33m"
#  define BLUE "\x1B[34m"
#  define MAGENTA "\x1B[35m"
#  define CYAN "\x1B[36m"
#  define WHITE "\x1B[37m"
# endif

# ifndef MAPS
#  define PATH "maps/"
#  define BER ".ber"
#  define DEBBUG "debbug"
# endif

# ifndef TEXTURES
#  define GROUND1 "textures/ground1.xpm"
#  define GROUND2 "textures/ground2.xpm"
#  define WATER1 "textures/water1.xpm"
#  define WATER2 "textures/water2.xpm"
#  define BORDER_N "textures/border_N.xpm"
#  define BORDER_NE "textures/border_NE.xpm"
#  define BORDER_E "textures/border_E.xpm"
#  define BORDER_SE "textures/border_SE.xpm"
#  define BORDER_S "textures/border_S.xpm"
#  define BORDER_SW "textures/border_SW.xpm"
#  define BORDER_W "textures/border_W.xpm"
#  define BORDER_NW "textures/border_NW.xpm"
#  define WALL1 "textures/wall1.xpm"
#  define WALL2 "textures/wall2.xpm"
#  define WALL3 "textures/wall3.xpm"
#  define WALL4 "textures/wall4.xpm"
#  define WALL5 "textures/wall5.xpm"
#  define WALL6 "textures/wall6.xpm"
#  define WALL7 "textures/wall7.xpm"
#  define PLAYER_IDLE1 "textures/player_idle1.xpm"
# endif

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
	char					found_end;
}							t_a_star_struct;

typedef struct s_window
{
	void					*ptr;
	char					**screen;
	t_coords				max;
	t_coords				min;
}							t_window;

typedef struct s_image
{
	void					*image;
	char					*addr;
	t_coords				wh;
	int						size_l;
	int						bpp;
	int						endian;
}							t_image;

typedef struct s_textures
{
	t_image					*ground;
	t_image					*water;
	t_image					*walls;
	t_image					*border;
}							t_textures;

typedef struct s_data
{
	void					*mlx;
	t_textures				textures;
	t_window				window;
	t_map					*map;
}							t_data;

int							set_map(t_map *map);
int							check_map(t_map *map);
int							a_star(t_map *map);
void						start(t_data data);

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
void						print_list(t_a_star_list *list);
void						set_textures(t_textures *textures, void *mlx);
void						get_map_coords_in_screen(t_window *window,
								t_map *map);
void						init_screen_array(t_map *map, t_window window);
void						init_window(t_map *map, t_window window, void *mlx,
								t_textures textures);
void						free_memory_map(t_map *map);
void						free_a_star_search(t_a_star_struct a_star,
								int map_height);

void						free_open_list(t_a_star_list *open_list);
// utils
void						print_array(char **array);
void						print_final_path(t_cell **cell_details,
								t_coords end);

#endif
