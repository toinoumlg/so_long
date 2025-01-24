/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/24 01:34:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_end(int y, int x, t_coords end)
{
	if (y == end.y && x == end.x)
		return (1);
	else
		return (0);
}

int	is_blocked(char **array, int y, int x)
{
	if (array[y][x] == '1')
		return (0);
	else
		return (1);
}

signed char	**init_closed_list(t_map *map)
{
	int			y;
	int			x;
	signed char	**closed_list;

	y = 0;
	closed_list = ft_calloc(sizeof(signed char *), map->height);
	while (y < map->height)
	{
		closed_list[y] = ft_calloc(sizeof(signed char), map->width);
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			closed_list[y][x] = -1;
			x++;
		}
		y++;
	}
	return (closed_list);
}

void	set_to_next(t_a_star_list *open_list)
{
	t_a_star_list	*tmp;

	tmp = open_list;
	open_list = tmp->next;
	free(tmp);
}

int	a_star_search(t_coords start, t_coords end,
		t_possible_directions *possible_directions, t_map *map)
{
	t_cell			**cell_details;
	t_a_star_list	*open_list;
	signed char		**closed_list;
	t_a_star_list	*first;

	(void)possible_directions;
	if (is_end(start.y, start.x, end))
		return (0);
	closed_list = init_closed_list(map);
	cell_details = init_and_set_cell_details(start, map);
	open_list = set_list(0, start.x, start.y);
	while (open_list)
	{
		first = open_list;
		(void)first;
		free_a_star_search(closed_list, cell_details, open_list, map->height);
		return (0);
	}
	return (0);
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
	free(possible_directions.possible_directions);
	return (0);
}
