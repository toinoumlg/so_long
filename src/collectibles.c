/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:33:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 20:08:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	add_new_collectible(t_map *map, int x, int y)
{
	t_collectibles	*new_collectible;
	t_collectibles	*tmp;

	new_collectible = ft_calloc(sizeof(t_collectibles), 1);
	new_collectible->coords.x = x;
	new_collectible->coords.y = y;
	new_collectible->i_image = rand() % 13;
	new_collectible->next_collectible = NULL;
	if (!map->collectibles)
	{
		map->collectibles = new_collectible;
		return ;
	}
	tmp = map->collectibles;
	while (tmp->next_collectible)
		tmp = tmp->next_collectible;
	tmp->next_collectible = new_collectible;
	return ;
}

void	destroy_collectible(t_collectibles **collectibles, t_coords coords)
{
	t_collectibles	*previous;
	t_collectibles	*tmp;
	int				i;

	i = 0;
	tmp = *collectibles;
	if (tmp->coords.x == coords.x && tmp->coords.y == coords.y)
	{
		*collectibles = tmp->next_collectible;
		free(tmp);
		return ;
	}
	while (tmp != NULL && (tmp->coords.x != coords.x
			|| tmp->coords.y != coords.y))
	{
		i++;
		previous = tmp;
		tmp = tmp->next_collectible;
	}
	previous->next_collectible = tmp->next_collectible;
	free(tmp);
}

void	update_collectible_coords(t_collectibles *collectibles, t_coords min)
{
	t_collectibles *tmp;
	tmp = collectibles;
	while (tmp)
	{
		tmp->coords.x += min.x;
		tmp->coords.y += min.y;
		tmp = tmp->next_collectible;
	}
}