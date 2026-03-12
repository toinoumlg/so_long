/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:32:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

void	check_if_rectangular(t_data *data)
{
	int		i;
	char	**array;

	array = data->map.array;
	i = 0;
	data->map.max.x = ft_strlen(array[i++]);
	while (array[i] && ft_strlen(array[i]) == (size_t)data->map.max.x)
		i++;
	if (array[i])
		exit(parsing_error(data, MAP_NOT_RECTANGULAR));
}

void	check_border(t_data *data)
{
	char	**array;
	int		x;
	int		y;

	array = data->map.array;
	y = 0;
	x = 0;
	while (array[0][x])
		if (array[0][x++] != '1')
			exit(parsing_error(data, "top " WRONG_BORDERS));
	x = 0;
	while (array[data->map.max.y][x])
		if (array[data->map.max.y][x++] != '1')
			exit(parsing_error(data, "bottom " WRONG_BORDERS));
	while (array[y] && array[y][0])
		if (array[y++][0] != '1')
			exit(parsing_error(data, "left " WRONG_BORDERS));
	y = 0;
	while (array[y] && array[y][data->map.max.x])
		if (array[y++][data->map.max.x] != '1')
			exit(parsing_error(data, "right " WRONG_BORDERS));
}

static int	is_in_char_set(char c)
{
	return (!(c == '1' && c == '0' && c == 'C' && c == '2' && c == 'E'
			&& c == 'P'));
}

void	add_exit(t_data *data, int x, int y)
{
	if (data->map.exit.x)
		exit(parsing_error(data, MULTIPLE_EXITS));
	data->map.exit = set_vector2(y, x);
}

void	add_player(t_data *data, int x, int y)
{
	if (data->player.coords.x)
		exit(parsing_error(data, MULTIPLE_PLAYERS));
	ft_memset(&data->player, 0, sizeof(t_player));
	data->player.health = 3;
	data->player.coords = set_vector2(y, x);
}

void	check_char_at_coords(t_data *data, int x, int y)
{
	char	c;

	c = data->map.array[y][x];
	if (!is_in_char_set(c))
		exit(parsing_error(data, WRONG_CHARACTER));
	if (c == 'C')
		add_collectible(data, x, y);
	else if (c == '2')
		add_ennemy(data, x, y);
	else if (c == 'E')
		add_exit(data, x, y);
	else if (c == 'P')
		add_player(data, x, y);
}

void	check_char(t_data *data)
{
	t_vector2	coords;
	t_vector2	*max;

	max = &data->map.max;
	coords = set_vector2(1, 1);
	while (coords.y < max->y)
	{
		check_char_at_coords(data, coords.x, coords.y);
		coords.x++;
		if (coords.x == max->x)
			coords = set_vector2(coords.y + 1, 1);
	}
}

void	check_map(t_data *data)
{
	check_if_rectangular(data);
	check_border(data);
	check_char(data);
	check_valid_paths(data);
}
