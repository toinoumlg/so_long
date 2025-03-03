/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:30:34 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_a_star_list	*move_lowest_f_to_front(t_a_star_list **open_list)
{
	t_a_star_list	*lowest_prev;
	t_a_star_list	*current;
	t_a_star_list	*lowest;

	current = *open_list;
	lowest = *open_list;
	lowest_prev = NULL;
	while (current->next)
	{
		if (current->next->f < lowest->f)
		{
			lowest_prev = current;
			lowest = current->next;
		}
		current = current->next;
	}
	if (lowest == *open_list)
		return (*open_list);
	if (lowest_prev)
		lowest_prev->next = lowest->next;
	lowest->next = *open_list;
	*open_list = lowest;
	return (*open_list);
}

t_a_star_list	*add_to_list(t_a_star_list *open_list, float f, int y, int x)
{
	t_a_star_list	*tmp;
	t_a_star_list	*new_list;

	new_list = ft_calloc(sizeof(t_a_star_list), 1);
	if (!new_list)
		return (NULL);
	new_list->coords = set_vector2(y, x);
	new_list->f = f;
	new_list->next = NULL;
	if (!open_list)
		return (new_list);
	tmp = open_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_list;
	return (open_list);
}

t_a_star_list	*init_list(float f, int x, int y)
{
	t_a_star_list	*list;

	list = ft_calloc(sizeof(t_a_star_list), 1);
	if (!list)
		return (NULL);
	list->coords = set_vector2(y, x);
	list->f = f;
	list->next = NULL;
	return (list);
}

signed char	**init_closed_list(t_vector2 max)
{
	int			i;
	signed char	**closed_list;

	i = 0;
	closed_list = ft_calloc(sizeof(signed char *), max.y);
	if (!closed_list)
		return (NULL);
	while (i < max.y)
	{
		closed_list[i] = ft_calloc(sizeof(signed char), max.x);
		if (!closed_list[i])
			return (free_array((char **)closed_list), NULL);
		ft_memset(closed_list[i], -1, max.x);
		i++;
	}
	return (closed_list);
}
