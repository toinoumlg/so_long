/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 22:00:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

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

void	map_parser(t_data *data, char **av, int ac)
{
	(void)ac;
	ft_memset(data, 0, sizeof(t_data));
	data->map.file_path = av[1];
	check_map_file(data->map.file_path);
	set_map_array(&data->map);
	check_map(data);
}
