/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/31 15:07:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_textures_border(t_image *borders, void *mlx)
{
	char	*borders_files[8];
	int		i;

	borders_files[0] = BORDER_N;
	borders_files[1] = BORDER_NE;
	borders_files[2] = BORDER_E;
	borders_files[3] = BORDER_SE;
	borders_files[4] = BORDER_S;
	borders_files[5] = BORDER_SW;
	borders_files[6] = BORDER_W;
	borders_files[7] = BORDER_NW;
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
	char	*walls_files[7];

	walls_files[0] = WALL1;
	walls_files[1] = WALL2;
	walls_files[2] = WALL3;
	walls_files[3] = WALL4;
	walls_files[4] = WALL5;
	walls_files[5] = WALL6;
	walls_files[6] = WALL7;
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
	char	*coin_files[13];
	int		i;

	coin_files[0] = COIN_R1;
	coin_files[1] = COIN_R2;
	coin_files[2] = COIN_R3;
	coin_files[3] = COIN_R4;
	coin_files[4] = COIN_R5;
	coin_files[5] = COIN_R6;
	coin_files[6] = COIN_R7;
	coin_files[7] = COIN_R8;
	coin_files[8] = COIN_R9;
	coin_files[9] = COIN_R10;
	coin_files[10] = COIN_R11;
	coin_files[11] = COIN_R12;
	coin_files[12] = COIN_R13;
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
