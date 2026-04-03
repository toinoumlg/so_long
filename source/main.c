/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/14 15:54:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar.h"
#include "bsp.h"
#include "data.h"
#include "internal.h"
#include "mem.h"
#include "str.h"

// for testing purpose
int	main(int ac, char *av[])
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac > 2)
		exit(1);
	if (ac == 2)
		load_map(&data, av[1]);
	else
	{
		data.map.rooms = get_data(MAP_HEIGHT, &data.map.size, &data.map.array,
				&data.map.room_nbr);
		populate_rooms(data.map.rooms, data.map.array, &data.map.size);
		save_to_file(data.map.array);
	}
	check_map(&data);
	// init_engine(&data);
	free_map(&data.map);
	free_collectibles(data.collectibles);
	free_ennemies(data.ennemies);
	return (0);
}
