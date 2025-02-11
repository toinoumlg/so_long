/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:23:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 16:10:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_ennemies_move(t_data *data, t_ennemy *tmp)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, tmp->coords.x * PIXEL_PADDING,
		tmp->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.ennemies[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->next_coords.x * PIXEL_PADDING, tmp->next_coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	tmp->coords = tmp->next_coords;
	tmp->next_coords = set_vector2(0, 0);
}

void	print_ennemies(t_data *data, t_ennemy *tmp)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.ennemies[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->coords.x * PIXEL_PADDING, tmp->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
}

void	is_ennemy_on_collectible(t_data *data, t_collectible *collectible)
{
	t_ennemy	*ennemy;
	t_ennemy	*ennemy_next;

	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy_next = ennemy->next_ennemy;
		if (ennemy->next_coords.y == collectible->coords.y
			&& ennemy->next_coords.x == collectible->coords.x)
			collectible_and_ennemy_move_print(data, collectible, ennemy);
		if (ennemy->coords.y == collectible->coords.y
			&& ennemy->coords.x == collectible->coords.x)
			collectible_and_ennemy_print(data, collectible, ennemy);
		ennemy = ennemy_next;
	}
}

void	is_ennemy_printed(t_data *data)
{
	t_ennemy	*ennemy;
	t_ennemy	*ennemy_next;

	if (!data->game.ennemies)
		return ;
	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy_next = ennemy->next_ennemy;
		if (!ennemy->is_printed)
		{
			if ((ennemy->next_coords.y || ennemy->next_coords.x)
				&& !ennemy->got_hit)
				print_ennemies_move(data, ennemy);
			else
				print_ennemies(data, ennemy);
		}
		ennemy = ennemy_next;
	}
}
