/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 11:11:57 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "error.h"
#include "so_long.h"

void	check_if_rectangular(t_map *map)
{
	int	i;

	i = 0;
	map->max.x = ft_strlen(map->array[i++]) - 1;
	while (map->array[i] && ft_strlen(map->array[i]) == (size_t)map->max.x + 1)
		i++;
	if (map->array[i])
		exit(parsing_error(map, MAP_NOT_RECTANGULAR));
	else
		map->max.y = i - 1;
}

void	check_border(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map->array[0][x])
		if (map->array[0][x++] != '1')
			exit(parsing_error(map, "top " WRONG_BORDERS));
	x = 0;
	while (map->array[map->max.y][x])
		if (map->array[map->max.y][x++] != '1')
			exit(parsing_error(map, "top " WRONG_BORDERS));
	while (map->array[y] && map->array[y][0])
		if (map->array[y++][0] != '1')
			exit(parsing_error(map, "left " WRONG_BORDERS));
	y = 0;
	while (map->array[y] && map->array[y][map->max.x])
		if (map->array[y++][map->max.x] != '1')
			exit(parsing_error(map, "right " WRONG_BORDERS));
}

int	what_is_on_path(t_map *map, int x, int y)
{
	if (map->array[y][x] == 'C')
		add_collectible(map, x, y);
	else if (map->array[y][x] == '2')
		add_ennemy(map, x, y);
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
	while (coords.y < map->max.y - 1 && coords.x < map->max.x - 1)
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

void	check_map(t_map *map)
{
	check_if_rectangular(map);
	check_border(map);
	finder(map);
	a_star(map);
}
