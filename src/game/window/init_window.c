/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:10:31 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/06 22:01:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	get_border_image_index(t_vector2 coords, t_vector2 min, t_vector2 max)
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

void	print_border_and_water(t_window *window, t_textures textures, void *mlx)
{
	char	c;
	int		i_border;

	c = window->screen[window->actual.y][window->actual.x];
	if (c == 'W')
		mlx_put_image_to_window(mlx, window->ptr, textures.water[rand()
			% 2].image, window->actual.x * PIXEL_PADDING, window->actual.y
			* PIXEL_PADDING);
	if (c == '1')
	{
		i_border = get_border_image_index(window->actual, window->min,
				window->max);
		if (i_border >= 0)
			mlx_put_image_to_window(mlx, window->ptr,
				textures.borders[i_border].image, window->actual.x
				* PIXEL_PADDING, window->actual.y * PIXEL_PADDING);
		else
			combine_image(textures.walls[rand() % 6], textures.ground[rand()
				% 2], mlx, *window);
	}
}

void	wich_texture_to_print(t_window *window, t_textures textures, void *mlx)
{
	char	c;

	c = window->screen[window->actual.y][window->actual.x];
	if (c == 'W' || c == '1')
		print_border_and_water(window, textures, mlx);
	if (c == 'P')
		combine_image(textures.player[0], textures.ground[rand() % 2], mlx,
			*window);
	if (c == '0' || c == 'E')
		mlx_put_image_to_window(mlx, window->ptr, textures.ground[rand()
			% 2].image, window->actual.x * PIXEL_PADDING, window->actual.y
			* PIXEL_PADDING);
	if (c == 'C')
		combine_image(textures.coins_r[0], textures.ground[rand() % 2], mlx,
			*window);
	if (c == '2')
		combine_image(textures.ennemies[0], textures.ground[0], mlx, *window);
	window->actual.x++;
}

void	print_screen_array(char **screen, t_textures textures, t_window *window,
		void *mlx)
{
	window->actual.y = 0;
	while (screen[window->actual.y])
	{
		window->actual.x = 0;
		while (screen[window->actual.y][window->actual.x])
			wich_texture_to_print(window, textures, mlx);
		window->actual.y++;
	}
}

void	init_window(t_map *map, t_window *window, void *mlx,
		t_textures textures)
{
	window->screen = ft_calloc(sizeof(char *), (map->actual.y + 4) + 1);
	window->min = set_vector2(2, 2);
	window->max = set_vector2(map->actual.y + 2, map->actual.x + 2);
	init_screen_array(map, window);
	window->ptr = mlx_new_window(mlx, (map->actual.x + 4) * PIXEL_PADDING,
			(map->actual.y + 4) * PIXEL_PADDING, "so_long");
	print_screen_array(window->screen, textures, window, mlx);
	window->exit = set_vector2(map->exit.y + window->min.y, map->exit.x
			+ window->min.x);
	window->actual = set_vector2(map->player_start.y + window->min.y,
			map->player_start.x + window->min.x);
	free_map(map);
}
