/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/08 10:33:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_collectibles(t_collectible *collectibles)
{
	t_collectible	*tmp;

	tmp = collectibles;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = collectibles->next_collectible;
		free(collectibles);
		collectibles = tmp;
	}
}

void	free_ennemies(t_ennemy *ennemies)
{
	t_ennemy	*tmp;

	tmp = ennemies;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = ennemies->next_ennemy;
		free(ennemies);
		ennemies = tmp;
	}
}

void	free_images(t_data data)
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
		mlx_destroy_image(data.mlx, data.textures.player_axe[i].image);
	i = -1;
	while (i++ < 12)
		mlx_destroy_image(data.mlx, data.textures.coins_r[i].image);
	i = -1;
	while (i++ < 20)
		mlx_destroy_image(data.mlx, data.textures.ennemies[i].image);
	mlx_destroy_image(data.mlx, data.textures.exit[0].image);
}

void	free_game(t_data data)
{
	int	i;

	i = 0;
	while (data.window.screen[i])
	{
		free(data.window.screen[i]);
		i++;
	}
	free_ennemies(data.game.ennemies);
	free_images(data);
	free(data.window.screen);
	free(data.textures.ennemies);
	free(data.textures.ground);
	free(data.textures.walls);
	free(data.textures.water);
	free(data.textures.borders);
	free(data.textures.player);
	free(data.textures.player_axe);
	free(data.textures.exit);
	free(data.textures.coins_r);
	mlx_destroy_window(data.mlx, data.window.ptr);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->array[i])
	{
		free(map->array[i]);
		i++;
	}
	if (map->array)
		free(map->array);
	free(map);
}
