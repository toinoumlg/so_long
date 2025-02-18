/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:25:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 14:53:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_images_start(t_data data)
{
	int	i;

	i = -1;
	while (i++ < 7)
		mlx_destroy_image(data.mlx, data.textures.borders[i].image);
	i = -1;
	while (i++ < 6)
		mlx_destroy_image(data.mlx, data.textures.walls[i].image);
	i = -1;
	while (i++ < 1)
		mlx_destroy_image(data.mlx, data.textures.water[i].image);
	i = -1;
	while (i++ < 1)
		mlx_destroy_image(data.mlx, data.textures.ground[i].image);
	i = -1;
	while (i++ < 4)
		mlx_destroy_image(data.mlx, data.textures.player[i].image);
	i = -1;
	while (i++ < 3)
		mlx_destroy_image(data.mlx, data.textures.sword[i].image);
}

void	free_images_end(t_data data)
{
	int	i;

	i = -1;
	while (i++ < 12)
		mlx_destroy_image(data.mlx, data.textures.coins[i].image);
	i = -1;
	while (i++ < 20)
		mlx_destroy_image(data.mlx, data.textures.ennemies[i].image);
	i = -1;
	while (i++ < 4)
		mlx_destroy_image(data.mlx, data.textures.hud[i].image);
	mlx_destroy_image(data.mlx, data.textures.exit[0].image);
}

void	free_textures(t_textures textures)
{
	free(textures.ennemies);
	free(textures.ground);
	free(textures.walls);
	free(textures.water);
	free(textures.borders);
	free(textures.player);
	free(textures.sword);
	free(textures.hud);
	free(textures.exit);
	free(textures.coins);
}
