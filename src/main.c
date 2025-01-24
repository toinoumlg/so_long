/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 00:34:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(void)
{
	t_map	*map;
	int		check;

	map = ft_calloc(sizeof(t_map), 1);
	if (set_map(map))
	{
		ft_printf("Error\nMap is not Rectangular");
		free_memory(map);
		return (-1);
	}
	check = check_map(map);
	if (check == -1)
		ft_printf("Error\nBorder arent correct");
	else if (check == -2)
		ft_printf("Error\nMissing either collectibles,exit or start (can be double or missing max collectibles 30)");
	else if (check == -3)
		ft_printf("Error\nNo available path for taking collectibles and exiting");
	else
		print_array(map);
	free_memory(map);
}
