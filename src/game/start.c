/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 00:48:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_game(t_data data)
{
	int	i;

	i = 0;
	while (i < data.textures.i_border)
		mlx_destroy_image(data.mlx, data.textures.border[i++].image);
	i = 0;
	while (i < data.textures.i_walls)
		mlx_destroy_image(data.mlx, data.textures.walls[i++].image);
	i = 0;
	while (i < data.textures.i_water)
		mlx_destroy_image(data.mlx, data.textures.water[i++].image);
	i = 0;
	while (i < data.textures.i_ground)
		mlx_destroy_image(data.mlx, data.textures.ground[i++].image);
	free(data.textures.border);
	free(data.textures.walls);
	free(data.textures.water);
	free(data.textures.ground);
}

void	start(t_data data)
{
	set_textures(&data.textures, data.mlx);
	init_window(data.map, data.window, data.mlx, data.textures);
	mlx_loop(data.mlx);
	free_game(data);
}