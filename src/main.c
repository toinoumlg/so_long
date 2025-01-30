/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 22:57:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;
	data.mlx = mlx_init();
	if (ac > 2)
		return (ft_printf(RED "Error\nToo much arguments" RESET), -1);
	data.map = ft_calloc(sizeof(t_map), 1);
	if (ac == 1)
		data.map->file_name = "debbug";
	else
		data.map->file_name = av[1];
	if (set_map(data.map))
		return (free(data.mlx), -1);
	print_array(data.map->array);
	game(data);
	// free(get_next_line(0));
}
