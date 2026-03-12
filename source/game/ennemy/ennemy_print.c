/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:23:44 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:46:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_ennemies(t_data *data, t_ennemy *tmp)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.ennemies[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		tmp->coords.x * PIXEL_PADDING, tmp->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
}

void	is_ennemy_on_collectible(t_data *data, t_collectible *collectible)
{
	t_ennemy	*ennemy;
	t_ennemy	*ennemy_next;

	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy_next = ennemy->next;
		if (ennemy->next_coords.y == collectible->coords.y
			&& ennemy->next_coords.x == collectible->coords.x)
			collectible_and_ennemy_move_print(data, collectible, ennemy);
		if (ennemy->coords.y == collectible->coords.y
			&& ennemy->coords.x == collectible->coords.x)
			collectible_and_ennemy_print(data, collectible, ennemy);
		ennemy = ennemy_next;
	}
}

void	print_ennemy_on_exit(t_data *data, t_ennemy *ennemy)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.exit[0], &combined);
	set_front_color(&data->textures.ennemies[ennemy->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr,
		ennemy->coords.x * PIXEL_PADDING, ennemy->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	data->game.is_exit_printed = 1;
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
		ennemy_next = ennemy->next;
		if (!ennemy->is_printed)
			// {
			// 	if ((ennemy->next_coords.y || ennemy->next_coords.x)
			// 		&& !ennemy->got_hit)
			// 		print_ennemy_move(data, ennemy);
			// 	else if ((ennemy->coords.x == data->window.exit.x
			// 			&& ennemy->coords.y == data->window.exit.y)
			// 		&& (data->game.game_finished == 1
			// 			|| data->game.game_finished == 2))
			// 		print_ennemy_on_exit(data, ennemy);
			// 	else
			// 		print_ennemies(data, ennemy);
			// }
			ennemy = ennemy_next;
	}
}
