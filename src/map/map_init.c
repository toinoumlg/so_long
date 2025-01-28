/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/27 17:48:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* 5*PIXEL_PADDING for min height and width to have a 3x3 playable area */
int	init_map(t_map *map)
{
	int		fd;
	int		i;
	char	*file_path;
	char	*tmp;

	file_path = ft_strjoin(PATH, map->file_name);
	file_path = ft_strjoin((tmp = file_path), BER);
	free(tmp);
	fd = open(file_path, O_RDWR);
	if (fd < 0)
	{
		free(file_path);
		close(fd);
		return (-1);
	}
	map->max_height = SCREEN_HEIGHT / PIXEL_PADDING;
	map->max_width = SCREEN_WIDTH / PIXEL_PADDING;
	map->min_width = PIXEL_PADDING * 5;
	map->min_height = PIXEL_PADDING * 5;
	map->array = ft_calloc(sizeof(char *), map->max_height);
	i = 0;
	while (i < map->max_height)
	{
		map->array[i] = get_next_line(fd);
		if (i == 0)
			map->width = (int)ft_strlen(map->array[i]) - 1;
		if (!map->array[i])
			break ;
		i++;
	}
	close(fd);
	free(file_path);
	map->height = i;
	return (0);
}

int	set_map(t_map *map)
{
	int	error;

	if (init_map(map))
		return (free(map), ft_printf(RED "Error\nWrong map name" RESET), -2);
	error = check_map(map);
	if (error == -1)
		return (free_memory_map(map),
			ft_printf(RED "Error\nMap is not Rectangular" RESET), -1);
	if (error == -2)
		return (free_memory_map(map),
			ft_printf(RED "Error\nBorder arent correct" RESET), -1);
	if (error == -3)
		return (free_memory_map(map),
			ft_printf(RED "Error\nMissing either collectibles,exit or start "),
			ft_printf("(can be double or missing max collectibles 30)" RESET),
			-1);
	if (error == -4)
		return (free_memory_map(map),
			ft_printf(RED "Error\nNo available path for "),
			ft_printf("taking collectibles and exiting" RESET), -1);
	return (0);
}
