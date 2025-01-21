/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:19:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 23:15:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_array(t_map *map)
{
	int				i;
	t_collectibles	*tmp;

	i = 0;
	while (map->array[i])
	{
		ft_printf("%s\n", map->array[i]);
		i++;
	}
	tmp = map->collectibles;
	while (tmp)
	{
		ft_printf("%d %d\n", tmp->x, tmp->y);
		tmp = tmp->next_collectible;
		i++;
	}
	ft_printf("%d %d\n", map->collectibles->x, map->collectibles->y);
	ft_printf("%d", i);
}
