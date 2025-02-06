/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/06 18:39:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 2)
		return (ft_printf(RED "Error\nToo much arguments\n" RESET), -1);
	data.map = ft_calloc(sizeof(t_map), 1);
	if (ac == 1)
		data.map->file_name = DEBBUG;
	else
		data.map->file_name = av[1];
	if (set_map(data.map))
		return (-1);
	print_array(data.map->array);
	game(data);
}
