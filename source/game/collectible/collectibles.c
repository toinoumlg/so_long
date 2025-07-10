/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:33:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 13:11:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

t_collectible	*set_new_collectible(t_data *data)
{
	t_collectible	*new;

	new = malloc(sizeof(t_collectible));
	if (!new)
		exit(parsing_error(data, ALLOC_ERROR));
	ft_memset(new, 0, sizeof(t_collectible));
	return (new);
}

void	append_new_collectible(t_collectible **collectibles, t_collectible *new)
{
	t_collectible	*tmp;
	t_collectible	*head;

	tmp = *collectibles;
	if (!tmp)
	{
		*collectibles = new;
		return ;
	}
	head = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*collectibles = head;
}

void	add_collectible(t_data *data, int x, int y)
{
	t_collectible	*new;

	new = set_new_collectible(data);
	new->coords = set_vector2(y, x);
	new->i_image = rand() % 13;
	append_new_collectible(&data->collectibles, new);
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
