/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 20:35:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_game(t_data data)
{
	int	i;

	i = -1;
	while (i++ < 7)
		mlx_destroy_image(data.mlx, data.textures.border[i].image);
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
	while (i++ < 0)
		mlx_destroy_image(data.mlx, data.textures.player[i].image);
	i = -1;
	while (i++ < 0)
		mlx_destroy_image(data.mlx, data.textures.coins_r[i].image);
	i = 0;
	while (data.window.screen[i])
	{
		free(data.window.screen[i]);
		i++;
	}
	free(data.window.screen);
	free(data.textures.ground);
	free(data.textures.walls);
	free(data.textures.water);
	free(data.textures.border);
	free(data.textures.player);
	free(data.textures.coins_r);
	mlx_destroy_window(data.mlx, data.window.ptr);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}

void	free_collectibles(t_collectibles *collectibles)
{
	t_collectibles	*tmp;

	while (collectibles)
	{
		tmp = collectibles->next_collectible;
		free(collectibles);
		collectibles = tmp;
	}
}

void	free_memory_map(t_map *map)
{
	int	i;

	if (map->collectibles)
		free_collectibles(map->collectibles);
	i = 0;
	while (map->array[i])
	{
		free(map->array[i]);
		i++;
	}
	if (map->array)
		free(map->array);
	free(map->possible_directions);
	free(map);
}
