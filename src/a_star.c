/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 23:34:24 by amalangu         ###   ########.fr       */
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

int	a_star_search(char **array, t_coords start, t_coords end)
{
	ft_printf("Start [%d][%d]\n", (int)start.y, (int)start.x);
	ft_printf("End [%d][%d]\n", (int)end.y, (int)end.x);
	ft_printf("%c", array[0][0]);
	
	return (0);
}

void	a_star(t_map *map)
{
	t_map			*tmp_map;
	t_coords		start;
	t_coords		end;
	t_collectibles	*collectibles;
	char			**array;

	tmp_map = map;
	array = tmp_map->array;
	collectibles = tmp_map->collectibles;
	start.x = tmp_map->player_start_x;
	start.y = tmp_map->player_start_y;
	while (collectibles)
	{
		end.x = collectibles->x;
		end.y = collectibles->y;
		if (a_star_search(array, start, end))
			return ;
		start.x = collectibles->x;
		start.y = collectibles->y;
		collectibles = collectibles->next_collectible;
	}
}
