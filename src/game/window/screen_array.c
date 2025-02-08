/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:00:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/07 21:36:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"



void	update_screen_array(t_data *data)
{
	t_vector2	new_coords;

	new_coords = set_vector2(data->window.actual.y + data->window.move.y,
			data->window.actual.x + data->window.move.x);
	data->window.screen[data->window.actual.y][data->window.actual.x] = '0';
	if (data->window.screen[new_coords.y][new_coords.x] == 'C')
	{
		destroy_collectible(&data->game.collectibles, new_coords);
		if (!data->game.collectibles)
			data->game.game_finished = 1;
	}
	if ((new_coords.x == data->window.exit.x
			&& new_coords.y == data->window.exit.y)
		&& data->game.game_finished == 2)
		data->game.game_finished = 3;
	data->window.screen[new_coords.y][new_coords.x] = 'P';
	data->game.player.status = 1;
}

int	is_in_map(t_vector2 screen, t_window *window)
{
	if ((screen.x >= window->min.x && screen.x < window->max.x)
		&& (screen.y >= window->min.y && screen.y < window->max.y))
		return (1);
	else
		return (0);
}

void	set_screen_array_c(t_vector2 *map_coords, t_vector2 *screen_coords,
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
	t_vector2	screen_coords;
	t_vector2	map_coords;

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
		screen_coords.y++;
	}
}

void	print_actual_arrays(t_data *data)
{
	int	i;

	i = 0;
	ft_printf("actual %d %d\nscreen:\n", data->window.actual.x,
		data->window.actual.y);
	while (data->window.screen[i])
	{
		ft_printf("[%d]-%s\n", i, data->window.screen[i]);
		i++;
	}
}
