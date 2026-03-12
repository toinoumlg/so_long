/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:10:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_vector2	set_vector2(int y, int x)
{
	t_vector2	vector2;

	vector2.x = x;
	vector2.y = y;
	return (vector2);
}

int	is_destination(t_vector2 actual, t_vector2 end)
{
	return (actual.y == end.y && actual.x == end.x);
}

int	is_blocked(char **array, t_vector2 actual)
{
	return (array[actual.y][actual.x] == '1');
}

float	calculate_new_h_value(int y, int x, t_vector2 end)
{
	return (fabsf((float)y - (float)end.y) + fabsf((float)x - (float)end.x));
}
