/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 16:16:09 by amalangu         ###   ########.fr       */
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

void	free_swords(t_sword *swords)
{
	t_sword	*tmp;

	tmp = swords;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = tmp->next_sword;
		free(swords);
		swords = tmp;
	}
}

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
		mlx_destroy_image(data.mlx, data.textures.player_axe[i].image);
}

void	free_images_end(t_data data)
{
	int	i;

	i = -1;
	while (i++ < 12)
		mlx_destroy_image(data.mlx, data.textures.coins_r[i].image);
	i = -1;
	while (i++ < 20)
		mlx_destroy_image(data.mlx, data.textures.ennemies[i].image);
	i = -1;
	while (i++ < 2)
		mlx_destroy_image(data.mlx, data.textures.hud[i].image);
	i = -1;
	while (i++ < 0)
		mlx_destroy_image(data.mlx, data.textures.heart[i].image);
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
	free(textures.player_axe);
	free(textures.hud);
	free(textures.heart);
	free(textures.exit);
	free(textures.coins_r);
}

void	free_game(t_data data)
{
	int	i;

	i = 0;
	while (data.window.screen[i])
		free(data.window.screen[i++]);
	free(data.window.screen);
	free_ennemies(data.game.ennemies);
	free_swords(data.game.player.swords);
	free_images_start(data);
	free_images_end(data);
	free_textures(data.textures);
	mlx_destroy_window(data.mlx, data.window.ptr);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->array[i])
		free(map->array[i++]);
	if (map->array)
		free(map->array);
	free(map);
}
