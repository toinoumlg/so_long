/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:10:31 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 17:21:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	get_border_image_index(t_coords coords, t_coords min, t_coords max)
{
	if (coords.y == min.y && coords.x == min.x)
		return (7);
	else if (coords.y == max.y - 1 && coords.x == min.x)
		return (5);
	else if (coords.x == min.x)
		return (6);
	else if (coords.y == min.y && coords.x == max.x - 1)
		return (1);
	else if (coords.y == max.y - 1 && coords.x == max.x - 1)
		return (3);
	else if (coords.x == max.x - 1)
		return (2);
	else if (coords.y == max.y - 1)
		return (4);
	else if (coords.y == min.y)
		return (0);
	else
		return (-1);
}

void	wich_texture_to_print(t_coords *i, t_window window, t_textures textures,
		void *mlx)
{
	int		i_border;
	char	c;

	c = window.screen[i->y][i->x];
	if (c == 'W')
		mlx_put_image_to_window(mlx, window.ptr, textures.water[rand()
			% 2].image, i->x * PIXEL_PADDING, i->y * PIXEL_PADDING);
	if (c == 'P')
		combine_image(textures.player[0], textures.ground[rand() % 2],
			mlx, window, *i);
	if (c == '0')
		mlx_put_image_to_window(mlx, window.ptr, textures.ground[rand()
			% 2].image, i->x * PIXEL_PADDING, i->y * PIXEL_PADDING);
	if (c == 'C')
		combine_image(textures.walls[rand() % 6], textures.ground[rand() % 2],
			mlx, window, *i);
	if (c == '1')
	{
		i_border = get_border_image_index(*i, window.min, window.max);
		if (i_border >= 0)
			mlx_put_image_to_window(mlx, window.ptr,
				textures.border[i_border].image, i->x * PIXEL_PADDING, i->y
				* PIXEL_PADDING);
		else
			combine_image(textures.walls[rand() % 6], textures.ground[rand()
				% 2], mlx, window, *i);
	}
	i->x++;
}

void	print_screen_array(char **screen, t_textures textures, t_window *window,
		void *mlx)
{
	t_coords i;

	i.y = 0;
	while (screen[i.y])
	{
		i.x = 0;
		while (screen[i.y][i.x])
			wich_texture_to_print(&i, *window, textures, mlx);
		i.y++;
	}
}