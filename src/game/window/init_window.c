/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/30 02:21:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_window(t_map *map, t_window *window, void *mlx,
		t_textures textures)
{
	window->screen = ft_calloc(sizeof(char *), (map->actual.y + 4) + 1);
	get_map_coords_in_screen(window, map);
	init_screen_array(map, window);
	window->ptr = mlx_new_window(mlx, (map->actual.x + 4) * PIXEL_PADDING,
			(map->actual.y + 4) * PIXEL_PADDING, "caca dans culotte");
	print_screen_array(window->screen, textures, window, mlx);
	window->exit.x = map->exit.x + window->min.x;
	window->exit.y = map->exit.y + window->min.y;
	window->actual.x = map->player_start.x + window->min.x;
	window->actual.y = map->player_start.y + window->min.y;
	free_memory_map(map);
}
