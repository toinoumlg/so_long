/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_free_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:22:21 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:13:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_cell_details(t_a_star_values **cell_details)
{
	int	y;

	y = 0;
	if (cell_details)
	{
		while (cell_details[y])
			free(cell_details[y++]);
		free(cell_details);
	}
}

void	free_closed_list(signed char **closed_list)
{
	int	y;

	y = 0;
	if (closed_list)
	{
		while (closed_list[y])
			free(closed_list[y++]);
		free(closed_list);
	}
}

void	free_open_list(t_open_list *open_list)
{
	t_open_list	*tmp;

	while (open_list)
	{
		tmp = open_list->next;
		free(open_list);
		open_list = tmp;
	}
}

void	free_a_star_routine(t_a_star *a_star)
{
	t_a_star	*next;

	while (a_star)
	{
		next = a_star->next;
		free_open_list(a_star->open_list);
		free_closed_list(a_star->closed_list);
		free_cell_details(a_star->cell_details);
		free(a_star);
		a_star = next;
	}
}
