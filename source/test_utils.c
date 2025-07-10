/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:19:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/09 17:43:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_colors.h"
#include "so_long.h"

void	test_print_final_path(t_a_star_values **cell_details, t_vector2 end)
{
	t_vector2	*final_path;
	t_vector2	tmp;
	int			i;

	i = 0;
	final_path = ft_calloc(sizeof(t_vector2), 100);
	// ft_printf("Path is : ");
	while (!(cell_details[end.y][end.x].coords.x == end.x
			&& cell_details[end.y][end.x].coords.y == end.y))
	{
		final_path[i] = end;
		tmp = cell_details[end.y][end.x].coords;
		end = tmp;
		i++;
	}
	final_path[i] = end;
	while (i > 0)
	{
		// ft_printf("[%d][%d]-", final_path[i].y, final_path[i].x);
		i--;
	}
	// ft_printf("[%d][%d]\n", final_path[i].y, final_path[i].x);
	free(final_path);
}

void	print_list(t_collectible *list)
{
	while (list)
	{
		// printf("[%d][%d]\n", list->coords.y, list->coords.x);
		list = list->next;
	}
}

void	print_array(char **array, t_vector2 end)
{
	int	y;
	int	x;

	y = -1;
	while (array[++y])
	{
		x = -1;
		while (array[y][++x])
		{
			if (y == end.y && x == end.x)
				printf(BG_RED "  ");
			else
			{
				if (array[y][x] == '0')
					printf(BG_BLUE "  ");
				else if (array[y][x] == 'C')
					printf(BG_YELLOW "  ");
				else if (array[y][x] == '2')
					printf(BG_CYAN "  ");
				else if (array[y][x] == 'E')
					printf(BG_MAGENTA "  ");
				else if (array[y][x] == 'P')
					printf(BG_WHITE "  ");
				else if (array[y][x] == '1')
					printf(BG_BLACK "  ");
			}
			printf(RESET);
		}
		printf("\n");
	}
	printf("\n");
}

int	print_open_list(t_open_list *open_list, int y, int x)
{
	while (open_list)
	{
		if (open_list->values.coords.y == y && open_list->values.coords.x == x)
			return (1);
		open_list = open_list->next;
	}
	return (0);
}

void	print_a_star(t_a_star a_star, char **array)
{
	int			y;
	int			x;
	signed char	**closed_list;
	t_vector2	start;
	t_vector2	end;
	t_open_list	*open_list;

	closed_list = a_star.closed_list;
	start = a_star.start;
	end = a_star.end;
	open_list = a_star.open_list;
	y = -1;
	while (closed_list[++y])
	{
		x = -1;
		while (closed_list[y][++x])
		{
			if (open_list->values.coords.y == y
				&& open_list->values.coords.x == x)
				printf(BG_WHITE "  ");
			else if (print_open_list(open_list, y, x))
				printf(BG_GREEN "  ");
			else if (start.y == y && start.x == x)
				printf(BG_YELLOW "  ");
			else if (end.y == y && end.x == x)
				printf(BG_MAGENTA "  ");
			else if (closed_list[y][x] == '0' && (array[y][x] == '0'
					|| array[y][x] == 'C' || array[y][x] == '2'
					|| array[y][x] == 'E' || array[y][x] == 'P'))
				printf(BG_BLUE "  ");
			else if (closed_list[y][x] == '1' && (array[y][x] == '0'
					|| array[y][x] == 'C' || array[y][x] == '2'
					|| array[y][x] == 'E' || array[y][x] == 'P'))
				printf(BG_RED "  ");
			else if (array[y][x] == '1')
				printf(BG_BLACK "  ");
			printf(RESET);
		}
		printf("\n");
	}
	printf("\n");
	printf("%f %f %f \n", open_list->values.f, open_list->values.h,
		open_list->values.g);
	x = 0;
	while (open_list)
	{
		x++;
		open_list = open_list->next;
	}
	printf("%d\n", x);
}
