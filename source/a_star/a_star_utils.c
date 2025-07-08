/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/31 14:22:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_vector2	set_vector2(int y, int x)
{
	t_vector2	vector2;

	vector2.y = y;
	vector2.x = x;
	return (vector2);
}

int	is_destination(t_vector2 actual, t_vector2 end)
{
	if (actual.y == end.y && actual.x == end.x)
		return (1);
	else
		return (0);
}

int	is_blocked(char **array, t_vector2 actual)
{
	if (array[actual.y][actual.x] == '1')
		return (0);
	else
		return (1);
}

float	calculate_new_h_value(int y, int x, t_vector2 end)
{
	return (sqrtf(powf((y - end.y), 2) + powf((x - end.x), 2)));
}

t_possible_directions	set_move(void)
{
	t_possible_directions	move;

	move.up = set_vector2(-1, 0);
	move.down = set_vector2(1, 0);
	move.right = set_vector2(0, 1);
	move.left = set_vector2(0, -1);
	move.zero = set_vector2(0, 0);
	return (move);
}
