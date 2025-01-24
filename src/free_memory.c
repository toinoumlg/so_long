/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/24 01:34:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_cell_details(t_cell **cell_details, int map_height)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		free(cell_details[y]);
		y++;
	}
	free(cell_details);
}

void	free_closed_list(signed char **closed_list, int map_height)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		free(closed_list[y]);
		y++;
	}
	free(closed_list);
}

void	free_collectibles(t_collectibles *collectibles)
{
	t_collectibles	*tmp;

	while (collectibles)
	{
		tmp = collectibles->next_collectible;
		free(collectibles);
		collectibles = tmp;
	}
}

void	free_a_star_search(signed char **closed_list, t_cell **cell_details,
		t_a_star_list *open_list, int map_height)
{
	free_closed_list(closed_list, map_height);
	free_cell_details(cell_details, map_height);
	free(open_list);
}
void	free_memory(t_map *map)
{
	int	i;

	free_collectibles(map->collectibles);
	free(map->screen_res[0]);
	free(map->screen_res[1]);
	free(map->screen_res);
	i = 0;
	while (map->array[i])
	{
		free(map->array[i]);
		i++;
	}
	free(map->array);
	free(map);
}
