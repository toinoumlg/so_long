/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:25:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_collectibles(t_collectible *collectibles)
{
	t_collectible	*tmp;

	tmp = collectibles;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = collectibles->next_collectible;
		free(collectibles);
		collectibles = tmp;
	}
}

void	free_ennemies(t_ennemy *ennemies)
{
	t_ennemy	*tmp;

	tmp = ennemies;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = ennemies->next_ennemy;
		free(ennemies);
		ennemies = tmp;
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->array)
	{
		while (map->array[i])
			free(map->array[i++]);
	}
	if (map->array)
		free(map->array);
	free(map);
}
