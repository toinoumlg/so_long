/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/29 19:36:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_textures_border(t_image *borders, void *mlx)
{
	char	*borders_files[] = {BORDER_N, BORDER_NE, BORDER_E, BORDER_SE,
			BORDER_S, BORDER_SW, BORDER_W, BORDER_NW};
	int		i;

	i = 0;
	while (i < 8)
	{
		borders[i].image = mlx_xpm_file_to_image(mlx, borders_files[i],
				&borders[i].wh.x, &borders[i].wh.y);
		borders[i].addr = mlx_get_data_addr(borders[i].image, &borders[i].bpp,
				&borders[i].size_l, &borders[i].endian);
		i++;
	}
}

void	set_textures_wgw(t_textures *textures, void *mlx)
{
	int	i;

	textures->ground[0].image = mlx_xpm_file_to_image(mlx, GROUND1,
			&textures->ground[0].wh.x, &textures->ground[0].wh.y);
	textures->ground[1].image = mlx_xpm_file_to_image(mlx, GROUND2,
			&textures->ground[1].wh.x, &textures->ground[1].wh.y);
	textures->water[0].image = mlx_xpm_file_to_image(mlx, WATER1,
			&textures->water[0].wh.x, &textures->water[0].wh.y);
	textures->water[1].image = mlx_xpm_file_to_image(mlx, WATER2,
			&textures->water[1].wh.x, &textures->water[1].wh.y);
	textures->exit[0].image = mlx_xpm_file_to_image(mlx, EXIT1,
			&textures->exit->wh.x, &textures->exit->wh.y);
	textures->exit[0].addr = mlx_get_data_addr(textures->exit[0].image,
			&textures->exit[0].bpp, &textures->exit[0].size_l,
			&textures->exit[0].endian);
	i = -1;
	while (i++ < 1)
		textures->water[i].addr = mlx_get_data_addr(textures->water[i].image,
				&textures->water[i].bpp, &textures->water[i].size_l,
				&textures->water[i].endian);
	i = -1;
	while (i++ < 1)
		textures->ground[i].addr = mlx_get_data_addr(textures->ground[i].image,
				&textures->ground[i].bpp, &textures->ground[i].size_l,
				&textures->ground[i].endian);
}

void	set_textures_walls(t_image *walls, void *mlx)
{
	int		i;
	char	*walls_files[] = {WALL1, WALL2, WALL3, WALL4, WALL5, WALL6, WALL7};

	i = 0;
	while (i < 7)
	{
		walls[i].image = mlx_xpm_file_to_image(mlx, walls_files[i],
				&walls[i].wh.x, &walls[i].wh.y);
		walls[i].addr = mlx_get_data_addr(walls[i].image, &walls[i].bpp,
				&walls[i].size_l, &walls[i].endian);
		i++;
	}
}

void	set_textures_player(t_image *player, void *mlx)
{
	player[0].image = mlx_xpm_file_to_image(mlx, PLAYER_IDLE1, &player[0].wh.x,
			&player[0].wh.y);
	player[0].addr = mlx_get_data_addr(player[0].image, &player[0].bpp,
			&player[0].size_l, &player[0].endian);
}

void	set_textures_coins(t_image *coins, void *mlx)
{
	char	*coin_files[] = {COIN_R1, COIN_R2, COIN_R3, COIN_R4, COIN_R5,
			COIN_R6, COIN_R7, COIN_R8, COIN_R9, COIN_R10, COIN_R11, COIN_R12,
			COIN_R13};
	int		i;

	i = 0;
	while (i < 13)
	{
		coins[i].image = mlx_xpm_file_to_image(mlx, coin_files[i],
				&coins[i].wh.x, &coins[i].wh.y);
		coins[i].addr = mlx_get_data_addr(coins[i].image, &coins[i].bpp,
				&coins[i].size_l, &coins[i].endian);
		i++;
	}
}

void	set_textures(t_data *data)
{
	data->game.collectibles = data->map->collectibles;
	data->textures.walls = ft_calloc(sizeof(t_image), 7);
	data->textures.ground = ft_calloc(sizeof(t_image), 2);
	data->textures.water = ft_calloc(sizeof(t_image), 2);
	data->textures.borders = ft_calloc(sizeof(t_image), 8);
	data->textures.player = ft_calloc(sizeof(t_image), 1);
	data->textures.coins_r = ft_calloc(sizeof(t_image), 13);
	data->textures.exit = ft_calloc(sizeof(t_image), 1);
	set_textures_border(data->textures.borders, data->mlx);
	set_textures_walls(data->textures.walls, data->mlx);
	set_textures_wgw(&data->textures, data->mlx);
	set_textures_player(data->textures.player, data->mlx);
	set_textures_coins(data->textures.coins_r, data->mlx);
}
