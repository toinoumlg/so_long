/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 22:16:21 by amalangu         ###   ########.fr       */
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
#  define GROUND1 "textures/world/ground/ground1.xpm"
#  define GROUND2 "textures/world/ground/ground2.xpm"
#  define WATER1 "textures/world/water/water1.xpm"
#  define WATER2 "textures/world/water/water2.xpm"
#  define BORDER_N "textures/world/borders/border_N.xpm"
#  define BORDER_NE "textures/world/borders/border_NE.xpm"
#  define BORDER_E "textures/world/borders/border_E.xpm"
#  define BORDER_SE "textures/world/borders/border_SE.xpm"
#  define BORDER_S "textures/world/borders/border_S.xpm"
#  define BORDER_SW "textures/world/borders/border_SW.xpm"
#  define BORDER_W "textures/world/borders/border_W.xpm"
#  define BORDER_NW "textures/world/borders/border_NW.xpm"
#  define WALL1 "textures/world/walls/wall1.xpm"
#  define WALL2 "textures/world/walls/wall2.xpm"
#  define WALL3 "textures/world/walls/wall3.xpm"
#  define WALL4 "textures/world/walls/wall4.xpm"
#  define WALL5 "textures/world/walls/wall5.xpm"
#  define WALL6 "textures/world/walls/wall6.xpm"
#  define WALL7 "textures/world/walls/wall7.xpm"
#  define PLAYER_IDLE1 "textures/player_idle1.xpm"
#  define COIN_R1 "textures/coins/coin_rotate2.xpm"
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
	t_coords				*possible_directions;
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
	char					found_end;
}							t_a_star_struct;

typedef struct s_window
{
	void					*ptr;
	char					**screen;
	t_coords				start;
	t_coords				max;
	t_coords				min;
	t_coords				actual;
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
	t_image					*player;
	t_image					*coins_r;
}							t_textures;

typedef struct s_data
{
	void					*mlx;
	clock_t					t;
	double					time_taken;
	t_textures				textures;
	t_window				window;
	t_map					*map;
}							t_data;

// main
int							set_map(t_map *map);
int							a_star(t_map *map);
void						start(t_data data);

// a_star
void						init_a_star(t_map *map, t_coords start,
								t_coords end, t_a_star_struct *a_star);
t_cell						**init_and_set_cell_details(t_coords start,
								t_map *map);
t_cell						set_cell_details(t_new_values new, t_coords coords);
void						init_possible_directions(t_map *map);
t_a_star_list				*init_list(float f, int x, int y);
t_a_star_list				*add_to_list(t_a_star_list *open_list, float f,
								int y, int x);
t_a_star_list				*move_lowest_f_to_front(t_a_star_list **open_list);
signed char					**init_closed_list(t_map *map);
int							is_destination(int y, int x, t_coords end);
int							is_blocked(char **array, int y, int x);
float						calculate_new_h_value(int y, int x, t_coords end);
void						found_destination(t_new_values new, t_coords actual,
								t_a_star_struct *a_star);
void						find_new_f(t_new_values new, t_coords actual,
								t_a_star_struct *a_star);

// map
int							check_map(t_map *map);
void						add_new_collectible(t_map *map, int x, int y);

// game
// ==> start
void						set_textures(t_textures *textures, void *mlx);
void						init_window(t_map *map, t_window *window, void *mlx,
								t_textures textures);
// ==> textures
void						combine_image(t_image front, t_image background,
								void *mlx, t_window window);
// ==> window
void						get_map_coords_in_screen(t_window *window,
								t_map *map);
void						init_screen_array(t_map *map, t_window *window);
void						print_screen_array(char **screen,
								t_textures textures, t_window *window,
								void *mlx);

// free
void						free_memory_map(t_map *map);
void						free_a_star_search(t_a_star_struct a_star,
								int map_height);
void						free_game(t_data data);
void						free_open_list(t_a_star_list *open_list);

// test utils
void						print_array(char **array);
void						test_print_final_path(t_cell **cell_details,
								t_coords end);
void						print_list(t_a_star_list *list);

#endif
