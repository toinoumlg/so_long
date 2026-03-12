/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:31:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

char	**get_map_size(t_map *map, char *path)
{
	char	*gnl;
	char	**array;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(parsing_error(NULL, FAILED_OPEN));
	while (1)
	{
		gnl = get_next_line(fd);
		if (!gnl)
			break ;
		map->max.y++;
		free(gnl);
	}
	close(fd);
	array = ft_calloc(sizeof(char *), map->max.y + 1);
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

void	load_map(t_map *map, char *path)
{
	int	i;
	int	fd;

	map->array = get_map_size(map, path);
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(parsing_error(NULL, FAILED_OPEN));
	while (1)
	{
		map->array[i] = gnl_no_line_feed(fd);
		if (!map->array[i++])
			break ;
	}
	close(fd);
}

void	check_map_file(char *file_path)
{
	int		fd;
	char	*ber;

	ber = ft_strnstr(file_path, ".ber", ft_strlen(file_path));
	if (ft_strncmp(ber, ".ber", 5))
		exit(parsing_error(NULL, INVALID_EXTENSION));
	fd = open(file_path, __O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		exit(parsing_error(NULL, FILE_DOESNT_EXIST));
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit(parsing_error(NULL, FILE_DOESNT_EXIST));
	close(fd);
}

void	map_parser(t_data *data, char **av, int ac)
{
	if (ac != 2)
		exit(parsing_error(NULL, WRONG_ARGUMENTS));
	ft_memset(data, 0, sizeof(t_data));
	check_map_file(av[1]);
	load_map(&data->map, av[1]);
	check_map(data);
}
