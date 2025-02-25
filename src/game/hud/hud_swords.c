/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_swords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:55:58 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:39:20 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_image	get_hud_sword(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.water[0].wh.x,
			data->textures.water[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[0], &combined);
	set_front_color(&data->textures.hud[4], &combined);
	return (combined);
}

void	print_hud_swords(t_data *data)
{
	int		s;
	int		i;
	t_image	combined;

	s = 2 - data->game.actual_sword;
	combined = get_hud_sword(data);
	i = 8;
	while (s != 0)
	{
		mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
			* PIXEL_PADDING, 0);
		s--;
		i++;
	}
	while (i < 10)
	{
		print_hud_empty(data, i);
		i++;
	}
	mlx_destroy_image(data->mlx, combined.image);
}
