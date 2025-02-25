/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:04 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:31:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destroy_ennemy(t_ennemy **ennemies, t_vector2 coords, t_data *data)
{
	t_ennemy	*previous;
	t_ennemy	*ennemy;

	ennemy = *ennemies;
	if (ennemy->coords.x == coords.x && ennemy->coords.y == coords.y)
	{
		*ennemies = ennemy->next_ennemy;
		mlx_put_image_to_window(data->mlx, data->window.ptr,
			data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
			* PIXEL_PADDING);
		free(ennemy);
		return ;
	}
	while (ennemy != NULL && (ennemy->coords.x != coords.x
			|| ennemy->coords.y != coords.y))
	{
		previous = ennemy;
		ennemy = ennemy->next_ennemy;
	}
	previous->next_ennemy = ennemy->next_ennemy;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(ennemy);
}

int	add_new_ennemy(t_map *map, int x, int y)
{
	t_ennemy	*new_ennemy;
	t_ennemy	*tmp;

	new_ennemy = ft_calloc(sizeof(t_ennemy), 1);
	if (!new_ennemy)
		return (-1);
	new_ennemy->coords = set_vector2(y, x);
	new_ennemy->next_coords = set_vector2(0, 0);
	new_ennemy->i_image = 0;
	new_ennemy->got_hit = 0;
	new_ennemy->next_ennemy = NULL;
	if (!map->ennemies)
	{
		map->ennemies = new_ennemy;
		return (0);
	}
	tmp = map->ennemies;
	while (tmp->next_ennemy)
		tmp = tmp->next_ennemy;
	tmp->next_ennemy = new_ennemy;
	return (0);
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
