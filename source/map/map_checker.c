/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 22:02:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar.h"
#include "error_string.h"
#include "internal.h"
#include "mem.h"
#include "str.h"

void	check_if_rectangular(t_data *data)
{
	int		i;
	char	**array;

	array = data->map.array;
	i = 0;
	data->map.size.x = ft_strlen(array[i++]);
	while (array[i] && ft_strlen(array[i]) == (size_t)data->map.size.x)
		i++;
	if (array[i])
		exit(parsing_error(data, MAP_NOT_RECTANGULAR));
}

void	check_border(t_data *data)
{
	char		**array;
	t_vector2	*size;
	int			x;
	int			y;

	size = &data->map.size;
	array = data->map.array;
	y = 0;
	x = 0;
	while (x < size->x)
		if (array[0][x++] != '1')
			exit(parsing_error(data, "top " WRONG_BORDERS));
	x = 0;
	while (x < size->x)
		if (array[size->y - 1][x++] != '1')
			exit(parsing_error(data, "bottom " WRONG_BORDERS));
	while (y < size->y)
		if (array[y++][0] != '1')
			exit(parsing_error(data, "left " WRONG_BORDERS));
	y = 0;
	while (y < size->y)
		if (array[y++][size->x - 1] != '1')
			exit(parsing_error(data, "right " WRONG_BORDERS));
}

static int	is_in_char_set(char c)
{
	return (!(c == WALL && c == EMPTY && c == COLLECTIBLE && c == ENNEMY
			&& c == END && c == PLAYER));
}

void	add_exit(t_data *data, int x, int y)
{
	if (data->map.exit.x)
		exit(parsing_error(data, MULTIPLE_EXITS));
	data->map.exit = (t_vector2){x, y};
}

void	add_player(t_data *data, int x, int y)
{
	if (data->player.coords.x)
		exit(parsing_error(data, MULTIPLE_PLAYERS));
	ft_memset(&data->player, 0, sizeof(t_player));
	data->player.health = 3;
	data->player.coords = (t_float2){x, y};
}

void	check_char_at_coords(t_data *data, int x, int y)
{
	char	c;

	c = data->map.array[y][x];
	if (!is_in_char_set(c))
		exit(parsing_error(data, WRONG_CHARACTER));
	if (c == COLLECTIBLE)
		add_collectible(data, x, y);
	else if (c == ENNEMY)
		add_ennemy(data, x, y);
	else if (c == END)
		add_exit(data, x, y);
	else if (c == PLAYER)
		add_player(data, x, y);
}

void	check_char(t_data *data)
{
	t_vector2	coords;
	t_vector2	*size;

	size = &data->map.size;
	coords = (t_vector2){1, 1};
	while (coords.y < size->y)
	{
		check_char_at_coords(data, coords.x, coords.y);
		coords.x++;
		if (coords.x == size->x)
			coords = (t_vector2){1, coords.y + 1};
	}
	if (!data->collectibles || !data->ennemies || !data->player.coords.x
		|| !data->map.exit.x)
		exit(parsing_error(data, WRONG_CHARACTER));
}

void	check_map(t_data *data)
{
	check_if_rectangular(data);
	check_border(data);
	check_char(data);
	if (astar(data->map.array, (t_vector2){data->player.coords.x,
			data->player.coords.y}, &data->map.size))
		exit(parsing_error(data, NO_PATH_AVAILABLE));
}
