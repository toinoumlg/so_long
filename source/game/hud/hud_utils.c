/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:59:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:56:23 by amalangu         ###   ########.fr       */
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
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, data->textures.water[0].width,
			data->textures.water[0].height);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.water[0].width;
	combined.height = data->textures.water[0].height;
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[1], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.ptr);
}

void	print_hud_right_corner(t_data *data, int i)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, data->textures.water[0].width,
			data->textures.water[0].height);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.water[0].width;
	combined.height = data->textures.water[0].height;
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[2], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.ptr);
}

void	print_hud_empty(t_data *data, int i)
{
	t_img	combined;

	combined.ptr = mlx_new_image(data->mlx, data->textures.water[0].width,
			data->textures.water[0].height);
	combined.addr = (t_pxl *)mlx_get_data_addr(combined.ptr, &combined.bpp,
			&combined.lenght, &combined.endian);
	combined.width = data->textures.water[0].width;
	combined.height = data->textures.water[0].height;
	set_background_color(&data->textures.water[0], &combined);
	set_front_color(&data->textures.hud[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.ptr, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.ptr);
}
