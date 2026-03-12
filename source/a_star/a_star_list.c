/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:32:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"
#include <pthread.h>

void	swap(t_open_list *low, t_open_list **open_list)
{
	t_open_list	*prev[2];
	t_open_list	*next[2];
	t_open_list	*head;

	head = *open_list;
	prev[0] = low->prev;
	prev[1] = head->prev;
	next[0] = low->next;
	next[1] = head->next;
	low->prev = prev[1];
	low->next = next[1];
	head->prev = prev[0];
	head->next = next[0];
	if (prev[1])
		prev[1]->next = low;
	if (next[1])
		next[1]->prev = low;
	if (prev[0])
		prev[0]->next = head;
	if (next[0])
		next[0]->prev = head;
	if (head == *open_list)
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

void	swap_adjacent(t_open_list *low, t_open_list **open_list)
{
	t_open_list	*prev[2];
	t_open_list	*next[2];
	t_open_list	*head;

	head = *open_list;
	prev[0] = low->prev;
	prev[1] = head->prev;
	next[0] = low->next;
	next[1] = head->next;
	low->prev = prev[1];
	low->next = head;
	head->prev = low;
	head->next = next[0];
	if (prev[1])
		prev[1]->next = low;
	if (next[0])
		next[0]->prev = head;
	if (head == *open_list)
		*open_list = low;
}

void	swap_open_list(t_open_list *low, t_open_list **open_list)
{
	if (*open_list == low->prev)
		swap_adjacent(low, open_list);
	else
		swap(low, open_list);
}

void	swap_lowest_f(t_open_list **open_list)
{
	t_open_list	*current;
	t_open_list	*candidate;

	if (!open_list_is_sorted(*open_list))
		return ;
	current = *open_list;
	candidate = current->next;
	while (current)
	{
		if (current->values.f < candidate->values.f)
			candidate = current;
		current = current->next;
	}
	swap_open_list(candidate, open_list);
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

void	init_open_list(t_a_star *a_star)
{
	// to protect
	a_star->open_list = ft_calloc(sizeof(t_open_list), 1);
	if (!a_star->open_list)
		pthread_exit(a_star);
	a_star->open_list->values.coords = set_vector2(a_star->start.y,
			a_star->start.x);
	a_star->open_list->values.f = 0;
	a_star->open_list->next = NULL;
	a_star->open_list->prev = NULL;
}

void	print_closed_list(signed char **closed_list)
{
	int	i;

	i = 0;
	while (closed_list[i])
		printf("%s\n", closed_list[i++]);
}

void	init_closed_list(t_a_star *a_star)
{
	int			i;
	t_vector2	max;

	max = a_star->max;
	i = 0;
	a_star->closed_list = malloc(sizeof(signed char *) * (max.y + 2));
	if (!a_star->closed_list)
		pthread_exit(a_star);
	ft_memset(a_star->closed_list, 0, sizeof(signed char *) * (max.y + 2));
	while (i <= max.y)
	{
		a_star->closed_list[i] = malloc(sizeof(signed char) * (max.x + 2));
		if (!a_star->closed_list[i])
			pthread_exit(a_star);
		ft_memset(a_star->closed_list[i++], '0', sizeof(signed char) * (max.x
				+ 1));
	}
	// print_closed_list(a_star->closed_list);
}
