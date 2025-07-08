/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_health.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:56:11 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 17:02:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_image	get_hud_hearth(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.water[0].wh.x,
			data->textures.water[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[0], &combined);
	set_front_color(&data->textures.hud[3], &combined);
	return (combined);
}

void	print_hud_health(t_data *data)
{
	int		i;
	int		j;
	t_image	combined;

	i = data->game.player.health;
	j = 5;
	combined = get_hud_hearth(data);
	while (i != 0)
	{
		mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, j
			* PIXEL_PADDING, 0);
		i--;
		j++;
	}
	while (j < 5 + 3)
	{
		print_hud_empty(data, j);
		j++;
	}
	mlx_destroy_image(data->mlx, combined.image);
}
