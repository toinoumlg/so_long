/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 18:55:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_textures_border(t_image *border, void *mlx, int *c)
{
	border[0].image = mlx_xpm_file_to_image(mlx, BORDER_N, c, c);
	border[1].image = mlx_xpm_file_to_image(mlx, BORDER_NE, c, c);
	border[2].image = mlx_xpm_file_to_image(mlx, BORDER_E, c, c);
	border[3].image = mlx_xpm_file_to_image(mlx, BORDER_SE, c, c);
	border[4].image = mlx_xpm_file_to_image(mlx, BORDER_S, c, c);
	border[5].image = mlx_xpm_file_to_image(mlx, BORDER_SW, c, c);
	border[6].image = mlx_xpm_file_to_image(mlx, BORDER_W, c, c);
	border[7].image = mlx_xpm_file_to_image(mlx, BORDER_NW, c, c);
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
	int	i;

	walls[0].image = mlx_xpm_file_to_image(mlx, WALL1, &walls[0].wh.x,
			&walls[0].wh.y);
	walls[1].image = mlx_xpm_file_to_image(mlx, WALL2, &walls[1].wh.x,
			&walls[1].wh.y);
	walls[2].image = mlx_xpm_file_to_image(mlx, WALL3, &walls[2].wh.x,
			&walls[2].wh.y);
	walls[3].image = mlx_xpm_file_to_image(mlx, WALL4, &walls[3].wh.x,
			&walls[3].wh.y);
	walls[4].image = mlx_xpm_file_to_image(mlx, WALL5, &walls[4].wh.x,
			&walls[4].wh.y);
	walls[5].image = mlx_xpm_file_to_image(mlx, WALL6, &walls[5].wh.x,
			&walls[5].wh.y);
	walls[6].image = mlx_xpm_file_to_image(mlx, WALL7, &walls[6].wh.x,
			&walls[6].wh.y);
	i = -1;
	while (i++ < 6)
		walls[i].addr = mlx_get_data_addr(walls[i].image, &walls[i].bpp,
				&walls[i].size_l, &walls[i].endian);
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
	coins[0].image = mlx_xpm_file_to_image(mlx, COIN_R1, &coins[0].wh.x,
			&coins[0].wh.y);
	coins[0].addr = mlx_get_data_addr(coins[0].image, &coins[0].bpp,
			&coins[0].size_l, &coins[0].endian);
}

void	set_textures(t_textures *textures, void *mlx)
{
	int	c;

	textures->walls = ft_calloc(sizeof(t_image), 7);
	textures->ground = ft_calloc(sizeof(t_image), 2);
	textures->water = ft_calloc(sizeof(t_image), 2);
	textures->border = ft_calloc(sizeof(t_image), 8);
	textures->player = ft_calloc(sizeof(t_image), 1);
	textures->coins_r = ft_calloc(sizeof(t_image), 1);
	set_textures_border(textures->border, mlx, &c);
	set_textures_walls(textures->walls, mlx);
	set_textures_wgw(textures, mlx);
	set_textures_player(textures->player, mlx);
	set_textures_coins(textures->coins_r, mlx);
}
