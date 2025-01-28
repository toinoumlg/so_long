/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 17:30:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_window(t_map *map, t_window *window, void *mlx,
		t_textures textures)
{
	window->screen = ft_calloc(sizeof(char *), SCREEN_HEIGHT / PIXEL_PADDING
			+ 1);
	get_map_coords_in_screen(window, map);
	init_screen_array(map, window);
	window->ptr = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"caca dans culotte");
	print_screen_array(window->screen, textures, window, mlx);
}