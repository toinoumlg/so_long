/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 14:30:34 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_memory(t_map *map)
{
	int	i;

	free(map->screen_res[0]);
	free(map->screen_res[1]);
	free(map->screen_res);
	i = 0;
	while (10)
	{
		if (map->array[i])
		{
			free(map->array[i]);
			i++;
		}
		else
			break ;
	}
	free(map->array);
}
