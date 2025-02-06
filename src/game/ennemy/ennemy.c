/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:04 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/07 00:13:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update_ennemies(t_data *data)
{
	t_ennemy	*tmp;

	tmp = data->game.ennemies;
	while (tmp)
	{
		if (tmp->next_coords.x)
			print_ennemies_move(data, tmp);
		else
			print_ennemies(data, tmp);
		tmp->i_image++;
		if (tmp->i_image > 10)
			tmp->i_image = 0;
		tmp = tmp->next_ennemy;
	}
}

void	add_new_ennemy(t_map *map, int x, int y)
{
	t_ennemy	*new_ennemy;
	t_ennemy	*tmp;

	new_ennemy = ft_calloc(sizeof(t_ennemy), 1);
	new_ennemy->coords = set_vector2(y, x);
	new_ennemy->next_coords = set_vector2(0, 0);
	new_ennemy->i_image = 0;
	new_ennemy->next_ennemy = NULL;
	if (!map->ennemies)
	{
		map->ennemies = new_ennemy;
		return ;
	}
	tmp = map->ennemies;
	while (tmp->next_ennemy)
		tmp = tmp->next_ennemy;
	tmp->next_ennemy = new_ennemy;
	return ;
}

void	update_ennemies_coords(t_ennemy *ennemies, t_vector2 coords)
{
	t_ennemy	*tmp;

	tmp = ennemies;
	while (tmp)
	{
		tmp->coords.x += coords.x;
		tmp->coords.y += coords.y;
		tmp = tmp->next_ennemy;
	}
}
