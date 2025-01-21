/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/20 23:49:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/so_long.h"

void set_map(map *map)
{
	int fd;
	int i;
	char  *file_name = "maps/" + map->file_name;

	fd = open("maps/map->file_name", O_RDWR);
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
	ft
}

int		main(int ac, char **av)
{
	map map;
	(void)ac;

	printf("%s",map.file_name = av[1]);
	set_map(&map);
	for (int i = 0; i < 7; i++)
	printf("[%s]\n", map.grid[i]);
}

