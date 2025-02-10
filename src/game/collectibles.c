/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:33:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/09 17:28:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	collectible_and_sword_print(t_data *data, t_collectible *collectible,
		t_sword *sword)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	collectible->i_image++;
	if (collectible->i_image > 12)
		collectible->i_image = 0;
	set_front_color_offset(&data->textures.player_axe[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		collectible->coords.x * PIXEL_PADDING, collectible->coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
}

void	collectible_and_ennemy_print(t_data *data, t_collectible *collectible,
		t_ennemy *ennemy)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color_offset(&data->textures.ennemies[ennemy->i_image],
		&combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		collectible->coords.x * PIXEL_PADDING, collectible->coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	ennemy->is_printed = 1;
	collectible->is_printed = 1;
}

void	add_new_collectible(t_map *map, int x, int y)
{
	t_collectible	*new_collectible;
	t_collectible	*tmp;

	new_collectible = ft_calloc(sizeof(t_collectible), 1);
	new_collectible->coords = set_vector2(y, x);
	new_collectible->i_image = rand() % 13;
	new_collectible->is_printed = 0;
	new_collectible->next_collectible = NULL;
	if (!map->collectibles)
	{
		map->collectibles = new_collectible;
		return ;
	}
	tmp = map->collectibles;
	while (tmp->next_collectible)
		tmp = tmp->next_collectible;
	tmp->next_collectible = new_collectible;
	return ;
}

void	destroy_collectible(t_collectible **collectibles, t_vector2 coords)
{
	t_collectible	*previous;
	t_collectible	*tmp;

	tmp = *collectibles;
	if (tmp->coords.x == coords.x && tmp->coords.y == coords.y)
	{
		*collectibles = tmp->next_collectible;
		free(tmp);
		return ;
	}
	while (tmp != NULL && (tmp->coords.x != coords.x
			|| tmp->coords.y != coords.y))
	{
		previous = tmp;
		tmp = tmp->next_collectible;
	}
	previous->next_collectible = tmp->next_collectible;
	free(tmp);
}

void	update_collectible_coords(t_collectible *collectibles, t_vector2 min)
{
	t_collectible	*tmp;

	tmp = collectibles;
	while (tmp)
	{
		tmp->coords.x += min.x;
		tmp->coords.y += min.y;
		tmp = tmp->next_collectible;
	}
}
