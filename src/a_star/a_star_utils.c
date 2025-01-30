/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 23:33:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_destination(t_coords actual, t_coords end)
{
	if (actual.y == end.y && actual.x == end.x)
		return (1);
	else
		return (0);
}

int	is_blocked(char **array, t_coords actual)
{
	if (array[actual.y][actual.x] == '1')
		return (0);
	else
		return (1);
}

float	calculate_new_h_value(int y, int x, t_coords end)
{
	return (sqrtf(powf((y - end.y), 2) + powf((x - end.x), 2)));
}

t_possible_directions	set_move(void)
{
	t_possible_directions move;

	move.up.y = -1;
	move.up.x = 0;
	move.down.y = 1;
	move.down.x = 0;
	move.right.y = 0;
	move.right.x = 1;
	move.left.y = 0;
	move.left.x = -1;
	move.zero.y = 0;
	move.zero.x = 0;
	return (move);
}