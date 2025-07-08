/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:59:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 16:59:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*string_hud(t_data *data)
{
	char	*itoa;
	char	*str;

	itoa = ft_itoa((int)data->timer.time);
	str = ft_strjoin(itoa, "s");
	free(itoa);
	return (str);
}

void	print_hud_left_corner(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.water[0].wh.x,
			data->textures.water[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.water[0].wh;
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[1], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_hud_right_corner(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.water[0].wh.x,
			data->textures.water[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.water[0].wh;
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[2], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_hud_empty(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.water[0].wh.x,
			data->textures.water[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.water[0].wh;
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}
