/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/25 21:23:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	start(t_map *map)
{
	void *mlx;
	void *mlx_win;
	void *mlx_image[5];
	char *image = "sprite_229.xpm";
	int height = 1080;
	int width = (1920);
	ft_printf("%d %d\n", map->width, map->height);
	ft_printf("%d %d\n", height, width);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, (width), (height), "caca dans culotte");
	mlx_image[0] = mlx_new_image(mlx, width, height);
	mlx_image[0] = mlx_xpm_file_to_image(mlx, image, &width, &height);
	int x, y, i, j;
	x = width / PIXEL_PADDING;
	y = height / PIXEL_PADDING;
	while ()
		mlx_put_image_to_window(mlx, mlx_win, mlx_image[0], 100, 100);
	ft_printf("%d\n", mlx_loop(mlx));
	(void)map;
	(void)mlx_win;
}