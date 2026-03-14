/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:50:42 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 20:52:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "internal.h"

#define ENEMY_SPAWN 10
#define COLLECTIBLE_SPAWN 10

void	try_ennemy(t_room *room, char **array)
{
	static int	ennemy_min_room_size = GRID_SIZE * 10 * 2;
	int			size;
	int			y;
	int			x;

	size = room->value.size;
	while (size >= ennemy_min_room_size)
	{
		y = range(room->value.min.y + GRID_SIZE, room->value.max.y - GRID_SIZE);
		x = range(room->value.min.x + GRID_SIZE, room->value.max.x - GRID_SIZE);
		if (array[y][x] == EMPTY && !(rand() % ENEMY_SPAWN))
			array[y][x] = ENNEMY;
		size -= ennemy_min_room_size;
	}
}

void	try_collectible(t_room *room, char **array)
{
	static int	collectible_min_room_size = GRID_SIZE * 10 * 2;
	int			size;
	int			y;
	int			x;

	size = room->value.size;
	while (size >= collectible_min_room_size)
	{
		y = range(room->value.min.y + GRID_SIZE, room->value.max.y - GRID_SIZE);
		x = range(room->value.min.x + GRID_SIZE, room->value.max.x - GRID_SIZE);
		if (array[y][x] == EMPTY && !(rand() % COLLECTIBLE_SPAWN))
			array[y][x] = COLLECTIBLE;
		size -= collectible_min_room_size;
	}
}

bool	is_tresure_room(t_room *room)
{
	static int	tresure_max_room_size = GRID_SIZE * 10 * 2;

	return (room->value.size < tresure_max_room_size && ((room->h_hall
				&& !room->h_hall->next) || (room->v_hall
				&& !room->v_hall->next)) && !(rand() % 3));
}

bool	compare_min(const t_vector2 *in, const t_vector2 *out)
{
	return (in->x >= out->x && in->y >= out->y);
}

void	set_player(t_room *rooms, char **array, t_vector2 *map_size)
{
	t_vector2	min;
	int			y;
	int			x;

	min = (t_vector2){(map_size->x * 3 / 8), (map_size->y * 3 / 8)};
	while (rooms)
	{
		if (compare_min(&rooms->value.min, &min))
		{
			y = range(rooms->value.min.y + GRID_SIZE, rooms->value.max.y
					- GRID_SIZE);
			x = range(rooms->value.min.x + GRID_SIZE, rooms->value.max.x
					- GRID_SIZE);
			array[y][x] = PLAYER;
			return ;
		}
		rooms = rooms->next;
	}
}

void	set_exit(t_room *rooms, char **array, t_vector2 *map_size)
{
	const t_vector2	min[4] = {{0, 0}, {0, map_size->y * 6 / 8}, {0, 0},
			{map_size->x * 6 / 8, 0}};
	int				x;
	int				y;

	while (rooms)
	{
		if (compare_min(&rooms->value.min, &min[rand() % 4]))
		{
			y = range(rooms->value.min.y + GRID_SIZE, rooms->value.max.y
					- GRID_SIZE);
			x = range(rooms->value.min.x + GRID_SIZE, rooms->value.max.x
					- GRID_SIZE);
			array[y][x] = END;
			return ;
		}
		rooms = rooms->next;
	}
}

void	populate_rooms(t_room *rooms, char **array, t_vector2 *map_size)
{
	if (!rooms)
		return ;
	set_player(rooms, array, map_size);
	set_exit(rooms, array, map_size);
	while (rooms)
	{
		if (is_tresure_room(rooms))
		{
			// spawn a treasure room 1 out 3 chance if only 1 corridor
			rooms = rooms->next;
			continue ;
		}
		try_collectible(rooms, array);
		try_ennemy(rooms, array);
		rooms = rooms->next;
	}
}
