/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_wallls_coins.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:56:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/01 09:56:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
