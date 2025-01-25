/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/24 23:24:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_destination(int y, int x, t_coords end)
{
	if (y == end.y && x == end.x)
		return (1);
	else
		return (0);
}

int	is_blocked(char **array, int y, int x)
{
	if (array[y][x] == '1')
		return (0);
	else
		return (1);
}

float	calculate_new_h_value(int y, int x, t_coords end)
{
	return (sqrtf(powf((y - end.y), 2) + powf((x - end.x), 2)));
}

/*
			Generating all the 4 directions

						N
						|
						|
				W-----Cell-----E
						|
						|
						S

			Cell-->Popped Cell (y, x)
			N -->  North       (y-1, x)
			S -->  South       (y+1, x)
			E -->  East        (y, x+1)
			W -->  West        (y, x-1)*/

t_coords	init_direction(int y, int x)
{
	t_coords	direction;

	direction.x = x;
	direction.y = y;
	return (direction);
}

t_coords	*init_possible_directions(void)
{
	t_coords	*possible_directions;

	possible_directions = ft_calloc(sizeof(t_coords), 4);
	possible_directions[0] = init_direction(0, -1);
	possible_directions[1] = init_direction(0, 1);
	possible_directions[2] = init_direction(1, 0);
	possible_directions[3] = init_direction(-1, 0);
	return (possible_directions);
}
