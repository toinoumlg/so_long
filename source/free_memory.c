/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 14:03:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <stdlib.h>

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

void	free_rooms(t_room *rooms)
{
	t_room	*next;

	while (rooms)
	{
		next = rooms->next;
		if (rooms->v_hall)
			free_hall(rooms->v_hall);
		if (rooms->h_hall)
			free_hall(rooms->h_hall);
		free(rooms);
		rooms = next;
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
		free(map->array);
	}
	if (map->rooms)
		free_rooms(map->rooms);
}
