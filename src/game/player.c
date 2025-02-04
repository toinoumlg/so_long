/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:23:24 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/04 17:28:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_player(int key_stroked, t_data *data)
{
	char	*str;
	char	*itoa;

	itoa = ft_itoa(data->game.player.moves);
	str = ft_strjoin("player move: ", itoa);
	free(itoa);
	// mlx_string_put(data->mlx, data->window.ptr, 50, 50, 0xffd700, str);
	if (key_stroked == 119)
		data->window.move = data->game.moves.up;
	if (key_stroked == 97)
		data->window.move = data->game.moves.left;
	if (key_stroked == 115)
		data->window.move = data->game.moves.down;
	if (key_stroked == 100)
		data->window.move = data->game.moves.right;
	if (data->window.screen[data->window.actual.y
		+ data->window.move.y][data->window.actual.x
		+ data->window.move.x] != '1')
		update_screen_array(data);
	else
		data->window.move = data->game.moves.zero;
	free(str);
}

void	print_player(t_data *data)
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
	data->game.player.is_moving = 0;
	data->window.move = data->game.moves.zero;
	mlx_destroy_image(data->mlx, combined.image);
}
