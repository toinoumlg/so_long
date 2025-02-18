/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_others.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:06:11 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 15:06:19 by amalangu         ###   ########.fr       */
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

void	set_textures_exit(t_image *exit, void *mlx)
{
	char	*exit_files[1];
	int		i;

	exit_files[0] = EXIT1;
	i = -1;
	while (i++ < 0)
	{
		exit[i].image = mlx_xpm_file_to_image(mlx, exit_files[i], &exit[i].wh.x,
				&exit[i].wh.y);
		exit[i].addr = mlx_get_data_addr(exit[i].image, &exit[i].bpp,
				&exit[i].size_l, &exit[i].endian);
	}
}

void	set_textures_water(t_image *water, void *mlx)
{
	int		i;
	char	*water_files[2];

	water_files[0] = WATER1;
	water_files[1] = WATER2;
	i = -1;
	while (i++ < 1)
	{
		water[i].image = mlx_xpm_file_to_image(mlx, water_files[i],
				&water[i].wh.x, &water[i].wh.y);
		water[i].addr = mlx_get_data_addr(water[i].image, &water[i].bpp,
				&water[i].size_l, &water[i].endian);
	}
}

void	set_textures_ground(t_image *ground, void *mlx)
{
	int		i;
	char	*ground_files[2];

	ground_files[0] = GROUND1;
	ground_files[1] = GROUND2;
	i = -1;
	while (i++ < 1)
	{
		ground[i].image = mlx_xpm_file_to_image(mlx, ground_files[i],
				&ground[i].wh.x, &ground[i].wh.y);
		ground[i].addr = mlx_get_data_addr(ground[i].image, &ground[i].bpp,
				&ground[i].size_l, &ground[i].endian);
	}
}

void	set_textures_hud(t_image *hud, void *mlx)
{
	char	*hud_files[5];
	int		i;

	hud_files[0] = HUD1;
	hud_files[1] = HUD2;
	hud_files[2] = HUD3;
	hud_files[3] = HUD4;
	hud_files[4] = HUD5;
	i = -1;
	while (i++ < 4)
	{
		hud[i].image = mlx_xpm_file_to_image(mlx, hud_files[i], &hud[i].wh.x,
				&hud[i].wh.y);
		hud[i].addr = mlx_get_data_addr(hud[i].image, &hud[i].bpp,
				&hud[i].size_l, &hud[i].endian);
	}
}
