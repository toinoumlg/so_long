/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 09:39:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error_string.h"
#include "../include/so_long.h"

int	parsing_error(t_map *map, char *error_string)
{
	free_map(map);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error_string, 2);
	ft_putstr_fd(RESET, 2);
	return (1);
}

char	**set_map_array_size(t_map *map)
{
	int		height;
	char	*gnl;
	char	**array;
	int		fd;

	fd = open(map->file_path, O_RDONLY);
	height = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		height++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	array = ft_calloc(sizeof(char *), height + 1);
	if (!array)
		exit(parsing_error(NULL, ALLOC_ERROR));
	return (array);
}

char	*gnl_no_line_feed(int fd)
{
	char	*gnl;
	char	*line_feed;

	gnl = get_next_line(fd);
	if (!gnl)
		return (NULL);
	line_feed = ft_strrchr(gnl, '\n');
	if (line_feed)
		*line_feed = 0;
	return (gnl);
}

void	set_map_array(t_map *map)
{
	int	i;
	int	fd;

	map->array = set_map_array_size(map);
	i = 0;
	fd = open(map->file_path, O_RDONLY);
	map->array[i] = gnl_no_line_feed(fd);
	while (map->array[i])
		map->array[++i] = gnl_no_line_feed(fd);
	close(fd);
	print_array(map->array);
}

void	check_map_file(char *file_path)
{
	int	fd;

	if (ft_strncmp(ft_strnstr(file_path, ".ber", ft_strlen(file_path)), ".ber",
			5))
		exit(parsing_error(NULL, INVALID_EXTENSION));
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit(parsing_error(NULL, FILE_DOESNT_EXIST));
	close(fd);
}

int	map_parser(t_map *map, char **av, int ac)
{
	(void)ac;
	ft_memset(map, 0, sizeof(t_map));
	map->file_path = av[1];
	check_map_file(map->file_path);
	set_map_array(map);
	check_map(map);
	// if (error == -1)
	// 	return (free_map(map),
	// 		ft_printf(RED "Error\nMap is not Rectangular\n" RESET), -1);
	// if (error == -2)
	// 	return (free_map(map),
	// 		ft_printf(RED "Error\nBorder arent correct\n" RESET), -1);
	// if (error == -3)
	// 	return (free_collectibles(map->collectibles), free_map(map),
	// 		ft_printf(RED "Error\nMissing either collectibles,exit or start\n"),
	// 		ft_printf("Can also be a wrong character in map\n" RESET), -1);
	// if (error == -4)
	// 	return (free_collectibles(map->collectibles), free_map(map),
	// 		ft_printf(RED "Error\nNo available path for "),
	// 		ft_printf("taking collectibles and exiting\n" RESET), -1);
	return (0);
}
