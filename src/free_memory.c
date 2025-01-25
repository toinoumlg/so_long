/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 11:23:49 by amalangu         ###   ########.fr       */
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

void	free_memory(t_map *map)
{
	int	i;

	free_collectibles(map->collectibles);
	i = 0;
	while (map->array[i])
	{
		free(map->array[i]);
		i++;
	}
	free(map->array);
	free(map);
}
