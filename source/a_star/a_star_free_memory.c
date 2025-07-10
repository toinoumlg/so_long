/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_free_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:22:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/09 15:38:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// void	free_cell_details(t_cell **cell_details, int height)
// {
// 	int	y;

// 	y = 0;
// 	if (cell_details)
// 	{
// 		while (cell_details[y] && y <= height)
// 			free(cell_details[y++]);
// 		free(cell_details);
// 		cell_details = NULL;
// 	}
// }

// void	free_closed_list(signed char **closed_list, int height)
// {
// 	int	y;

// 	y = 0;
// 	if (closed_list)
// 	{
// 		while (closed_list[y] && y <= height)
// 			free(closed_list[y++]);
// 		free(closed_list);
// 	}
// 	closed_list = NULL;
// }

// void	free_open_list(t_open_list *open_list)
// {
// 	t_open_list	*next;

// 	while (open_list)
// 	{
// 		next = open_list->next;
// 		free(open_list);
// 		open_list = next;
// 	}
// }

// void	free_a_star_search(t_a_star *a_star, int height)
// {
// 	if (a_star->open_list)
// 		free_open_list(a_star->open_list);
// 	if (a_star->closed_list)
// 		free_closed_list(a_star->closed_list, height);
// 	if (a_star->cell_details)
// 		free_cell_details(a_star->cell_details, height);
// }

void	free_cell_details(t_a_star_values **cell_details, int map_height)
{
	int	y;

	y = 0;
	if (cell_details)
	{
		while (y < map_height)
			free(cell_details[y++]);
		free(cell_details);
	}
}

void	free_closed_list(signed char **closed_list, int map_height)
{
	int	y;

	y = 0;
	if (closed_list)
	{
		while (y <= map_height)
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

void	free_a_star_search(t_a_star *a_star, int map_height)
{
	free_open_list(a_star->open_list);
	free_closed_list(a_star->closed_list, map_height);
	free_cell_details(a_star->cell_details, map_height);
}