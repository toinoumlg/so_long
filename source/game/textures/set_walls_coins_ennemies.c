/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_walls_coins_ennemies.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:56:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:49:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_textures_ennemy_file(char **ennemy_file)
{
	ennemy_file[0] = ENNEMY1;
	ennemy_file[1] = ENNEMY2;
	ennemy_file[2] = ENNEMY3;
	ennemy_file[3] = ENNEMY4;
	ennemy_file[4] = ENNEMY5;
	ennemy_file[5] = ENNEMY6;
	ennemy_file[6] = ENNEMY7;
	ennemy_file[7] = ENNEMY8;
	ennemy_file[8] = ENNEMY9;
	ennemy_file[9] = ENNEMY10;
	ennemy_file[10] = ENNEMY11;
	ennemy_file[11] = ENNEMY12;
	ennemy_file[12] = ENNEMY13;
	ennemy_file[13] = ENNEMY14;
	ennemy_file[14] = ENNEMY15;
	ennemy_file[15] = ENNEMY1;
	ennemy_file[16] = ENNEMY17;
	ennemy_file[17] = ENNEMY18;
	ennemy_file[18] = ENNEMY19;
	ennemy_file[19] = ENNEMY20;
	ennemy_file[20] = ENNEMY21;
}

void	set_textures_ennemies(t_image *ennemies, void *mlx)
{
	char	*ennemy_file[21];
	int		i;

	set_textures_ennemy_file(ennemy_file);
	i = 0;
	while (i < 21)
	{
		ennemies[i].image = mlx_xpm_file_to_image(mlx, ennemy_file[i],
				&ennemies[i].wh.x, &ennemies[i].wh.y);
		ennemies[i].addr = mlx_get_data_addr(ennemies[i].image,
				&ennemies[i].bpp, &ennemies[i].size_l, &ennemies[i].endian);
		i++;
	}
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
