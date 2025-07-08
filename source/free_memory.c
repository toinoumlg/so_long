/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 10:58:56 by amalangu         ###   ########.fr       */
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
		tmp = collectibles->next;
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
		tmp = ennemies->next;
		free(ennemies);
		ennemies = tmp;
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->array)
	{
		while (map->array[i])
			free(map->array[i++]);
		free(map->array);
	}
}
