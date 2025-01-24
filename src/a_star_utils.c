/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/24 01:09:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_a_star_list	*set_list(float f, int x, int y)
{
	t_a_star_list	*list;

	list = ft_calloc(sizeof(t_a_star_list), 1);
	list->coords.x = x;
	list->coords.x = y;
	list->f = f;
	list->next = NULL;
	return (list);
}


t_cell	set_cell_details(float f, float h, float g, int x, int y)
{
	t_cell	cell_details;

	cell_details.f = f;
	cell_details.h = h;
	cell_details.g = g;
	cell_details.parent.x = x;
	cell_details.parent.y = y;
	return (cell_details);
}

t_cell	**init_and_set_cell_details(t_coords start, t_map *map)
{
	int y = 0;
	int x = 0;
	t_cell **cell_details;

	cell_details = ft_calloc(sizeof(t_cell *), map->height);
	while (y < map->height)
	{
		cell_details[y] = ft_calloc(sizeof(t_cell), map->width);
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			cell_details[y][x] = set_cell_details(__FLT_MAX__, __FLT_MAX__,
					__FLT_MAX__, -1, -1);
			x++;
		}
		y++;
	}
	cell_details[start.y][start.x] = set_cell_details(0, 0, 0, start.x,
			start.y);
	return (cell_details);
}