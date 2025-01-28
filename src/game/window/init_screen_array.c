/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:00:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 17:31:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_map_coords_in_screen(t_window *window, t_map *map)
{
	window->max.x = (SCREEN_WIDTH / PIXEL_PADDING / 2) + (map->width / 2)
		+ (map->width % 2);
	window->max.y = (SCREEN_HEIGHT / PIXEL_PADDING / 2) + (map->height / 2)
		+ (map->height % 2);
	window->min.x = (SCREEN_WIDTH / PIXEL_PADDING / 2) - (map->width / 2);
	window->min.y = (SCREEN_HEIGHT / PIXEL_PADDING / 2) - (map->height / 2);
}

int	is_in_map(t_coords screen, t_window *window)
{
	if ((screen.x >= window->min.x && screen.x < window->max.x)
		&& (screen.y >= window->min.y && screen.y < window->max.y))
		return (1);
	else
		return (0);
}

void	set_screen_array_c(t_coords *map_coords, t_coords *screen_coords,
		t_map *map, t_window *window)
{
	if (is_in_map(*screen_coords, window))
	{
		window->screen[screen_coords->y][screen_coords->x] = map->array[map_coords->y][map_coords->x];
		map_coords->x++;
	}
	else
		window->screen[screen_coords->y][screen_coords->x] = 'W';
	screen_coords->x++;
}

void	init_screen_array(t_map *map, t_window *window)
{
	t_coords	screen_coords;
	t_coords	map_coords;

	screen_coords.y = 0;
	map_coords.y = 0;
	while (screen_coords.y < SCREEN_HEIGHT / PIXEL_PADDING)
	{
		window->screen[screen_coords.y] = ft_calloc(sizeof(char), (SCREEN_WIDTH
					/ PIXEL_PADDING) + 1);
		map_coords.x = 0;
		screen_coords.x = 0;
		while (screen_coords.x < SCREEN_WIDTH / PIXEL_PADDING)
			set_screen_array_c(&map_coords, &screen_coords, map, window);
		if (map_coords.x)
			map_coords.y++;
		screen_coords.y++;
	}
}
