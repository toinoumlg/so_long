/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:30:23 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 21:39:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "error_string.h"
#include "internal.h"
#include "mem.h"

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
	t_collectible *new;

	new = ft_calloc(1, sizeof(t_collectible));
	new->coords = (t_vector2){x, y};
	new->i_image = rand() % 13;
	append_new_collectible(&data->collectibles, new);
}