/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 00:08:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/10 22:37:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_move_string(t_data *data)
{
	t_image	combined;
	char	*str;
	char	*itoa;
	char	*tmp;
	int		i;
	int		j;
	int		s;

	s = 2 - data->game.actual_axes;
	j = data->game.player.health;
	i = -1;
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
	while (i++ < data->window.max.x + 1)
	{
		combined.image = mlx_new_image(data->mlx, data->textures.ground[0].wh.x,
				data->textures.ground[0].wh.y);
		combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
				&combined.size_l, &combined.endian);
		combined.wh = data->textures.ground[0].wh;
		set_background_color(&data->textures.ground[0], &combined);
		if (i == 0)
		{
			set_front_color(&data->textures.hud[1], &combined);
			mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
				i * PIXEL_PADDING, 0);
			mlx_destroy_image(data->mlx, combined.image);
		}
		else if (i == data->window.max.x + 1)
		{
			set_front_color(&data->textures.hud[2], &combined);
			mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
				i * PIXEL_PADDING, 0);
			mlx_destroy_image(data->mlx, combined.image);
		}
		else if (i > 5 && j != 0)
		{
			set_front_color(&data->textures.hud[0], &combined);
			set_front_color_offset(&data->textures.heart[0], &combined);
			mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
				i * PIXEL_PADDING, 0);
			mlx_destroy_image(data->mlx, combined.image);
			j--;
		}
		else if (i > 5 + data->game.player.health && s != 0)
		{
			set_front_color(&data->textures.hud[0], &combined);
			set_front_color_offset(&data->textures.player_axe[0], &combined);
			mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
				i * PIXEL_PADDING, 0);
			mlx_destroy_image(data->mlx, combined.image);
			s--;
		}
		else
		{
			set_front_color(&data->textures.hud[0], &combined);
			mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
				i * PIXEL_PADDING, 0);
			mlx_destroy_image(data->mlx, combined.image);
		}
	}
	mlx_string_put(data->mlx, data->window.ptr, 10, 20, 0xffd700, str);
	free(str);
}

void	spawn_exit(t_data *data)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.exit[0], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		data->window.exit.x * PIXEL_PADDING, data->window.exit.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	data->game.game_finished = 2;
}

void	print_collectibles(t_data *data, t_collectible *tmp)
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
	tmp->is_printed = 1;
}

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
