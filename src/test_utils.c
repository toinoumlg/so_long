/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:19:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 23:37:20 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	test_print_final_path(t_cell **cell_details, t_coords end)
{
	t_coords	*final_path;
	t_coords	tmp;
	int			i;

	i = 0;
	final_path = ft_calloc(sizeof(t_coords), 100);
	ft_printf("Path is : ");
	while (!(cell_details[end.y][end.x].parent.x == end.x
			&& cell_details[end.y][end.x].parent.y == end.y))
	{
		final_path[i] = end;
		tmp = cell_details[end.y][end.x].parent;
		end = tmp;
		i++;
	}
	final_path[i] = end;
	while (i > 0)
	{
		ft_printf("[%d][%d]-", final_path[i].y, final_path[i].x);
		i--;
	}
	ft_printf("[%d][%d]\n", final_path[i].y, final_path[i].x);
	free(final_path);
}

int	trace_path(t_cell **cell_details, t_coords end, char found)
{
	if (!found)
		return (-1);
	else
		test_print_final_path(cell_details, end);
	return (0);
}

void	print_list(t_collectibles *list)
{
	while (list)
	{
		printf("[%d][%d]\n", list->coords.y, list->coords.x);
		list = list->next_collectible;
	}
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		ft_printf("%s\n", array[i++]);
}
