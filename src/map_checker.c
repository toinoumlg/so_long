/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 14:33:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// x ordinate y abscissa
int	check_border(t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	(void)i;
	while (map->array[y])
	{
		if (map->array[y][x] == '1')
			x++;
		else if (x == map->width)
		{
			x = 0;
			y += map->height - 1;
		}
		else
			return (-1);
	}
	return (0);
}

void	check_map(t_map *map)
{
	check_border(map);
}
