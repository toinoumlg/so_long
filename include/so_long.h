/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 18:50:56 by amalangu         ###   ########.fr       */
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

typedef struct collectibles
{
	int					x;
	int					y;
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
	int					player_starting_x;
	int					player_starting_y;
	int					exit_x;
	int					exit_y;
	t_collectibles		*collectibles;
}						t_map;

int						set_map(t_map *map);
int						check_map(t_map *map);

void					free_memory(t_map *map);
void					add_new_collectible(t_map *map, int x, int y);

// utils
void					print_array(t_map *map);

#endif
