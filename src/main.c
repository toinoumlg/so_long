/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 14:30:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(void)
{
	t_map	map;
	int		map_error;

	map_error = set_map(&map);
	if (map_error)
		ft_printf("map_error %d", map_error);
	else
		ft_printf("map ok %d", map_error);
	free_memory(&map);
}
