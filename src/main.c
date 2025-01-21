/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 10:56:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/so_long.h"

void get_resolution(int fd, t_map *map) {
	char *raw_res;

	map->screen_res = malloc(sizeof(char *) * 2);
	map->screen_res[0] = malloc(sizeof(char) * 5);
	map->screen_res[1] = malloc(sizeof(char) * 5);
	raw_res = get_next_line(fd);
	ft_strlcpy(map->screen_res[0], raw_res, 5);
	ft_strlcpy(map->screen_res[1], raw_res + 5, 5);
	free(raw_res);
	map->max_width = ft_atoi(map->screen_res[0]) / 32;
	map->max_height = ft_atoi(map->screen_res[1]) / 32;
	close(fd);
}

void set_map(t_map *map)
{
	int fd;
	int i;
	get_resolution(open("config.txt", O_RDWR), map);
	fd = open("maps/map_ok.ber", O_RDWR);
	map->array = ft_calloc(sizeof(char *), map->max_height);
	i = 0;
	while (i < map->max_height) {
		map->array[i] = get_next_line(fd);
		if (i == 0)
			map->width = (int)ft_strlen(map->array[i]) - 1;
		if (!map->array[i])
			break;
		i++;
	}
	close(fd);
	map->height = i;
	for (int j = 0; j < i ; j++)
		map->array[j][map->width] = 0;
}

void	free_memory(t_map *map) {
	free(map->screen_res[0]);
	free(map->screen_res[1]);
	free(map->screen_res);
	int i = 0;
	while (10) {
		if (map->array[i]) {
			free(map->array[i]);
			i++;
		}
		else
			break;
	}
	free(map->array);
}

void	check_map(t_map *map) {

}

int		main()
{
	t_map map;
	set_map(&map);
	check_map(&map);
	free_memory(&map);
}

