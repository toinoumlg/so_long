/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/11 16:50:47 by amalangu         ###   ########.fr       */
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

void	set_textures_water_ground(t_textures *textures, void *mlx)
{
	int		i;
	char	*ground_files[2];
	char	*water_files[2];

	ground_files[0] = GROUND1;
	ground_files[1] = GROUND2;
	water_files[0] = WATER1;
	water_files[1] = WATER2;
	i = -1;
	while (i++ < 1)
	{
		textures->ground[i].image = mlx_xpm_file_to_image(mlx, ground_files[i],
				&textures->ground[i].wh.x, &textures->ground[i].wh.y);
		textures->ground[i].addr = mlx_get_data_addr(textures->ground[i].image,
				&textures->ground[i].bpp, &textures->ground[i].size_l,
				&textures->ground[i].endian);
	}
	i = -1;
	while (i++ < 1)
	{
		textures->water[i].image = mlx_xpm_file_to_image(mlx, water_files[i],
				&textures->water[i].wh.x, &textures->water[i].wh.y);
		textures->water[i].addr = mlx_get_data_addr(textures->water[i].image,
				&textures->water[i].bpp, &textures->water[i].size_l,
				&textures->water[i].endian);
	}
}

void	set_textures_player(t_image *player, t_image *player_axe, void *mlx)
{
	char	*player_files[5];
	char	*player_axe_files[4];
	int		i;

	player_files[0] = PLAYER_IDLE1;
	player_files[1] = PLAYER_IDLE2;
	player_files[2] = PLAYER_IDLE3;
	player_files[3] = PLAYER_IDLE4;
	player_files[4] = PLAYER_IDLE5;
	player_axe_files[0] = PLAYER_AXE1;
	player_axe_files[1] = PLAYER_AXE2;
	player_axe_files[2] = PLAYER_AXE3;
	player_axe_files[3] = PLAYER_AXE4;
	i = -1;
	while (i++ < 4)
	{
		player[i].image = mlx_xpm_file_to_image(mlx, player_files[i],
				&player[i].wh.x, &player[i].wh.y);
		player[i].addr = mlx_get_data_addr(player[i].image, &player[i].bpp,
				&player[i].size_l, &player[i].endian);
	}
	i = -1;
	while (i++ < 3)
	{
		player_axe[i].image = mlx_xpm_file_to_image(mlx, player_axe_files[i],
				&player_axe[i].wh.x, &player_axe[i].wh.y);
		player_axe[i].addr = mlx_get_data_addr(player_axe[i].image,
				&player_axe[i].bpp, &player_axe[i].size_l,
				&player_axe[i].endian);
	}
}

void	set_textures_hud(t_image *hud, void *mlx)
{
	char	*hud_files[3];
	int		i;

	hud_files[0] = HUD1;
	hud_files[1] = HUD2;
	hud_files[2] = HUD3;
	i = -1;
	while (i++ < 2)
	{
		hud[i].image = mlx_xpm_file_to_image(mlx, hud_files[i], &hud[i].wh.x,
				&hud[i].wh.y);
		hud[i].addr = mlx_get_data_addr(hud[i].image, &hud[i].bpp,
				&hud[i].size_l, &hud[i].endian);
	}
}

void	set_textures_heart(t_image *heart, void *mlx)
{
	char	*heart_files[1];
	int		i;

	heart_files[0] = HEART1;
	i = -1;
	while (i++ < 0)
	{
		heart[i].image = mlx_xpm_file_to_image(mlx, heart_files[i],
				&heart[i].wh.x, &heart[i].wh.y);
		heart[i].addr = mlx_get_data_addr(heart[i].image, &heart[i].bpp,
				&heart[i].size_l, &heart[i].endian);
	}
}

void	set_calloc_textures(t_data *data)
{
	data->textures.walls = ft_calloc(sizeof(t_image), 7);
	data->textures.ground = ft_calloc(sizeof(t_image), 2);
	data->textures.water = ft_calloc(sizeof(t_image), 2);
	data->textures.borders = ft_calloc(sizeof(t_image), 8);
	data->textures.player = ft_calloc(sizeof(t_image), 5);
	data->textures.player_axe = ft_calloc(sizeof(t_image), 4);
	data->textures.coins_r = ft_calloc(sizeof(t_image), 13);
	data->textures.exit = ft_calloc(sizeof(t_image), 1);
	data->textures.ennemies = ft_calloc(sizeof(t_image), 21);
	data->textures.hud = ft_calloc(sizeof(t_image), 3);
	data->textures.heart = ft_calloc(sizeof(t_image), 1);
}

void	set_textures(t_data *data)
{
	data->game.collectibles = data->map->collectibles;
	data->game.ennemies = data->map->ennemies;
	set_calloc_textures(data);
	set_textures_hud(data->textures.hud, data->mlx);
	set_textures_heart(data->textures.heart, data->mlx);
	set_textures_border(data->textures.borders, data->mlx);
	set_textures_walls(data->textures.walls, data->mlx);
	set_textures_ennemies(data->textures.ennemies, data->mlx);
	set_textures_water_ground(&data->textures, data->mlx);
	set_textures_player(data->textures.player, data->textures.player_axe,
		data->mlx);
	set_textures_coins(data->textures.coins_r, data->mlx);
}
