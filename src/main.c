/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:57:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_printf(RED "Error\nNo or too much arguments\n" RESET),
			-1);
	data.map = ft_calloc(sizeof(t_map), 1);
	if (!data.map)
		return (ft_printf(RED "Error\nFailed calloc on map\n" RESET), -1);
	else
		data.map->file_name = av[1];
	if (set_map(data.map))
		return (-1);
	game(data);
}
