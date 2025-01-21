/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 15:17:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// x ordinate y abscissa
int	check_border(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->array[y])
	{
		while (map->array[y][x])
		{
			if (map->array[y][x] == '1')
				x++;
			else
				return (-1);
		}
		y += map->height - 1;
		x = 0;
	}
	return (0);
}

int	check_map(t_map *map)
{
	if (check_border(map))
		return (-1);
	return (0);
}
