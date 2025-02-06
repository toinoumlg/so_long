/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/06 21:42:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_map_array(int fd, t_map *map)
{
	int	i;

	map->array = ft_calloc(sizeof(char *), SCREEN_HEIGHT / PIXEL_PADDING);
	i = 0;
	while (i < SCREEN_HEIGHT / PIXEL_PADDING)
	{
		map->array[i] = get_next_line(fd);
		if (i == 0)
			map->actual.x = (int)ft_strlen(map->array[i]) - 1;
		if (!map->array[i])
			break ;
		i++;
	}
	close(fd);
	map->actual.y = i;
}

/* 5*PIXEL_PADDING for min height and width to have a 3x3 playable area */
int	init_map(t_map *map)
{
	int		fd;
	char	*file_path;

	file_path = ft_strjoin(PATH, map->file_name);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (ft_printf(RED "Error\nWrong map name\n" RESET), free(file_path),
			close(fd), -1);
	free(file_path);
	set_map_array(fd, map);
	map->max = set_vector2((map->actual.y + 4) * PIXEL_PADDING, (map->actual.x
				+ 4) * PIXEL_PADDING);
	map->min = set_vector2(5, 5);
	if (map->max.y / 32 > SCREEN_HEIGHT || map->max.x / 32 > SCREEN_WIDTH
		|| map->min.x > map->actual.x || map->min.y > map->actual.y)
		return (ft_printf(RED "Error\nMap is too big or too small\n" RESET), -1);
	return (0);
}

int	set_map(t_map *map)
{
	int	error;

	if (init_map(map))
		return (free(map), -2);
	error = check_map(map);
	if (error == -1)
		return (free_map(map),
			ft_printf(RED "Error\nMap is not Rectangular\n" RESET), -1);
	if (error == -2)
		return (free_map(map),
			ft_printf(RED "Error\nBorder arent correct\n" RESET), -1);
	if (error == -3)
		return (free_collectibles(map->collectibles), free_map(map),
			ft_printf(RED "Error\nMissing either collectibles,exit or start\n"),
			ft_printf("Can also be a wrong character in map\n" RESET), -1);
	if (error == -4)
		return (free_collectibles(map->collectibles),free_map(map),
			ft_printf(RED "Error\nNo available path for "),
			ft_printf("taking collectibles and exiting\n" RESET), -1);
	return (0);
}
