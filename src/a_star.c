/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/23 00:08:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

//  possible_moves = [
// (x+1, y), (x-1, y),    # Right, Left
// (x, y+1), (x, y-1),    # Up, Down
// (x+1, y+1), (x-1, y-1),  # Diagonal moves
// (x+1, y-1), (x-1, y+1)
// ]

int	is_end(int y, int x, t_coords end)
{
	if (y == end.y && x == end.x)
		return (1);
	else
		return (0);
}

// Returns true if the cell is not blocked else false
int	is_blocked(char **array, int y, int x)
{
	if (array[y][x] == '1')
		return (0);
	else
		return (1);
}

void	init_closed_list(int **closed_list, t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		closed_list[y] = ft_calloc(sizeof(int), map->width);
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		while (x < map->width)
		{
			closed_list[y][x] = -1;
			x++;
		}
		y++;
		x = 0;
	}
	return ;
}

int	a_star_search(t_coords start, t_coords end,
		t_possible_directions *possible_directions, t_map *map)
{
	t_cell			**cell_details;
	t_a_star_list	*open_list;
	int				**closed_list;
	int				i;
	int				j;
	t_a_star_list	*tmp;

	// t_a_star_list	*tmp;
	// int			found_dest;
	// found_dest = -1;
	(void)possible_directions;
	if (is_end(start.y, start.x, end))
		return (0);
	closed_list = ft_calloc(sizeof(int *), map->height);
	init_closed_list(closed_list, map);
	ft_printf("prout %d", closed_list[1][1]);
	i = 0;
	cell_details = ft_calloc(sizeof(t_cell *), map->height);
	open_list = ft_calloc(sizeof(t_a_star_list), 1);
	while (i < map->height)
	{
		cell_details[i] = ft_calloc(sizeof(t_cell), map->width);
		i++;
	}
	i = 0;
	j = 0;
	while (i < map->height)
	{
		
		while (j < map->width)
		{
			cell_details[i][j].f = __FLT_MAX__;
			cell_details[i][j].h = __FLT_MAX__;
			cell_details[i][j].g = __FLT_MAX__;
			cell_details[i][j].parent.x = -1;
			cell_details[i][j].parent.y = -1;
			j++;
		}
		i++;
		j = 0;
	}
	cell_details[start.y][start.x].f = 0;
	cell_details[start.y][start.x].h = 0;
	cell_details[start.y][start.x].g = 0;
	cell_details[start.y][start.x].parent.y = start.y;
	cell_details[start.y][start.x].parent.x = start.x;
	set_list(open_list, 0, start.x, start.y);
	while (open_list)
	{
		tmp = open_list;
		return (0);
	}
	ft_printf("crotte de cuk %d", open_list->coords.x);
	return (0);
	ft_printf("%d %d dada \n", i, j);
	i = 3;
	j = 3;
	// while (cell_details[i])
	// {
	// 	while (cell_details[i][j])
	// 	{
	// 		free(cell_details[i])
	// 	}
	// }
	// check_neighboorg(possible_directions);
	return (-1);
}

void	init_direction(t_coords *direction, float x, float y)
{
	direction->x = x;
	direction->y = y;
}

void	init_possible_directions(t_possible_directions *possible_directions)
{
	possible_directions->possible_directions = ft_calloc(sizeof(t_coords), 8);
	init_direction(&possible_directions->possible_directions[0], 1, 0);
	init_direction(&possible_directions->possible_directions[1], -1, 0);
	init_direction(&possible_directions->possible_directions[2], 0, 1);
	init_direction(&possible_directions->possible_directions[3], 0, -1);
	init_direction(&possible_directions->possible_directions[4], 1, 1);
	init_direction(&possible_directions->possible_directions[5], -1, 1);
	init_direction(&possible_directions->possible_directions[6], 1, -1);
	init_direction(&possible_directions->possible_directions[7], -1, 1);
	possible_directions->tmp_index = 0;
}

int	a_star(t_map *map)
{
	t_map					*tmp_map;
	t_coords				start;
	t_coords				end;
	t_possible_directions	possible_directions;
	t_collectibles			*collectibles;

	tmp_map = map;
	init_possible_directions(&possible_directions);
	collectibles = tmp_map->collectibles;
	start.x = tmp_map->player_start_x;
	start.y = tmp_map->player_start_y;
	while (collectibles)
	{
		end.x = collectibles->x;
		end.y = collectibles->y;
		if (a_star_search(start, end, &possible_directions, tmp_map))
			return (-1);
		start.x = collectibles->x;
		start.y = collectibles->y;
		collectibles = collectibles->next_collectible;
	}
	return (0);
}
