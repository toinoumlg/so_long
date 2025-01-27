/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/27 01:06:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_textures(t_textures *textures, void *mlx)
{
	int	c;

	textures->wall = ft_calloc(sizeof(void *), 1);
	textures->ground = ft_calloc(sizeof(void *), 2);
	textures->water = ft_calloc(sizeof(void *), 2);
	textures->border = ft_calloc(sizeof(void *), 8);
	textures->wall[0] = mlx_xpm_file_to_image(mlx, WALL1, &c, &c);
	textures->ground[0] = mlx_xpm_file_to_image(mlx, GROUND1, &c, &c);
	textures->ground[1] = mlx_xpm_file_to_image(mlx, GROUND2, &c, &c);
	textures->water[0] = mlx_xpm_file_to_image(mlx, WATER1, &c, &c);
	textures->water[1] = mlx_xpm_file_to_image(mlx, WATER2, &c, &c);
	textures->border[0] = mlx_xpm_file_to_image(mlx, BORDER_N, &c, &c);
	textures->border[1] = mlx_xpm_file_to_image(mlx, BORDER_NE, &c, &c);
	textures->border[2] = mlx_xpm_file_to_image(mlx, BORDER_E, &c, &c);
	textures->border[3] = mlx_xpm_file_to_image(mlx, BORDER_SE, &c, &c);
	textures->border[4] = mlx_xpm_file_to_image(mlx, BORDER_S, &c, &c);
	textures->border[5] = mlx_xpm_file_to_image(mlx, BORDER_SW, &c, &c);
	textures->border[6] = mlx_xpm_file_to_image(mlx, BORDER_W, &c, &c);
	textures->border[7] = mlx_xpm_file_to_image(mlx, BORDER_NW, &c, &c);
}

void	get_map_coords_in_screen(t_window *window, t_map *map)
{
	window->max.x = (SCREEN_WIDTH / PIXEL_PADDING / 2) + (map->width / 2);
	window->max.y = (SCREEN_HEIGHT / PIXEL_PADDING / 2) + (map->height / 2);
	window->min.x = (SCREEN_WIDTH / PIXEL_PADDING / 2) - (map->width / 2);
	window->min.y = (SCREEN_HEIGHT / PIXEL_PADDING / 2) - (map->height / 2);
}

int	get_border_image_index(t_coords coords, t_window window)
{
	if (coords.x == window.min.x)
	{
		if (coords.y == window.min.y)
			return (7);
		else if (coords.y == window.max.y)
			return (5);
		else
			return (6);
	}
	else if (coords.x == window.max.x)
	{
		if (coords.y == window.min.y)
			return (1);
		else if (coords.y == window.max.y)
			return (3);
		else
			return (2);
	}
	else if (coords.y == window.max.y)
		return (4);
	else if (coords.y == window.min.y)
		return (0);
	else
		return (-1);
}

int	is_in_map(t_coords screen, t_coords min, t_coords max)
{
	if ((screen.x >= min.x && screen.x <= max.x) && (screen.y >= min.y
			&& screen.y <= max.y))
		return (1);
	else
		return (0);
}

void	init_screen_array(t_map *map, t_window window)
{
	t_coords	screen_coords;
	t_coords	map_coords;

	// ft_printf("%d  c[%c][%c][%c] d[%d][%d]\n",
	// 			screen_coords.x,
	// 			window.screen_array[screen_coords.y][screen_coords.x
	// 				- 2],
	// 			window.screen_array[screen_coords.y][screen_coords.x
	// 				- 1],
	// 			window.screen_array[screen_coords.y][screen_coords.x],
	// 			window.screen_array[screen_coords.y][screen_coords.x
	// 				- 1],
	// 			window.screen_array[screen_coords.y][screen_coords.x]);
	screen_coords.y = 0;
	map_coords.y = 0;
	ft_printf("%d %d  %d %d\n", map->width % 2, map->height % 2, map->width,
		map->height);
	ft_printf("%d %d\n", SCREEN_HEIGHT / PIXEL_PADDING, SCREEN_WIDTH
		/ PIXEL_PADDING);
	while (screen_coords.y < SCREEN_HEIGHT / PIXEL_PADDING)
	{
		window.screen_array[screen_coords.y] = ft_calloc(sizeof(char),
				(SCREEN_WIDTH / PIXEL_PADDING) + 1);
		map_coords.x = 0;
		screen_coords.x = 0;
		while (screen_coords.x < SCREEN_WIDTH / PIXEL_PADDING)
		{
			if (is_in_map(screen_coords, window.min, window.max))
			{
				window.screen_array[screen_coords.y][screen_coords.x] = map->array[map_coords.y][map_coords.x];
				map_coords.x++;
			}
			else
			{
				if (map->width % 2 == 0)
					window.screen_array[screen_coords.y][screen_coords.x
						- 1] = 'W';
				window.screen_array[screen_coords.y][screen_coords.x] = 'W';
			}
			screen_coords.x++;
		}
		window.screen_array[screen_coords.y][screen_coords.x] = 0;
		if (map_coords.x)
			map_coords.y++;
		ft_printf("%s	%d %d\n", window.screen_array[screen_coords.y],
				map_coords.x, map_coords.y);
		screen_coords.y++;
	}
}

void	print_screen_array(char **screen_array, t_textures textures,
		t_window window, void *mlx)
{
	t_coords	i;
	int			i_border;

	i.y = 0;
	while (screen_array[i.y])
	{
		i.x = 0;
		while (screen_array[i.y][i.x])
		{
			if (screen_array[i.y][i.x] == 'W')
				mlx_put_image_to_window(mlx, window.ptr, textures.water[rand()
					% 2], i.x * PIXEL_PADDING, i.y * PIXEL_PADDING);
			if (screen_array[i.y][i.x] == '0' || screen_array[i.y][i.x] == 'C')
			{
				mlx_put_image_to_window(mlx, window.ptr, textures.ground[rand()
					% 2], i.x * PIXEL_PADDING, i.y * PIXEL_PADDING);
			}
			if (screen_array[i.y][i.x] == '1')
			{
				i_border = get_border_image_index(i, window);
				if (i_border >= 0)
					mlx_put_image_to_window(mlx, window.ptr,
						textures.border[i_border], i.x * PIXEL_PADDING, i.y
						* PIXEL_PADDING);
				else
					mlx_put_image_to_window(mlx, window.ptr, textures.wall[0],
						i.x * PIXEL_PADDING, i.y * PIXEL_PADDING);
			}
			i.x++;
		}
		i.y++;
	}
}

void	init_window(t_map *map, t_window window, void *mlx, t_textures textures)
{
	window.screen_array = ft_calloc(sizeof(char *), SCREEN_HEIGHT
			/ PIXEL_PADDING + 1);
	get_map_coords_in_screen(&window, map);
	init_screen_array(map, window);
	window.ptr = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"caca dans culotte");
	print_screen_array(window.screen_array, textures, window, mlx);
}

void	start(t_data data)
{
	set_textures(&data.textures, data.mlx);
	init_window(data.map, data.window, data.mlx, data.textures);
	mlx_loop(data.mlx);
}