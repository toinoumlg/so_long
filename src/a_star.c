/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:02:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/24 19:46:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_destination(int y, int x, t_coords end)
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

float	calculate_new_h_value(int y, int x, t_coords end)
{
	return (sqrtf(powf((y - end.y), 2) + powf((x - end.x), 2)));
}

float	calculate_movement_cost(int y, int x)
{
	if (y == 0 || x == 0)
		return (1);
	else
		return (1.414);
}

t_a_star_list	*add_to_list(t_a_star_list *open_list, float f, int y, int x)
{
	t_a_star_list	*tmp;
	t_a_star_list	*new_list;

	// int				i;
	// i = 0;
	new_list = ft_calloc(sizeof(t_a_star_list), 1);
	new_list->coords.x = x;
	new_list->coords.y = y;
	new_list->f = f;
	new_list->next = NULL;
	if (!open_list)
	{
		open_list = new_list;
		// ft_printf("open_list [%d]\n", open_list->coords.x);
		return (open_list);
	}
	tmp = open_list;
	while (tmp->next)
	{
		tmp = tmp->next;
		// i++;
	}
	tmp->next = new_list;
	// ft_printf("[%d]\n", i);
	return (open_list);
}

void	trace_path(t_cell **cell_details, t_coords end)
{
	int			y;
	int			x;
	t_coords	*final_path;
	t_coords	tmp;
	int			i;

	i = 0;
	final_path = ft_calloc(sizeof(t_coords), 100);
	ft_printf("Path is : ");
	y = end.y;
	x = end.x;
	while (!(cell_details[y][x].parent.x == x
			&& cell_details[y][x].parent.y == y))
	{
		final_path[i].x = x;
		final_path[i].y = y;
		tmp.x = cell_details[y][x].parent.x;
		tmp.y = cell_details[y][x].parent.y;
		y = tmp.y;
		x = tmp.x;
		i++;
	}
	// ft_printf("%d", i);
	final_path[i].x = x;
	final_path[i].y = y;
	while (i > 0)
	{
		ft_printf("[%d][%d]-", final_path[i].y, final_path[i].x);
		i--;
	}
	ft_printf("[%d][%d]", final_path[i].y, final_path[i].x);
	ft_printf("\n");
}

t_a_star_list	*test(t_a_star_list *first, signed char **closed_list,
		t_coords end, t_possible_directions *possible_directions,
		t_cell **cell_details, t_map *map, t_a_star_list *open_list)
{
	t_coords	possible_direction;

	int x, y, i = 0, new_y, new_x;
	float g_new, h_new, f_new, movement_cost;
	x = first->coords.x;
	y = first->coords.y;
	closed_list[y][x] = 0;
	free(first);
	// ft_printf("y:[%d], x:[%d]\n", y, x);
	while (i < 4)
	{
		// ft_printf("i:[%d]\n", i);
		possible_direction = possible_directions->possible_directions[i];
		new_y = y + possible_direction.y;
		new_x = x + possible_direction.x;
		// ft_printf("new y:[%d], x:[%d]\n", new_y, new_x);
		if (is_destination(new_y, new_x, end))
		{
			cell_details[new_y][new_x].parent.x = x;
			cell_details[new_y][new_x].parent.y = y;
			return (open_list);
		}
		else if (closed_list[new_y][new_x] == -1 && is_blocked(map->array,
				new_y, new_x))
		{
			movement_cost = calculate_movement_cost(possible_direction.y,
					possible_direction.x);
			g_new = cell_details[new_y][new_x].g + movement_cost;
			h_new = calculate_new_h_value(new_y, new_x, end);
			f_new = g_new + h_new;
			if (cell_details[new_y][new_x].f == __FLT_MAX__
				|| cell_details[new_y][new_x].f > f_new)
			{
				open_list = add_to_list(open_list, f_new, new_y, new_x);
				cell_details[new_y][new_x] = set_cell_details(f_new, h_new,
						g_new, x, y);
			}
		}
		i++;
	}
	return (open_list);
}

int	a_star_search(t_coords start, t_coords end,
		t_possible_directions *possible_directions, t_map *map)
{
	t_cell			**cell_details;
	t_a_star_list	*open_list;
	signed char		**closed_list;
	t_a_star_list	*first;

	if (is_destination(start.y, start.x, end))
		return (0);
	closed_list = init_closed_list(map);
	cell_details = init_and_set_cell_details(start, map);
	open_list = init_list(0, start.x, start.y);
	while (open_list)
	{
		first = open_list;
		open_list = open_list->next;
		open_list = test(first, closed_list, end, possible_directions,
				cell_details, map, open_list);
		// free_a_star_search(closed_list, cell_details, open_list,
		// 	map->height);
		// ft_printf("open_list coord [%d]", open_list->coords.y);
	}
	trace_path(cell_details, end);
	return (0);
}

t_coords	init_direction(float y, float x)
{
	t_coords	direction;

	direction.x = x;
	direction.y = y;
	return (direction);
}

/*
			Generating all the 8 directions

				N.W   N   N.E
				\   |   /
				\  |  /
				W----Cell----E
					/ | \
				/   |  \
				S.W    S   S.E

			Cell-->Popped Cell (y, x)
			N -->  North       (y-1, x)
			S -->  South       (y+1, x)
			E -->  East        (y, x+1)
			W -->  West        (y, x-1)
			N.E--> North-East  (y-1, x+1)
			N.W--> North-West  (y-1, x-1)
			S.E--> South-East  (y+1, x+1)
			S.W--> South-West  (y+1, x-1)*/

t_coords	*init_possible_directions(void)
{
	t_coords	*possible_directions;

	possible_directions = ft_calloc(sizeof(t_coords), 4);
	possible_directions[0] = init_direction(0, -1);
	possible_directions[1] = init_direction(0, 1);
	possible_directions[2] = init_direction(1, 0);
	possible_directions[3] = init_direction(-1, 0);
	// possible_directions[4] = init_direction(1, -1);
	// possible_directions[5] = init_direction(-1, -1);
	// possible_directions[6] = init_direction(1, 1);
	// possible_directions[7] = init_direction(-1, 1);
	return (possible_directions);
}

int	a_star(t_map *map)
{
	t_coords				start;
	t_coords				end;
	t_possible_directions	possible_directions;
	t_collectibles			*collectibles;

	possible_directions.possible_directions = init_possible_directions();
	collectibles = map->collectibles;
	start.x = map->player_start_x;
	start.y = map->player_start_y;
	while (collectibles)
	{
		end.x = collectibles->x;
		end.y = collectibles->y;
		ft_printf("start y:[%d], x:[%d]\n", start.y, start.x);
		ft_printf("end y:[%d], x:[%d]\n", end.y, end.x);
		if (a_star_search(start, end, &possible_directions, map))
			return (-1);
		start.x = collectibles->x;
		start.y = collectibles->y;
		collectibles = collectibles->next_collectible;
	}
	end.x = map->exit_x;
	end.y = map->exit_y;
	ft_printf("start y:[%d], x:[%d]\n", start.y, start.x);
	ft_printf("end y:[%d], x:[%d]\n", end.y, end.x);
	if (a_star_search(start, end, &possible_directions, map))
		return (-1);
	free(possible_directions.possible_directions);
	return (0);
}
