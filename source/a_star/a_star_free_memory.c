/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_free_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:22:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/04 20:32:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_cell_details(t_cell **cell_details, int map_height)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		free(cell_details[y]);
		y++;
	}
	free(cell_details);
}

void	free_closed_list(signed char **closed_list, int map_height)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		free(closed_list[y]);
		y++;
	}
	free(closed_list);
}

void	free_open_list(t_a_star_list *open_list)
{
	t_a_star_list	*tmp;

	while (open_list)
	{
		tmp = open_list->next;
		free(open_list);
		open_list = tmp;
	}
}

void	free_a_star_search(t_a_star_struct a_star, int map_height)
{
	free_open_list(a_star.open_list);
	free_closed_list(a_star.closed_list, map_height);
	free_cell_details(a_star.cell_details, map_height);
}
