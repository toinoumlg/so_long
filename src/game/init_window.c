/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 01:06:48 by amalangu         ###   ########.fr       */
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

unsigned int	get_pixel_color(t_image *image, t_coords i)
{
	return (*(unsigned int *)(image->addr + (i.y * image->size_l + i.x
				* (image->bpp / 8))));
}

void	put_pixel(t_image *image, t_coords i, unsigned int color)
{
	char	*pixel;

	pixel = image->addr + (i.y * image->size_l + i.x * (image->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	set_background_color(t_image *background, t_image *combined)
{
	t_coords	i;

	i.y = 0;
	while (i.y < background->wh.y)
	{
		i.x = 0;
		while (i.x < background->wh.x)
		{
			put_pixel(combined, i, get_pixel_color(background, i));
			i.x++;
		}
		i.y++;
	}
}

void	set_front_color(t_image *front, t_image *combined)
{
	unsigned int	front_color;
	t_coords		i;

	i.y = 0;
	while (i.y < front->wh.y)
	{
		i.x = 0;
		while (i.x < front->wh.x)
		{
			front_color = get_pixel_color(front, i);
			if ((front_color & 0xFF000000) == 0)
				put_pixel(combined, i, front_color);
			i.x++;
		}
		i.y++;
	}
}

void	combine_image(t_image background, t_image front, void *mlx,
		t_window window, t_coords i)
{
	t_image	combined;

	combined.image = mlx_new_image(mlx, background.wh.x, background.wh.y);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = background.wh;
	set_background_color(&background, &combined);
	set_front_color(&front, %combined);
	mlx_put_image_to_window(mlx, window.ptr, combined->image, i.x
		* PIXEL_PADDING, i.y * PIXEL_PADDING);
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
	if (c == '0' || c == 'C')
		mlx_put_image_to_window(mlx, window.ptr, textures.ground[rand()
			% 2].image, i->x * PIXEL_PADDING, i->y * PIXEL_PADDING);
	if (c == '1')
	{
		i_border = get_border_image_index(*i, window.min, window.max);
		if (i_border >= 0)
			mlx_put_image_to_window(mlx, window.ptr,
				textures.border[i_border].image, i->x * PIXEL_PADDING, i->y
				* PIXEL_PADDING);
		else
			combine_image(textures.ground[0], textures.walls[0], mlx, window,
				*i);
	}
	i->x++;
}

void	print_screen_array(char **screen, t_textures textures, t_window window,
		void *mlx)
{
	t_coords	i;

	i.y = 0;
	while (screen[i.y])
	{
		i.x = 0;
		while (screen[i.y][i.x])
			wich_texture_to_print(&i, window, textures, mlx);
		i.y++;
	}
}

void	init_window(t_map *map, t_window window, void *mlx, t_textures textures)
{
	window.screen = ft_calloc(sizeof(char *), SCREEN_HEIGHT / PIXEL_PADDING
			+ 1);
	get_map_coords_in_screen(&window, map);
	init_screen_array(map, window);
	window.ptr = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"caca dans culotte");
	print_screen_array(window.screen, textures, window, mlx);
	(void)textures;
}