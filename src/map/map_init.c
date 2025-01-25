/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 01:31:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_resolution(int fd, t_map *map)
{
	char	*raw_res;

	map->screen_res = ft_calloc(sizeof(char *), 2);
	map->screen_res[0] = ft_calloc(sizeof(char), 5);
	map->screen_res[1] = ft_calloc(sizeof(char), 5);
	raw_res = get_next_line(fd);
	ft_strlcpy(map->screen_res[0], raw_res, 5);
	ft_strlcpy(map->screen_res[1], raw_res + 5, 5);
	free(raw_res);
	map->max_width = ft_atoi(map->screen_res[0]) / PIXEL_PADDING;
	map->max_height = ft_atoi(map->screen_res[1]) / PIXEL_PADDING;
	close(fd);
}

void	init_map(t_map *map)
{
	int	fd;
	int	i;

	fd = open("maps/map_ok_big3.ber", O_RDWR);
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
	map->height = i;
}

int	check_if_rectangular(t_map *map)
{
	char	*tmp;
	char	*cr;
	int		i;

	i = 0;
	while (i < map->height)
	{
		cr = ft_strchr(map->array[i], '\n');
		if (cr)
		{
			map->array[i] = ft_strtrim((tmp = map->array[i]), cr);
			free(tmp);
		}
		if (((int)ft_strlen(map->array[i])) != map->width)
			return (-1);
		i++;
	}
	return (0);
}

int	set_map(t_map *map)
{
	int	error;

	get_resolution(open("config.txt", O_RDWR), map);
	init_map(map);
	if (check_if_rectangular(map))
		return (ft_printf("Error\nMap is not Rectangular"), -1);
	error = check_map(map);
	if (error == -1)
		return (ft_printf("Error\nBorder arent correct"), -1);
	if (error == -2)
	{
		ft_printf("Error\nMissing either collectibles,exit or start ");
		ft_printf("(can be double or missing max collectibles 30)");
		return (-1);
	}
	if (error == -3)
	{
		ft_printf("Error\nNo available path for ");
		ft_printf("taking collectibles and exiting");
		return (-1);
	}
	return (0);
}
