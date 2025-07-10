/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/10 13:49:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef INCLUDES
#  include "check.h"
#  include "data.h"
#  include "mem.h"
#  include "mlx.h"
#  include "mlx_int.h"
#  include "put.h"
#  include "str.h"
#  include "swap.h"
#  include <math.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <sys/time.h>
# endif

# ifndef VARS
#  define PIXEL_PADDING 32
# endif

// main
void					map_parser(t_data *data, char **av, int ac);
void					check_valid_paths(t_data *data);
void					start_game(t_data data);

// a_star
int						init_a_star(t_data *data, t_vector2 start,
							t_vector2 end, t_a_star *a_star);
void					free_closed_list(signed char **closed_list, int height);
void					a_star_search(t_vector2 start, t_vector2 end,
							t_data *data);
void					free_cell_details(t_a_star_values **cell_details,
							int height);
void					init_and_set_cell_details(t_a_star *a_star,
							t_vector2 start, t_data *data);
void					a_star_neighbor(t_a_star *a_star, t_data *data);
t_a_star_values			set_cell_details(t_a_star_values new, t_vector2 coords);
void					init_possible_directions(t_map *map);
void					init_list(t_a_star *a_star, float f, int x, int y);
void					add_to_list(t_open_list **open_list,
							t_a_star_values values);
void					sort_open_list(t_open_list **open_list);
void					init_closed_list(t_a_star *a_star, t_data *data);
t_vector2				set_vector2(int y, int x);
int						is_destination(t_vector2 actual, t_vector2 end);
int						is_blocked(char **array, t_vector2 actual);
float					calculate_new_h_value(int y, int x, t_vector2 end);
void					found_destination(t_vector2 new, t_vector2 actual,
							t_a_star *a_star);
void					find_new_f(t_a_star_values new, t_vector2 actual,
							t_a_star *a_star);

// map
void					check_map(t_data *data);
t_possible_directions	set_move(void);

// game
// ==> start
int						init_game(t_data *data);
int						set_textures(t_data *data);
int						init_window(t_map *map, t_window *window, void *mlx,
							t_textures textures);
// ==> update
int						update(t_data *data);
int						can_player_attack(int key_stroked, t_data *data);
int						can_player_move(int key_stroked, t_data *data);
void					get_current_time(t_data *data);
void					print_object_on_map(t_data *data);
void					update_entities(t_data *data);
void					update_frames(t_data *data);
// ==> textures
void					set_textures_ennemies(t_image *ennemies, void *mlx);
void					set_textures_coins(t_image *coins, void *mlx);
void					set_textures_player(t_image *player, t_image *sword,
							void *mlx);
void					set_textures_border(t_image *borders, void *mlx);
void					set_textures_exit(t_image *exit, void *mlx);
void					set_textures_water(t_image *water, void *mlx);
void					set_textures_ground(t_image *ground, void *mlx);
void					set_textures_hud(t_image *hud, void *mlx);
void					set_textures_walls(t_image *walls, void *mlx);
void					combine_image(t_image front, t_image background,
							void *mlx, t_window window);
void					set_background_color(t_image *background,
							t_image *combined);
void					set_front_color_offset(t_image *front,
							t_image *combined);
void					set_front_color(t_image *front, t_image *combined);
void					print_player(t_data *data);
void					print_ennemies(t_data *data, t_ennemy *tmp);
void					print_ennemy_move(t_data *data, t_ennemy *ennemy);
void					print_collectibles(t_data *data, t_collectible *tmp);
void					print_hud(t_data *data);
void					print_hud_empty(t_data *data, int i);
void					print_hud_right_corner(t_data *data, int i);
void					print_hud_left_corner(t_data *data, int i);
char					*string_hud(t_data *data);
void					print_hud_time(t_data *data);
void					print_hud_move(t_data *data);
void					print_hud_health(t_data *data);
void					print_hud_swords(t_data *data);
void					print_seconds(t_data *data);
void					is_sword_printed(t_data *data);
void					is_ennemy_printed(t_data *data);
void					is_ennemy_on_collectible(t_data *data,
							t_collectible *collectible);
void					is_sword_on_collectible(t_data *data,
							t_collectible *collectible);
void					collectible_and_ennemy_move_print(t_data *data,
							t_collectible *collectible, t_ennemy *ennemy);
void					is_collectible_printed(t_data *data);
void					player_attack(int key_stroked, t_data *data);
void					collectible_and_ennemy_print(t_data *data,
							t_collectible *collectible, t_ennemy *ennemy);
void					collectible_and_sword_print(t_data *data,
							t_collectible *collectible, t_sword *sword);
void					collectible_and_sword_move_print(t_data *data,
							t_collectible *collectible, t_sword *sword);
unsigned int			get_pixel_color(t_image *image, t_vector2 i);
void					put_pixel(t_image *image, t_vector2 i,
							unsigned int color);
void					spawn_exit(t_data *data);
void					update_index(t_data *data);
// ==> window
void					get_map_coords_in_screen(t_window *window, t_map *map);
int						init_screen_array(t_map *map, t_window *window);
void					print_screen_array(char **screen, t_textures textures,
							t_window *window, void *mlx);
void					update_screen_array(t_data *data);
void					player_move(int key_stroked, t_data *data);
// ==> player
void					update_swords(t_data *data);
void					spawn_sword(t_data *data, t_vector2 direction);
t_vector2				sword_next_pos(t_sword *sword);
void					print_sword(t_data *data, t_sword *sword);
void					destroy_sword(t_sword **swords, t_vector2 coords,
							t_data *data);
void					set_player_direction(int key_stroked, t_data *data);
int						is_next_coords_blocked(t_data *data);
int						is_ennemy_on_next_coords(t_data *data,
							t_ennemy *ennemy);
// ==> sword
void					is_sword_ended(t_data *data, t_sword *sword);
void					is_sword_blocked(t_data *data, t_sword *sword);
int						set_sword_index(t_vector2 direction);
int						check_sword_on_collectible(t_sword *sword,
							t_collectible *collectible);
// ==> collectible
void					add_collectible(t_data *data, int x, int y);
void					update_collectible_coords(t_collectible *collectibles,
							t_vector2 min);
void					destroy_collectible(t_collectible **collectibles,
							t_vector2 coords);
void					update_collectibles(t_data *data);
// ==> ennemy
void					add_ennemy(t_data *data, int x, int y);
void					update_ennemies_coords(t_ennemy *ennemies,
							t_vector2 coords);
void					update_ennemies(t_data *data);
void					destroy_ennemy(t_ennemy **ennemies, t_vector2 coords,
							t_data *data);
// free
void					free_map(t_map *map);
void					free_a_star_search(t_a_star *a_star, int height);
void					free_game(t_data data);
void					free_open_list(t_open_list *open_list);
void					free_collectibles(t_collectible *collectibles);
void					free_ennemies(t_ennemy *ennemies);
void					free_images_start(t_data data);
void					free_images_end(t_data data);
void					free_textures(t_textures textures);
void					free_failed_textures_init(t_data data);
void					free_failed_window_init(t_data data);
void					free_array(char **array);

// test utils
void					print_array(char **array, t_vector2 end);
void					print_actual_arrays(t_data *data);
void					print_list(t_collectible *list);
void					print_a_star(t_a_star a_star, char **array);

#endif
