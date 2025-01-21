/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 01:27:04 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/so_long.h"

void set_map(map *map)
{
	int fd;
	int i;

	fd = open("maps/map_ok.ber", O_RDWR);
	map->grid = ft_calloc(sizeof(char *), 10);
	i = 0;
	while (i < 10) {
		map->grid[i] = get_next_line(fd);
		if (i == 0)
			map->width = ft_strlen(map->grid[i]) - 1;
		if (!map->grid[i])
			break;
		i++;
	}
	close(fd);
	map->height = i;
	for (int j = 0; j < i ; j++)
		map->grid[j][map->width] = 0;
}

int		main()
{
	map map;
	set_map(&map);
	for (int i = 0; i < 7; i++)
	printf("[%s]\n", map.grid[i]);
}

