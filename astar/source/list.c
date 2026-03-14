/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:39:42 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:42:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar_struct.h"
#include "astar_globals.h"
#include "astar_internal.h"
#include "mem.h"
#include <pthread.h>
#include <stdio.h>

void	swap(t_open *low, t_open **open)
{
	t_open	*prev[2];
	t_open	*next[2];
	t_open	*head;

	head = *open;
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
	if (head == *open)
		*open = low;
}

bool	is_list_is_sorted(t_open *open)
{
	while (open && open->next)
	{
		if (open->cell.f > open->next->cell.f)
			return (false);
		open = open->next;
	}
	return (true);
}

void	swap_adjacent(t_open *low, t_open **open)
{
	t_open	*prev[2];
	t_open	*next[2];
	t_open	*head;

	head = *open;
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
	if (head == *open)
		*open = low;
}

void	swap_open(t_open *low, t_open **open)
{
	if (*open == low->prev)
		swap_adjacent(low, open);
	else
		swap(low, open);
}

void	swap_lowest_f(t_open **open)
{
	t_open	*current;
	t_open	*candidate;

	if (is_list_is_sorted(*open))
		return ;
	current = *open;
	candidate = current->next;
	while (current)
	{
		if (current->cell.f < candidate->cell.f)
			candidate = current;
		current = current->next;
	}
	swap_open(candidate, open);
}

void	append_new_cell(t_open **open, t_open *new)
{
	t_open	*tmp;

	if (!*open)
	{
		*open = new;
		new->prev = NULL;
		new->next = NULL;
		return ;
	}
	tmp = *open;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

void	add_to_open(t_open **open, t_cell_astar *cell)
{
	t_open	*new;

	new = ft_calloc(1, sizeof(t_open));
	new->cell = *cell;
	append_new_cell(open, new);
}

void	init_open(t_astar *a_star, t_thread_data *data)
{
	a_star->open = ft_calloc(1, sizeof(t_open));
	if (!a_star->open)
		exit_thread(a_star, data);
	a_star->open->cell.coords = (t_vector2){data->start.x, data->start.y};
	a_star->open->cell.f = 0;
}

void	init_closed(t_astar *a_star, t_thread_data *data)
{
	int	y;

	y = 0;
	a_star->closed = ft_calloc(data->map_size->y + 1, sizeof(t_closed *));
	if (!a_star->closed)
		exit_thread(a_star, data);
	while (y < data->map_size->y)
	{
		a_star->closed[y] = ft_calloc(data->map_size->x, sizeof(t_closed));
		if (!a_star->closed[y++])
			exit_thread(a_star, data);
	}
}
