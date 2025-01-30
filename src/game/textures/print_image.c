/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 00:08:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/30 00:09:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_collectibles(t_data *data, t_collectibles *tmp)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[tmp->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->coords.x * PIXEL_PADDING, tmp->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
}

void print_player(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.player[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, data->window.actual.x * PIXEL_PADDING,
		data->window.actual.y * PIXEL_PADDING);
	data->window.actual.y += data->window.move.y;
	data->window.actual.x += data->window.move.x;
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		data->window.actual.x * PIXEL_PADDING, data->window.actual.y
		* PIXEL_PADDING);
	data->window.move = data->game.move.zero;
	mlx_destroy_image(data->mlx, combined.image);
}