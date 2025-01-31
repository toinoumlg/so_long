/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/31 14:13:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_window(t_map *map, t_window *window, void *mlx,
		t_textures textures)
{
	window->screen = ft_calloc(sizeof(char *), (map->actual.y + 4) + 1);
	window->min = set_vector2(2, 2);
	window->max = set_vector2(map->actual.y + 2, map->actual.x + 2);
	init_screen_array(map, window);
	window->ptr = mlx_new_window(mlx, (map->actual.x + 4) * PIXEL_PADDING,
			(map->actual.y + 4) * PIXEL_PADDING, "caca dans culotte");
	print_screen_array(window->screen, textures, window, mlx);
	window->exit = set_vector2(map->exit.y + window->min.y, map->exit.x
			+ window->min.x);
	window->actual = set_vector2(map->player_start.y + window->min.y,
			map->player_start.x + window->min.x);
	free_memory_map(map);
}
