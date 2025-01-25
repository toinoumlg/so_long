/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 13:10:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_if_rectangular(t_map *map)
{
	char	*tmp;
	char	*cr;
	int		i;

	i = 0;
	while (i < map->height)
	{
		cr = ft_strchr(map->array[i], '\n');
		if (cr)
		{
			map->array[i] = ft_strtrim((tmp = map->array[i]), cr);
			free(tmp);
		}
		if (((int)ft_strlen(map->array[i])) != map->width)
			return (-1);
		i++;
	}
	return (0);
}

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

int	what_is_on_path(t_map *map, int x, int y)
{
	if (map->array[y][x] == 'C')
		add_new_collectible(map, x, y);
	else if (map->array[y][x] == 'E')
	{
		if (!map->exit.x)
		{
			map->exit.x = x;
			map->exit.y = y;
		}
		else
			return (-1);
	}
	else if (map->array[y][x] == 'P')
	{
		if (!map->player_start.x)
		{
			map->player_start.x = x;
			map->player_start.y = y;
		}
		else
			return (-1);
	}
	return (0);
}

int	finder(t_map *map)
{
	t_coords	coords;

	coords.x = 1;
	coords.y = 1;
	while (coords.y < map->height - 1 && coords.x < map->width - 1)
	{
		if (!what_is_on_path(map, coords.x, coords.y))
			coords.x++;
		else
			return (-1);
		if (coords.x == map->width - 1)
		{
			coords.x = 0;
			coords.y++;
		}
	}
	if (!map->collectibles || !map->exit.x || !map->player_start.x)
		return (-1);
	return (0);
}

int	check_map(t_map *map)
{
	if (check_if_rectangular(map))
		return (-1);
	if (check_border(map))
		return (-2);
	if (finder(map))
		return (-3);
	if (a_star(map))
		return (-4);
	return (0);
}
