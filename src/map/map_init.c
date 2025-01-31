/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/30 02:39:45 by amalangu         ###   ########.fr       */
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
	ft_printf("actual %d %d\n", map->actual.x, map->actual.y);
}

char	*set_file_path(char *file_name)
{
	char	*tmp;
	char	*file_path;

	file_path = ft_strjoin(PATH, file_name);
	file_path = ft_strjoin((tmp = file_path), BER);
	free(tmp);
	ft_printf("%s\n", file_path);
	return (file_path);
}

/* 5*PIXEL_PADDING for min height and width to have a 3x3 playable area */
int	init_map(t_map *map)
{
	int		fd;
	char	*file_path;

	file_path = set_file_path(map->file_name);
	fd = open(file_path, O_RDWR);
	if (fd < 0)
		return (ft_printf(RED "Error\nWrong map name" RESET), free(file_path),
			close(fd), -1);
	free(file_path);
	set_map_array(fd, map);
	map->max.y = (map->actual.y + 4) * PIXEL_PADDING;
	map->max.x = (map->actual.x + 4) * PIXEL_PADDING;
	map->min.y = 5;
	map->min.x = 5;
	ft_printf("max %d %d\nmin %d %d\nmap %d %d", map->max.y, map->max.x, 
	map->min.y ,map->min.y, map->actual.y,map->actual.x);
	if (map->max.y > SCREEN_HEIGHT || map->max.x > SCREEN_WIDTH
		|| map->min.x > map->actual.x || map->min.y > map->actual.y)
		return (ft_printf(RED "Error\nMap is too big or too small" RESET), -1);
	return (0);
}

int	set_map(t_map *map)
{
	int	error;

	if (init_map(map))
		return (free(map), -2);
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
