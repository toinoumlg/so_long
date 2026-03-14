/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:37:44 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 23:20:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "internal.h"
#include "mem.h"


void	append_new_ennemy(t_ennemy **ennemies, t_ennemy *new)
{
	t_ennemy	*tmp;
	t_ennemy	*head;

	tmp = *ennemies;
	if (!tmp)
	{
		*ennemies = new;
		return ;
	}
	head = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*ennemies = head;
}

void	add_ennemy(t_data *data, int x, int y)
{
	t_ennemy *new;

	new = ft_calloc(1, sizeof(t_ennemy));
	if (!new)
		exit(parsing_error(data, ALLOC_ERROR));
	new->coords = (t_vector2){x, y};
	append_new_ennemy(&data->ennemies, new);
}
