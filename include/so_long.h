/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:59:55 by amalangu         ###   ########.fr       */
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
#  include <sys/time.h>
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
#  define PLAYER_IDLE1 "textures/player/idle/player_idle1.xpm"
#  define PLAYER_IDLE2 "textures/player/idle/player_idle2.xpm"
#  define PLAYER_IDLE3 "textures/player/idle/player_idle3.xpm"
#  define PLAYER_IDLE4 "textures/player/idle/player_idle4.xpm"
#  define PLAYER_IDLE5 "textures/player/idle/player_idle5.xpm"
#  define SWORD1 "textures/player/axe/sword1.xpm"
#  define SWORD2 "textures/player/axe/sword2.xpm"
#  define SWORD3 "textures/player/axe/sword3.xpm"
#  define SWORD4 "textures/player/axe/sword4.xpm"
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
#  define ENNEMY1 "textures/ennemies/ennemies1.xpm"
#  define ENNEMY2 "textures/ennemies/ennemies2.xpm"
#  define ENNEMY3 "textures/ennemies/ennemies3.xpm"
#  define ENNEMY4 "textures/ennemies/ennemies4.xpm"
#  define ENNEMY5 "textures/ennemies/ennemies5.xpm"
#  define ENNEMY6 "textures/ennemies/ennemies6.xpm"
#  define ENNEMY7 "textures/ennemies/ennemies7.xpm"
#  define ENNEMY8 "textures/ennemies/ennemies8.xpm"
#  define ENNEMY9 "textures/ennemies/ennemies9.xpm"
#  define ENNEMY10 "textures/ennemies/ennemies10.xpm"
#  define ENNEMY11 "textures/ennemies/ennemies11.xpm"
#  define ENNEMY12 "textures/ennemies/ennemies12.xpm"
#  define ENNEMY13 "textures/ennemies/ennemies13.xpm"
#  define ENNEMY14 "textures/ennemies/ennemies14.xpm"
#  define ENNEMY15 "textures/ennemies/ennemies15.xpm"
#  define ENNEMY16 "textures/ennemies/ennemies16.xpm"
#  define ENNEMY17 "textures/ennemies/ennemies17.xpm"
#  define ENNEMY18 "textures/ennemies/ennemies18.xpm"
#  define ENNEMY19 "textures/ennemies/ennemies19.xpm"
#  define ENNEMY20 "textures/ennemies/ennemies20.xpm"
#  define ENNEMY21 "textures/ennemies/ennemies21.xpm"
#  define HUD1 "textures/hud/hud1.xpm"
#  define HUD2 "textures/hud/hud2.xpm"
#  define HUD3 "textures/hud/hud3.xpm"
#  define HUD4 "textures/hud/heart.xpm"
#  define HUD5 "textures/hud/sword.xpm"
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

typedef struct s_collectible
{
	t_vector2				coords;
	int						i_image;
	int						is_printed;
	struct s_collectible	*next_collectible;
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
	struct s_ennemy			*next_ennemy;
}							t_ennemy;

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
	t_collectible			*collectibles;
	t_ennemy				*ennemies;
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
int							init_a_star(t_map *map, t_vector2 start,
								t_vector2 end, t_a_star_struct *a_star);
void						free_closed_list(signed char **closed_list,
								int map_height);
int							a_star_search(t_vector2 start, t_vector2 end,
								t_map *map);
void						free_cell_details(t_cell **cell_details,
								int map_height);
t_cell						**init_and_set_cell_details(t_vector2 start,
								t_vector2 max);
void						a_star_loop(t_a_star_struct *a_star, char **array,
								t_possible_directions direction);
t_cell						set_cell_details(t_new_values new,
								t_vector2 coords);
void						init_possible_directions(t_map *map);
t_a_star_list				*init_list(float f, int x, int y);
t_a_star_list				*add_to_list(t_a_star_list *open_list, float f,
								int y, int x);
t_a_star_list				*move_lowest_f_to_front(t_a_star_list **open_list);
signed char					**init_closed_list(t_vector2 max);
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
int							init_game(t_data *data);
int							set_textures(t_data *data);
int							init_window(t_map *map, t_window *window, void *mlx,
								t_textures textures);
// ==> update
int							update(t_data *data);
int							can_player_attack(int key_stroked, t_data *data);
int							can_player_move(int key_stroked, t_data *data);
void						get_current_time(t_data *data);
void						print_object_on_map(t_data *data);
void						update_entities(t_data *data);
void						update_frames(t_data *data);
// ==> textures
void						set_textures_ennemies(t_image *ennemies, void *mlx);
void						set_textures_coins(t_image *coins, void *mlx);
void						set_textures_player(t_image *player, t_image *sword,
								void *mlx);
void						set_textures_border(t_image *borders, void *mlx);
void						set_textures_exit(t_image *exit, void *mlx);
void						set_textures_water(t_image *water, void *mlx);
void						set_textures_ground(t_image *ground, void *mlx);
void						set_textures_hud(t_image *hud, void *mlx);
void						set_textures_walls(t_image *walls, void *mlx);
void						combine_image(t_image front, t_image background,
								void *mlx, t_window window);
void						set_background_color(t_image *background,
								t_image *combined);
void						set_front_color_offset(t_image *front,
								t_image *combined);
void						set_front_color(t_image *front, t_image *combined);
void						print_player(t_data *data);
void						print_ennemies(t_data *data, t_ennemy *tmp);
void						print_ennemy_move(t_data *data, t_ennemy *ennemy);
void						print_collectibles(t_data *data,
								t_collectible *tmp);
void						print_hud(t_data *data);
void						print_hud_empty(t_data *data, int i);
void						print_hud_right_corner(t_data *data, int i);
void						print_hud_left_corner(t_data *data, int i);
char						*string_hud(t_data *data);
void						print_hud_time(t_data *data);
void						print_hud_move(t_data *data);
void						print_hud_health(t_data *data);
void						print_hud_swords(t_data *data);
void						print_seconds(t_data *data);
void						is_sword_printed(t_data *data);
void						is_ennemy_printed(t_data *data);
void						is_ennemy_on_collectible(t_data *data,
								t_collectible *collectible);
void						is_sword_on_collectible(t_data *data,
								t_collectible *collectible);
void						collectible_and_ennemy_move_print(t_data *data,
								t_collectible *collectible, t_ennemy *ennemy);
void						is_collectible_printed(t_data *data);
void						player_attack(int key_stroked, t_data *data);
void						collectible_and_ennemy_print(t_data *data,
								t_collectible *collectible, t_ennemy *ennemy);
void						collectible_and_sword_print(t_data *data,
								t_collectible *collectible, t_sword *sword);
void						collectible_and_sword_move_print(t_data *data,
								t_collectible *collectible, t_sword *sword);
unsigned int				get_pixel_color(t_image *image, t_vector2 i);
void						put_pixel(t_image *image, t_vector2 i,
								unsigned int color);
void						spawn_exit(t_data *data);
void						update_index(t_data *data);
// ==> window
void						get_map_coords_in_screen(t_window *window,
								t_map *map);
int							init_screen_array(t_map *map, t_window *window);
void						print_screen_array(char **screen,
								t_textures textures, t_window *window,
								void *mlx);
void						update_screen_array(t_data *data);
void						player_move(int key_stroked, t_data *data);
// ==> player
void						update_swords(t_data *data);
void						spawn_sword(t_data *data, t_vector2 direction);
t_vector2					sword_next_pos(t_sword *sword);
void						print_sword(t_data *data, t_sword *sword);
void						destroy_sword(t_sword **swords, t_vector2 coords,
								t_data *data);
void						set_player_direction(int key_stroked, t_data *data);
int							is_next_coords_blocked(t_data *data);
int							is_ennemy_on_next_coords(t_data *data,
								t_ennemy *ennemy);
// ==> sword
void						is_sword_ended(t_data *data, t_sword *sword);
void						is_sword_blocked(t_data *data, t_sword *sword);
int							set_sword_index(t_vector2 direction);
int							check_sword_on_collectible(t_sword *sword,
								t_collectible *collectible);
// ==> collectible
int							add_new_collectible(t_map *map, int x, int y);
void						update_collectible_coords(
								t_collectible *collectibles, t_vector2 min);
void						destroy_collectible(t_collectible **collectibles,
								t_vector2 coords);
void						update_collectibles(t_data *data);
// ==> ennemy
int							add_new_ennemy(t_map *map, int x, int y);
void						update_ennemies_coords(t_ennemy *ennemies,
								t_vector2 coords);
void						update_ennemies(t_data *data);
void						destroy_ennemy(t_ennemy **ennemies,
								t_vector2 coords, t_data *data);
// free
void						free_map(t_map *map);
void						free_a_star_search(t_a_star_struct a_star,
								int map_height);
void						free_game(t_data data);
void						free_open_list(t_a_star_list *open_list);
void						free_collectibles(t_collectible *collectibles);
void						free_ennemies(t_ennemy *ennemies);
void						free_images_start(t_data data);
void						free_images_end(t_data data);
void						free_textures(t_textures textures);
void						free_failed_textures_init(t_data data);
void						free_failed_window_init(t_data data);
void						free_array(char **array);

// test utils
void						print_array(char **array);
void						print_actual_arrays(t_data *data);
void						print_list(t_collectible *list);

#endif
