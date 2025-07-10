/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/10 12:50:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

void	swap(t_open_list *low, t_open_list *high, t_open_list **open_list)
{
	t_open_list	*prev[2];
	t_open_list	*next[2];

	prev[0] = low->prev;
	prev[1] = high->prev;
	next[0] = low->next;
	next[1] = high->next;
	low->prev = prev[1];
	low->next = next[1];
	high->prev = prev[0];
	high->next = next[0];
	if (prev[1])
		prev[1]->next = low;
	if (next[1])
		next[1]->prev = low;
	if (prev[0])
		prev[0]->next = high;
	if (next[0])
		next[0]->prev = high;
	if (high == *open_list)
		*open_list = low;
}

int	open_list_is_sorted(t_open_list *open_list)
{
	while (open_list && open_list->next)
	{
		if (open_list->values.h > open_list->next->values.h)
			return (1);
		open_list = open_list->next;
	}
	return (0);
}

void	swap_adjacent(t_open_list *low, t_open_list *high,
		t_open_list **open_list)
{
	t_open_list	*prev[2];
	t_open_list	*next[2];

	prev[0] = low->prev;
	prev[1] = high->prev;
	next[0] = low->next;
	next[1] = high->next;
	low->prev = prev[1];
	low->next = high;
	high->prev = low;
	high->next = next[0];
	if (prev[1])
		prev[1]->next = low;
	if (next[0])
		next[0]->prev = high;
	if (high == *open_list)
		*open_list = low;
}

void	swap_open_list(t_open_list *low, t_open_list *high,
		t_open_list **open_list)
{
	if (high->next == low)
		swap_adjacent(low, high, open_list);
	else
		swap(low, high, open_list);
}

void	sort_open_list(t_open_list **open_list)
{
	t_open_list	*current;
	t_open_list	*candidate;

	if (!open_list_is_sorted(*open_list))
		return ;
	current = *open_list;
	while (current)
	{
		candidate = current->next;
		while (candidate)
		{
			if (current->values.f > candidate->values.f)
				return (swap_open_list(candidate, current, open_list),
					sort_open_list(open_list));
			candidate = candidate->next;
		}
		current = current->next;
	}
}

t_open_list	*new_open_list(void)
{
	t_open_list	*new;

	// to protect
	new = malloc(sizeof(t_open_list));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_open_list));
	return (new);
}

void	append_new_open_list(t_open_list **open_list, t_open_list *new)
{
	t_open_list	*tmp;

	if (!*open_list)
	{
		*open_list = new;
		new->prev = NULL;
		new->next = NULL;
		return ;
	}
	tmp = *open_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

void	add_to_list(t_open_list **open_list, t_a_star_values values)
{
	t_open_list	*new;

	new = new_open_list();
	new->values = values;
	append_new_open_list(open_list, new);
}

void	init_list(t_a_star *a_star, float f, int x, int y)
{
	// to protect
	a_star->open_list = ft_calloc(sizeof(t_open_list), 1);
	if (!a_star->open_list)
		return ;
	a_star->open_list->values.coords = set_vector2(y, x);
	a_star->open_list->values.f = f;
	a_star->open_list->next = NULL;
	a_star->open_list->prev = NULL;
}

void	init_closed_list(t_a_star *a_star, t_data *data)
{
	int			i;
	t_vector2	max;

	max = data->map.max;
	i = 0;
	a_star->closed_list = malloc(sizeof(signed char *) * (max.y + 2));
	if (!a_star->closed_list)
		exit(pathfinding_error(a_star, data, ALLOC_ERROR));
	memset(a_star->closed_list, 0, max.y + 2);
	while (i <= max.y)
	{
		a_star->closed_list[i] = ft_calloc(sizeof(signed char), max.x + 2);
		if (!a_star->closed_list[i])
			exit(pathfinding_error(a_star, data, ALLOC_ERROR));
		ft_memset(a_star->closed_list[i++], '0', max.x + 1);
	}
}
