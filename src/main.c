/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 12:58:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac > 2)
		return (ft_printf(RED "Error\nToo much arguments" RESET), -1);
	map = ft_calloc(sizeof(t_map), 1);
	if (ac == 1)
		map->file_name = "map_ok_debbug";
	else
		map->file_name = av[1];
	if (set_map(map))
		return (free_memory(map), -1);
	else
	{
		print_array(map);
		start(map);
	}
	free_memory(map);
	// free(get_next_line(0));
}
