/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:00:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/30 02:07:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_map_coords_in_screen(t_window *window, t_map *map)
{
	// ft_printf("%d\n%d\n", ((map->actual.x) / 2) + ((map->actual.x) % 2) + 2,
	// 	((map->actual.y + 4) / 2) + ((map->actual.y + 4) % 2));
	// window->max.x = ((map->actual.x) / 2) + ((map->actual.x) % 2) + 2;
	// window->max.y = ((map->actual.y) / 2) + ((map->actual.y) % 2) + 2;
	window->min.x = 2;
	window->min.y = 2;
	window->max.x = map->actual.x + 2;
	window->max.y = map->actual.y + 2;
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
	while (screen_coords.y < map->actual.y + 4)
	{
		window->screen[screen_coords.y] = ft_calloc(sizeof(char),
				((map->actual.x + 4) + 1));
		map_coords.x = 0;
		screen_coords.x = 0;
		while (screen_coords.x < map->actual.x + 4)
			set_screen_array_c(&map_coords, &screen_coords, map, window);
		if (map_coords.x)
			map_coords.y++;
		ft_printf("%s\n", window->screen[screen_coords.y]);
		screen_coords.y++;
	}
}
