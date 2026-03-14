/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:39:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:43:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar_globals.h"
#include "astar_struct.h"

void	free_cells(t_cell_astar **cells)
{
	int	y;

	y = 0;
	if (!cells)
		return ;
	while (cells[y])
		free(cells[y++]);
	free(cells);
}

void	free_closed(t_closed **closed)
{
	int	y;

	y = 0;
	if (!closed)
		return ;
	while (closed[y])
		free(closed[y++]);
	free(closed);
}

void	free_open(t_open *open)
{
	t_open	*next;

	while (open)
	{
		next = open->next;
		free(open);
		open = next;
	}
}

void	free_routine(t_astar *a_star, t_thread_data *data)
{
	free_open(a_star->open);
	free_closed(a_star->closed);
	free_cells(a_star->cells);
	free(data);
}

void	*exit_thread(t_astar *a_star, t_thread_data *data)
{
	free_routine(a_star, data);
	pthread_exit(NULL);
}