/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 10:51:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_map(t_map *map)
{
	int	fd;
	int	i;

	fd = open("maps/map_ok_big3.ber", O_RDWR);
	map->max_height = SCREEN_HEIGHT / 32;
	map->max_width = SCREEN_WIDTH / 32;
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
