/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 15:06:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_calloc_textures(t_data *data)
{
	data->textures.walls = ft_calloc(sizeof(t_image), 7);
	data->textures.ground = ft_calloc(sizeof(t_image), 2);
	data->textures.water = ft_calloc(sizeof(t_image), 2);
	data->textures.borders = ft_calloc(sizeof(t_image), 8);
	data->textures.player = ft_calloc(sizeof(t_image), 5);
	data->textures.sword = ft_calloc(sizeof(t_image), 4);
	data->textures.coins = ft_calloc(sizeof(t_image), 13);
	data->textures.exit = ft_calloc(sizeof(t_image), 1);
	data->textures.ennemies = ft_calloc(sizeof(t_image), 21);
	data->textures.hud = ft_calloc(sizeof(t_image), 5);
}

void	set_textures(t_data *data)
{
	data->game.collectibles = data->map->collectibles;
	data->game.ennemies = data->map->ennemies;
	set_calloc_textures(data);
	set_textures_hud(data->textures.hud, data->mlx);
	set_textures_border(data->textures.borders, data->mlx);
	set_textures_walls(data->textures.walls, data->mlx);
	set_textures_ennemies(data->textures.ennemies, data->mlx);
	set_textures_exit(data->textures.exit, data->mlx);
	set_textures_water(data->textures.water, data->mlx);
	set_textures_ground(data->textures.ground, data->mlx);
	set_textures_player(data->textures.player, data->textures.sword, data->mlx);
	set_textures_coins(data->textures.coins, data->mlx);
}
