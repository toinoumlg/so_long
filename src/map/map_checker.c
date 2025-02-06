/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/06 21:09:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_if_rectangular(t_map *map)
{
	char	*tmp;
	char	*cr;
	int		i;

	i = 0;
	while (i < map->actual.y)
	{
		cr = ft_strchr(map->array[i], '\n');
		if (cr)
		{
			map->array[i] = ft_strtrim((tmp = map->array[i]), cr);
			free(tmp);
		}
		if (((int)ft_strlen(map->array[i])) != map->actual.x)
			return (-1);
		i++;
	}
	return (0);
}

int	check_border(t_map *map)
{
	t_vector2	coords;

	coords = set_vector2(0, 0);
	while (map->array[coords.y])
	{
		if (map->array[coords.y][coords.x] != '1')
			return (-1);
		if (coords.x == map->actual.x - 1)
			coords = set_vector2(coords.y + 1, 0);
		else if (coords.y == 0 || coords.y == map->actual.y - 1)
			coords.x++;
		else
			coords.x += map->actual.x - 1;
	}
	return (0);
}

int	what_is_on_path(t_map *map, int x, int y)
{
	if (map->array[y][x] == 'C')
		add_new_collectible(map, x, y);
	else if (map->array[y][x] == '2')
		add_new_ennemy(map, x, y);
	else if (map->array[y][x] == 'E')
	{
		if (!map->exit.x)
			map->exit = set_vector2(y, x);
		else
			return (-1);
	}
	else if (map->array[y][x] == 'P')
	{
		if (!map->player_start.x)
			map->player_start = set_vector2(y, x);
		else
			return (-1);
	}
	if (map->array[y][x] == 'C' || map->array[y][x] == '1'
		|| map->array[y][x] == '0' || map->array[y][x] == 'E'
		|| map->array[y][x] == 'P' || map->array[y][x] == '2')
		return (0);
	else
		return (-1);
}

int	finder(t_map *map)
{
	t_vector2	coords;

	coords = set_vector2(1, 1);
	while (coords.y < map->actual.y - 1 && coords.x < map->actual.x - 1)
	{
		if (!what_is_on_path(map, coords.x, coords.y))
			coords.x++;
		else
			return (-1);
		if (coords.x == map->actual.x - 1)
			coords = set_vector2(coords.y + 1, 1);
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
