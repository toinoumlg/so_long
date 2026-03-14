/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:27:16 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 20:27:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_struct.h"
#include "mem.h"
#include "put.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char	**allocate_map(t_vector2 *size)
{
	int		y;
	char	**map;

	y = 0;
	map = ft_calloc(size->y + 1, sizeof(char *));
	while (y < size->y)
	{
		map[y] = ft_calloc(size->x + 1, sizeof(char));
		ft_memset(map[y++], '1', size->x);
	}
	return (map);
}

int	snap_to_grid(float x)
{
	return (round(x / GRID_SIZE) * GRID_SIZE);
}

int	range(int min, int max)
{
	return (rand() % (max + 1 - min) + min);
}

float	frange(float min, float max)
{
	return (min + (float)rand() / RAND_MAX * (max - min));
}

void	save_to_file(char **array)
{
	int	fd;

	fd = open("bsp.ber", O_WRONLY | O_CREAT | O_TRUNC, 00700);
	for (int y = 0; array[y]; y++)
	{
		ft_putstr_fd(array[y], fd);
		ft_putstr_fd("\n", fd);
	}
	close(fd);
}

t_cell	*new_cell(t_vector2 min, t_vector2 max)
{
	t_cell	*cell;

	cell = ft_calloc(1, sizeof(t_cell));
	cell->min = min;
	cell->max = max;
	cell->width = max.x - min.x;
	cell->height = max.y - min.y;
	return (cell);
}

bool	try_divide(int min_size, t_cell *branch)
{
	int	mid;

	if (branch->width < min_size && branch->height < min_size)
		return (false);
	if (branch->left)
	{
		if (range(0, 100) < 50)
			return (try_divide(min_size, branch->left));
		else
			return (try_divide(min_size, branch->right));
	}
	if (branch->width > branch->height)
	{
		mid = branch->min.x + frange(0.4, 0.8) * branch->width;
		branch->left = new_cell((t_vector2){branch->min.x, branch->min.y},
				(t_vector2){mid, branch->max.y});
		branch->right = new_cell((t_vector2){mid, branch->min.y},
				(t_vector2){branch->max.x, branch->max.y});
		return (true);
	}
	else
	{
		mid = branch->min.y + frange(0.4, 0.8) * branch->height;
		branch->left = new_cell((t_vector2){branch->min.x, branch->min.y},
				(t_vector2){branch->max.x, mid});
		branch->right = new_cell((t_vector2){branch->min.x, mid},
				(t_vector2){branch->max.x, branch->max.y});
		return (true);
	}
}

void	divide_map(t_bsp_map *map)
{
	int	rooms;

	rooms = 1;
	while (rooms < map->nbr_room)
	{
		if (try_divide(map->min_cell, &map->root))
			rooms++;
	}
}

void	update_cell(t_cell *value, char **array)
{
	int	y;
	int	x;

	y = value->min.y;
	while (y < value->max.y)
	{
		x = value->min.x;
		while (x < value->max.x)
			array[y][x++] = '0';
		y++;
	}
}

void	snap_cell(t_cell *value)
{
	value->min.x = snap_to_grid(value->min.x);
	value->min.y = snap_to_grid(value->min.y);
	value->max.x = snap_to_grid(value->max.x);
	value->max.y = snap_to_grid(value->max.y);
}

void	update_array(t_leaf *leafs, char **array)
{
	t_hall	*tmp;

	while (leafs)
	{
		tmp = leafs->h_hall;
		while (tmp)
		{
			snap_cell(tmp->value);
			update_cell(tmp->value, array);
			tmp = tmp->next;
		}
		tmp = leafs->v_hall;
		while (tmp)
		{
			snap_cell(tmp->value);
			update_cell(tmp->value, array);
			tmp = tmp->next;
		}
		snap_cell(leafs->value);
		update_cell(leafs->value, array);
		leafs = leafs->next;
	}
}

void	add_to_leafs(t_cell *value, t_leaf **leafs)
{
	t_leaf	*new_leaf;
	t_leaf	*tmp;

	new_leaf = ft_calloc(1, sizeof(t_leaf));
	new_leaf->value = value;
	if (!*leafs)
	{
		*leafs = new_leaf;
		return ;
	}
	tmp = *leafs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_leaf;
}

void	get_leaf(t_cell *branch, t_leaf **leafs)
{
	if (!branch->left)
		add_to_leafs(branch, leafs);
	else
	{
		get_leaf(branch->left, leafs);
		get_leaf(branch->right, leafs);
	}
}

void	add_to_neighbor(t_cell *value, t_neighbor **neighbor)
{
	t_neighbor	*new_neighbor;
	t_neighbor	*tmp;

	new_neighbor = ft_calloc(1, sizeof(t_neighbor));
	new_neighbor->value = value;
	if (!*neighbor)
	{
		*neighbor = new_neighbor;
		return ;
	}
	tmp = *neighbor;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_neighbor;
}

void	find_neighbors(t_cell *root, t_leaf **leafs)
{
	t_leaf	*tmp;
	t_leaf	*next;

	get_leaf(root, leafs);
	tmp = *leafs;
	while (tmp)
	{
		next = tmp->next;
		while (next)
		{
			if (tmp != next)
			{
				if (tmp->value->max.x == next->value->min.x)
				{
					if (fmaxl(tmp->value->min.y,
							next->value->min.y) < fminl(tmp->value->max.y,
							next->value->max.y))
						add_to_neighbor(next->value, &tmp->h_nei);
				}
				if (tmp->value->max.y == next->value->min.y)
				{
					if (fmaxl(tmp->value->min.x,
							next->value->min.x) < fminl(tmp->value->max.x,
							next->value->max.x))
						add_to_neighbor(next->value, &tmp->v_nei);
				}
			}
			next = next->next;
		}
		tmp = tmp->next;
	}
}

void	shrink(t_leaf *leafs, int min_cell)
{
	float	new_width;
	float	new_height;
	t_cell	*value;
	float	shrink_value;

	while (leafs)
	{
		value = leafs->value;
		shrink_value = frange(0.25, 0.9);
		new_width = fmaxf(value->width * shrink_value, min_cell);
		shrink_value = frange(0.25, 0.9);
		new_height = fmaxf(value->height * shrink_value, min_cell);
		value->min = (t_vector2){value->min.x + 0.5 * (value->width
				- new_width), value->min.y + 0.5 * (value->height
				- new_height)};
		value->max = (t_vector2){value->max.x - 0.5 * (value->width
				- new_width), value->max.y - 0.5 * (value->height
				- new_height)};
		value->height = new_height;
		value->width = new_width;
		leafs = leafs->next;
	}
}

void	add_hall(t_vector2 min, t_vector2 max, t_hall **halls)
{
	t_hall	*new_hall;
	t_hall	*tmp;

	new_hall = ft_calloc(1, sizeof(t_hall));
	new_hall->value = new_cell(min, max);
	if (!*halls)
	{
		*halls = new_hall;
		return ;
	}
	tmp = *halls;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_hall;
}

void	generate_halls(t_leaf *leafs)
{
	t_neighbor	*tmp;
	t_cell		*value;
	float		y;
	float		x;

	while (leafs)
	{
		tmp = leafs->h_nei;
		value = leafs->value;
		while (tmp)
		{
			if ((fminf(value->max.y, tmp->value->max.y) - fmaxf(value->min.y,
						tmp->value->min.y)) > GRID_SIZE)
			{
				y = frange(fmaxf(value->min.y, tmp->value->min.y),
						fminf(value->max.y, tmp->value->max.y) - GRID_SIZE);
				add_hall((t_vector2){value->max.x, y},
					(t_vector2){tmp->value->min.x, y + GRID_SIZE},
					&leafs->h_hall);
			}
			tmp = tmp->next;
		}
		tmp = leafs->v_nei;
		while (tmp)
		{
			if ((fminf(value->max.x, tmp->value->max.x) - fmaxf(value->min.x,
						tmp->value->min.x)) > GRID_SIZE)
			{
				x = frange(fmaxf(value->min.x, tmp->value->min.x),
						fminf(value->max.x, tmp->value->max.x) - GRID_SIZE);
				add_hall((t_vector2){x, value->max.y}, (t_vector2){x
					+ GRID_SIZE, tmp->value->min.y}, &leafs->v_hall);
			}
			tmp = tmp->next;
		}
		leafs = leafs->next;
	}
}

void	initialize_data(const int height, t_bsp *data)
{
	ft_memset(data, 0, sizeof(t_bsp));
	data->size = (t_vector2){height * 16 / 9, height};
	data->array = allocate_map(&data->size);
	srand(time(NULL));
	data->map.root.min = (t_vector2){GRID_SIZE, GRID_SIZE};
	data->map.root.max = (t_vector2){data->size.x - GRID_SIZE, data->size.y
		- GRID_SIZE};
	data->map.root.width = data->size.x;
	data->map.root.height = data->size.y;
	data->map.nbr_room = 10;
	data->map.min_cell = GRID_SIZE * 2;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_hall(t_hall *hall)
{
	t_hall	*next;

	while (hall)
	{
		next = hall->next;
		free(hall->value);
		free(hall);
		hall = next;
	}
}

void	free_neighbor(t_neighbor *neighbor)
{
	t_neighbor	*next;

	while (neighbor)
	{
		next = neighbor->next;
		free(neighbor);
		neighbor = next;
	}
}

void	free_leafs(t_leaf *leafs)
{
	t_leaf	*next;

	while (leafs)
	{
		next = leafs->next;
		if (leafs->h_hall)
			free_hall(leafs->h_hall);
		if (leafs->v_hall)
			free_hall(leafs->v_hall);
		if (leafs->h_nei)
			free_neighbor(leafs->h_nei);
		if (leafs->v_nei)
			free_neighbor(leafs->v_nei);
		free(leafs);
		leafs = next;
	}
}

void	free_root(t_cell *cell)
{
	if (!cell)
		return ;
	free_root(cell->right);
	free_root(cell->left);
	free(cell);
}

void	free_all(t_bsp *data)
{
	if (data->array)
		free_array(data->array);
	if (data->map.leafs)
		free_leafs(data->map.leafs);
	if (data->map.root.left)
	{
		free_root(data->map.root.left);
		free_root(data->map.root.right);
	}
}

// https://www.roguebasin.com/index.php?title=Basic_BSP_Dungeon_generation
// https://www.youtube.com/watch?v=S5y3ES4Rvkk
// https://www.youtube.com/watch?v=Pj4owFPH1Hw
void	bsp(const int height)
{
	t_bsp	data;

	initialize_data(height, &data);
	divide_map(&data.map);
	find_neighbors(&data.map.root, &data.map.leafs);
	shrink(data.map.leafs, data.map.min_cell);
	generate_halls(data.map.leafs);
	update_array(data.map.leafs, data.array);
	save_to_file(data.array);
	free_all(&data);
}

void	add_room(t_leaf *leafs, t_room **result)
{
	t_room	*new_room;
	t_room	*tmp;

	new_room = ft_calloc(1, sizeof(t_room));
	new_room->h_hall = leafs->h_hall;
	new_room->v_hall = leafs->v_hall;
	new_room->value.min = (t_vector2){leafs->value->min.x, leafs->value->min.y};
	new_room->value.max = (t_vector2){leafs->value->max.x, leafs->value->max.y};
	new_room->value.size = (new_room->value.max.x - new_room->value.min.x)
		* (new_room->value.max.y - new_room->value.min.y);
	if (!*result)
	{
		*result = new_room;
		return ;
	}
	tmp = *result;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_room;
}

void	generate_room_list(t_leaf *leafs, t_room **result, int *room_nbr)
{
	t_leaf	*next;

	while (leafs)
	{
		next = leafs->next;
		(*room_nbr)++;
		add_room(leafs, result);
		if (leafs->h_nei)
			free_neighbor(leafs->h_nei);
		if (leafs->v_nei)
			free_neighbor(leafs->v_nei);
		free(leafs);
		leafs = next;
	}
}

t_room	*get_data(const int height, t_vector2 *size, char ***array,
		int *room_nbr)
{
	t_bsp	data;
	t_room	*result;

	result = NULL;
	initialize_data(height, &data);
	divide_map(&data.map);
	find_neighbors(&data.map.root, &data.map.leafs);
	shrink(data.map.leafs, data.map.min_cell);
	generate_halls(data.map.leafs);
	update_array(data.map.leafs, data.array);
	*array = data.array;
	*size = data.size;
	generate_room_list(data.map.leafs, &result, room_nbr);
	free_root(data.map.root.left);
	free_root(data.map.root.right);
	return (result);
}
