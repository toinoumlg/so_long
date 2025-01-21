/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 15:29:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(void)
{
	t_map	map;

	if (set_map(&map))
		ft_printf("map_error\n");
	else
		ft_printf("map size ok\n");
	if (check_map(&map))
		ft_printf("map_error\n");
	else
		ft_printf("map ok\n");
	print_array(&map);
	free_memory(&map);
}
