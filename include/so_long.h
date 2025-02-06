/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/04 20:28:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef INCLUDES
#  include "../libftprintf/include/ft_printf.h"
#  include "../mlx/mlx.h"
#  include "../mlx/mlx_int.h"
#  include <math.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <time.h>
# endif

# ifndef VARS
#  define PIXEL_PADDING 32
#  define SCREEN_HEIGHT 2560
#  define SCREEN_WIDTH 1440
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
#  define DEBBUG "debbug.ber"
# endif

# ifndef TEXTURES
#  define EXIT1 "textures/world/ground/exit1.xpm"
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
#  define COIN_R1 "textures/coins/coin_rotate1.xpm"
#  define COIN_R2 "textures/coins/coin_rotate2.xpm"
#  define COIN_R3 "textures/coins/coin_rotate3.xpm"
#  define COIN_R4 "textures/coins/coin_rotate4.xpm"
#  define COIN_R5 "textures/coins/coin_rotate5.xpm"
#  define COIN_R6 "textures/coins/coin_rotate6.xpm"
#  define COIN_R7 "textures/coins/coin_rotate7.xpm"
#  define COIN_R8 "textures/coins/coin_rotate8.xpm"
#  define COIN_R9 "textures/coins/coin_rotate9.xpm"
#  define COIN_R10 "textures/coins/coin_rotate10.xpm"
#  define COIN_R11 "textures/coins/coin_rotate11.xpm"
#  define COIN_R12 "textures/coins/coin_rotate12.xpm"
#  define COIN_R13 "textures/coins/coin_rotate13.xpm"
# endif

typedef struct s_vector2
{
	int						x;
	int						y;
}							t_vector2;

typedef struct a_star_list
{
	float					f;
	t_vector2				coords;
	struct a_star_list		*next;
}							t_a_star_list;

typedef struct cell
{
	float					f;
	float					h;
	float					g;
	t_vector2				parent;
}							t_cell;

typedef struct s_collectibles
{
	t_vector2				coords;
	int						i_image;
	struct s_collectibles	*next_collectible;
}							t_collectibles;

typedef struct s_possible_directions
{
	t_vector2				up;
	t_vector2				down;
	t_vector2				left;
	t_vector2				right;
	t_vector2				zero;
}							t_possible_directions;

typedef struct s_map
{
	char					**array;
	char					*file_name;
	t_vector2				actual;
	t_vector2				min;
	t_vector2				max;
	t_possible_directions	direction;
	t_vector2				player_start;
	t_vector2				exit;
	t_collectibles			*collectibles;
}							t_map;

typedef struct s_new_values
{
	t_vector2				parent;
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
	t_vector2				start;
	t_vector2				end;
	char					found_end;
}							t_a_star_struct;

typedef struct s_window
{
	void					*ptr;
	char					**screen;
	t_vector2				max;
	t_vector2				min;
	t_vector2				move;
	t_vector2				actual;
	t_vector2				exit;
}							t_window;

typedef struct s_image
{
	void					*image;
	char					*addr;
	t_vector2				wh;
	int						size_l;
	int						bpp;
	int						endian;
}							t_image;

typedef struct s_textures
{
	t_image					*ground;
	t_image					*water;
	t_image					*walls;
	t_image					*borders;
	t_image					*player;
	t_image					*coins_r;
	t_image					*exit;
}							t_textures;

typedef struct s_player
{
	int						is_moving;
	int						moves;
}							t_player;

typedef struct s_game
{
	t_collectibles			*collectibles;
	t_possible_directions	moves;
	t_player				player;
	int						game_finished;

}							t_game;

typedef struct s_timer
{
	clock_t					start;
	clock_t					end;
	double					time;
}							t_timer;

typedef struct s_data
{
	int						frames;
	void					*mlx;
	t_textures				textures;
	t_window				window;
	t_game					game;
	t_map					*map;
	t_timer					timer;
}							t_data;

// main
int							set_map(t_map *map);
int							a_star(t_map *map);
void						game(t_data data);

// a_star
void						init_a_star(t_map *map, t_vector2 start,
								t_vector2 end, t_a_star_struct *a_star);
t_cell						**init_and_set_cell_details(t_vector2 start,
								t_map *map);
t_cell						set_cell_details(t_new_values new,
								t_vector2 coords);
void						init_possible_directions(t_map *map);
t_a_star_list				*init_list(float f, int x, int y);
t_a_star_list				*add_to_list(t_a_star_list *open_list, float f,
								int y, int x);
t_a_star_list				*move_lowest_f_to_front(t_a_star_list **open_list);
signed char					**init_closed_list(t_map *map);
t_vector2					set_vector2(int y, int x);
int							is_destination(t_vector2 actual, t_vector2 end);
int							is_blocked(char **array, t_vector2 coords);
float						calculate_new_h_value(int y, int x, t_vector2 end);
void						found_destination(t_vector2 new, t_vector2 actual,
								t_a_star_struct *a_star);
void						find_new_f(t_new_values new, t_vector2 actual,
								t_a_star_struct *a_star);

// map
int							check_map(t_map *map);
t_possible_directions		set_move(void);

// game
// ==> start
void						init_game(t_data *data);
void						set_textures(t_data *data);
void						init_window(t_map *map, t_window *window, void *mlx,
								t_textures textures);
// ==> textures
void						set_textures_coins(t_image *coins, void *mlx);
void						set_textures_walls(t_image *walls, void *mlx);
void						combine_image(t_image front, t_image background,
								void *mlx, t_window window);
void						set_background_color(t_image *background,
								t_image *combined);
void						set_front_color_offset(t_image *front,
								t_image *combined);
void						set_front_color(t_image *front, t_image *combined);
void						print_player(t_data *data);
void						print_collectibles(t_data *data,
								t_collectibles *tmp);
unsigned int				get_pixel_color(t_image *image, t_vector2 i);
void						put_pixel(t_image *image, t_vector2 i,
								unsigned int color);
void						spawn_exit(t_data *data);
// ==> window
void						get_map_coords_in_screen(t_window *window,
								t_map *map);
void						init_screen_array(t_map *map, t_window *window);
void						print_screen_array(char **screen,
								t_textures textures, t_window *window,
								void *mlx);
void						update_screen_array(t_data *data);
void						move_player(int key_stroked, t_data *data);
// ==> collectibles
void						add_new_collectible(t_map *map, int x, int y);
void						update_collectible_coords(t_collectibles *collectibles,
								t_vector2 min);
void						destroy_collectible(t_collectibles **collectibles,
								t_vector2 coords);
void						update_collectibles(t_data *data);
// free
void						free_memory_map(t_map *map);
void						free_a_star_search(t_a_star_struct a_star,
								int map_height);
void						free_game(t_data data);
void						free_open_list(t_a_star_list *open_list);
void						free_collectibles(t_collectibles *collectibles);
// test utils
void						print_array(char **array);
void						print_actual_arrays(t_data *data);
int							trace_path(t_cell **cell_details, t_vector2 end,
								char found);
void						print_list(t_collectibles *list);

#endif
