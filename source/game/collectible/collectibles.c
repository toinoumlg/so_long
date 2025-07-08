/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:33:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 11:15:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

t_collectible	*set_new_collectible(t_map *map)
{
	t_collectible	*new;

	new = ft_calloc(sizeof(t_collectible), 1);
	if (!new)
		exit(parsing_error(map, ALLOC_ERROR));
	memset(new, 0, sizeof(t_collectible));
	return (new);
}

void	add_collectible(t_map *map, int x, int y)
{
	t_collectible	*new;
	t_collectible	*tmp;

	new = set_new_collectible(map);
	new->coords = set_vector2(y, x);
	new->i_image = rand() % 13;
	if (!map->collectibles)
		return (map->collectibles = new, 0);
	tmp = map->collectibles;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	destroy_collectible(t_collectible **collectibles, t_vector2 coords)
{
	t_collectible	*previous;
	t_collectible	*tmp;

	tmp = *collectibles;
	if (tmp->coords.x == coords.x && tmp->coords.y == coords.y)
	{
		*collectibles = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp != NULL && (tmp->coords.x != coords.x
			|| tmp->coords.y != coords.y))
	{
		previous = tmp;
		tmp = tmp->next;
	}
	previous->next = tmp->next;
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
		tmp = tmp->next;
	}
}
