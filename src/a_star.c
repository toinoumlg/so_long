/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/22 10:59:08 by amalangu         ###   ########.fr       */
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

int	a_star_search(t_coords start, t_coords end,
		t_possible_directions *possible_directions, t_map *map)
{
	ft_printf("Start [%d][%d]\n", (int)start.y, (int)start.x);
	ft_printf("End [%d][%d]\n", (int)end.y, (int)end.x);
	ft_printf("caca %d %d", (int)possible_directions->possible_directions[7].x,
		(int)possible_directions->possible_directions[7].y);
	if(is_end(start.y,start.x, end))
		return 0;
	t_cell **results;
	*results = ft_calloc(sizeof(t_cell*), map->height);
	
	results = ft_calloc(sizeof(t_cell*), map->height);
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

void	a_star(t_map *map)
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
			return ;
		start.x = collectibles->x;
		start.y = collectibles->y;
		collectibles = collectibles->next_collectible;
	}
}
