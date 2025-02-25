/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:13:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/25 18:25:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_failed_window_init(t_data data)
{
	free_array(data.map->array);
	if (data.window.screen)
		free_array(data.window.screen);
	free_collectibles(data.game.collectibles);
	free_ennemies(data.game.ennemies);
	free_images_start(data);
	free_images_end(data);
	free_textures(data.textures);
	free(data.map);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	ft_printf(RED "Error\nFailed calloc window init\n" RESET);
}

void	free_failed_textures_init(t_data data)
{
	free_array(data.map->array);
	free_collectibles(data.map->collectibles);
	free_ennemies(data.map->ennemies);
	free(data.map);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	ft_printf(RED "Error\nFailed calloc on textures\n" RESET);
	return ;
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
	free_array(data.window.screen);
	free_collectibles(data.game.collectibles);
	free_ennemies(data.game.ennemies);
	free_swords(data.game.player.swords);
	free_images_start(data);
	free_images_end(data);
	free_textures(data.textures);
	mlx_destroy_window(data.mlx, data.window.ptr);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
