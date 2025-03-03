/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:33:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:31:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	add_new_collectible(t_map *map, int x, int y)
{
	t_collectible	*new_collectible;
	t_collectible	*tmp;

	new_collectible = ft_calloc(sizeof(t_collectible), 1);
	if (!new_collectible)
		return (-1);
	new_collectible->coords = set_vector2(y, x);
	new_collectible->i_image = rand() % 13;
	new_collectible->is_printed = 0;
	new_collectible->next_collectible = NULL;
	if (!map->collectibles)
		return (map->collectibles = new_collectible, 0);
	tmp = map->collectibles;
	while (tmp->next_collectible)
		tmp = tmp->next_collectible;
	tmp->next_collectible = new_collectible;
	return (0);
}

void	destroy_collectible(t_collectible **collectibles, t_vector2 coords)
{
	t_collectible	*previous;
	t_collectible	*tmp;

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
		previous = tmp;
		tmp = tmp->next_collectible;
	}
	previous->next_collectible = tmp->next_collectible;
	free(tmp);
}

void	update_collectible_coords(t_collectible *collectibles, t_vector2 min)
{
	t_collectible	*tmp;

	tmp = collectibles;
	while (tmp)
	{
		tmp->coords.x += min.x;
		tmp->coords.y += min.y;
		tmp = tmp->next_collectible;
	}
}
