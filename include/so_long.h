/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:04:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/20 19:48:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H


# include "../mlx/mlx.h"
# include "../libftprintf/include/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct map {
	char **array;
	char **screen_res;
	char *file_name;
	int width;
	int height;
	int max_width;
	int max_height;
}	t_map;


#endif
