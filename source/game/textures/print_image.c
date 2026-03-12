/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 00:08:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/13 12:30:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	spawn_exit(t_data *data)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.ground[0].width;
	combined.height = data->textures.ground[0].height;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.exit[0], &combined);
	// mlx_put_img_to_window(data->mlx, data->window.ptr, combined.image,
	// 	data->window.exit.x * PIXEL_PADDING, data->window.exit.y
	// 	* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.ptr);
	data->game.game_finished = 2;
}
