/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:58:57 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:25:40 by amalangu         ###   ########.fr       */
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
