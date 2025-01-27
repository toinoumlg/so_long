/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/26 14:05:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

void	free_memory_map(t_map *map)
{
	int	i;

	if(map->collectibles)
		free_collectibles(map->collectibles);
	i = 0;
	while (map->array[i])
	{
		free(map->array[i]);
		i++;
	}
	if(map->array)
		free(map->array);
	free(map);
}
