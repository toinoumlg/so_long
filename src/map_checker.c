/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 23:15:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_border(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->array[y])
	{
		if (map->array[y][x] != '1')
			return (-1);
		if (x == map->width - 1)
		{
			y++;
			x = 0;
		}
		else if (y == 0 || y == map->height - 1)
			x++;
		else
			x += map->width - 1;
	}
	return (0);
}

int	else_if(t_map *map, int x, int y)
{
	if (map->array[y][x] == 'C')
		add_new_collectible(map, x, y);
	else if (map->array[y][x] == 'E')
	{
		if (!map->exit_x)
		{
			map->exit_x = x;
			map->exit_y = y;
		}
		else
			return (-1);
	}
	else if (map->array[y][x] == 'P')
	{
		if (!map->player_start_x)
		{
			map->player_start_x = x;
			map->player_start_y = y;
		}
		else
			return (-1);
	}
	return (0);
}

int	finder(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < map->height - 1 && x < map->width - 1)
	{
		if (!else_if(map, x, y))
			x++;
		else
			return (-1);
		if (x == map->width - 1)
		{
			x = 0;
			y++;
		}
	}
	if (!map->collectibles || !map->exit_x || !map->player_start_x)
		return (-1);
	return (0);
}

// x ordinate y abscissa
int	check_map(t_map *map)
{
	if (check_border(map) || finder(map))
		return (-1);
	a_star(map);
	return (0);
}
