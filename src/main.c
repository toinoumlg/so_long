/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 01:22:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (set_map(map))
		return (free_memory(map), -1);
	else
	{
		print_array(map);
		start(map);
	}
	free_memory(map);
}
