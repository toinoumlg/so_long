/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 14:32:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef PIXEL_PADDING
#  define PIXEL_PADDING 32
# endif

# include "../libftprintf/include/ft_printf.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct map
{
	char	**array;
	char	**screen_res;
	char	*file_name;
	int		width;
	int		max_width;
	int		min_width;
	int		height;
	int		max_height;
	int		min_height;
}			t_map;

int			set_map(t_map *map);

void		free_memory(t_map *map);
void		check_map(t_map *map);

#endif
