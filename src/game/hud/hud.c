/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:59:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 12:22:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*string_hud(t_data *data)
{
	char	*itoa;
	char	*str;
	char	*tmp;

	itoa = ft_itoa(data->game.player.moves);
	str = ft_strjoin("player move: ", itoa);
	free(itoa);
	str = ft_strjoin((tmp = str), ";  ");
	free(tmp);
	itoa = ft_itoa((int)data->timer.time);
	str = ft_strjoin((tmp = str), itoa);
	free(tmp);
	free(itoa);
	str = ft_strjoin((tmp = str), "s");
	free(tmp);
	return (str);
}

void	print_hud_left_corner(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.ground[0].wh.x,
			data->textures.ground[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_front_color(&data->textures.hud[1], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_hud_right_corner(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.ground[0].wh.x,
			data->textures.ground[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_front_color(&data->textures.hud[2], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_hud_empty(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.ground[0].wh.x,
			data->textures.ground[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_front_color(&data->textures.hud[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_hud_health(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.ground[0].wh.x,
			data->textures.ground[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	set_front_color(&data->textures.hud[0], &combined);
	set_front_color_offset(&data->textures.heart[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_hud_sword(t_data *data, int i)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, data->textures.ground[0].wh.x,
			data->textures.ground[0].wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	set_front_color(&data->textures.hud[0], &combined);
	set_front_color_offset(&data->textures.player_axe[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image, i
		* PIXEL_PADDING, 0);
	mlx_destroy_image(data->mlx, combined.image);
}

void	print_move_string(t_data *data)
{
	char *str;
	int i;
	int j;
	int s;

	str = string_hud(data);
	s = 2 - data->game.actual_sword;
	j = data->game.player.health;
	i = -1;
	while (i++ < data->window.max.x + 1)
	{
		if (i == 0)
			print_hud_left_corner(data, i);
		else if (i == data->window.max.x + 1)
			print_hud_right_corner(data, i);
		else if (i > 5 && j != 0)
		{
			print_hud_health(data, i);
			j--;
		}
		else if (i > 5 + data->game.player.health && s != 0)
		{
			print_hud_sword(data, i);
			s--;
		}
		else
			print_hud_empty(data, i);
	}
	mlx_string_put(data->mlx, data->window.ptr, 10, 20, 0xffd700, str);
	free(str);
}