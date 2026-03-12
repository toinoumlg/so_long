/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_others.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:06:11 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:52:03 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "textures_path.h"

void	set_textures_border(t_img *borders, void *mlx)
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
		borders[i].ptr = mlx_xpm_file_to_image(mlx, borders_files[i],
				&borders[i].width, &borders[i].height);
		borders[i].addr = (t_pxl *)mlx_get_data_addr(borders[i].ptr,
				&borders[i].bpp, &borders[i].lenght, &borders[i].endian);
		i++;
	}
}

void	set_textures_exit(t_img *exit, void *mlx)
{
	char	*exit_files[1];
	int		i;

	exit_files[0] = EXIT1;
	i = -1;
	while (i++ < 0)
	{
		exit[i].ptr = mlx_xpm_file_to_image(mlx, exit_files[i], &exit[i].width,
				&exit[i].height);
		exit[i].addr = (t_pxl *)mlx_get_data_addr(exit[i].ptr, &exit[i].bpp,
				&exit[i].lenght, &exit[i].endian);
	}
}

void	set_textures_water(t_img *water, void *mlx)
{
	int		i;
	char	*water_files[2];

	water_files[0] = WATER1;
	water_files[1] = WATER2;
	i = -1;
	while (i++ < 1)
	{
		water[i].ptr = mlx_xpm_file_to_image(mlx, water_files[i],
				&water[i].width, &water[i].height);
		water[i].addr = (t_pxl *)mlx_get_data_addr(water[i].ptr, &water[i].bpp,
				&water[i].lenght, &water[i].endian);
	}
}

void	set_textures_ground(t_img *ground, void *mlx)
{
	int		i;
	char	*ground_files[2];

	ground_files[0] = GROUND1;
	ground_files[1] = GROUND2;
	i = -1;
	while (i++ < 1)
	{
		ground[i].ptr = mlx_xpm_file_to_image(mlx, ground_files[i],
				&ground[i].width, &ground[i].height);
		ground[i].addr = (t_pxl *)mlx_get_data_addr(ground[i].ptr, &ground[i].bpp,
				&ground[i].lenght, &ground[i].endian);
	}
}

void	set_textures_hud(t_img *hud, void *mlx)
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
		hud[i].ptr = mlx_xpm_file_to_image(mlx, hud_files[i], &hud[i].width,
				&hud[i].height);
		hud[i].addr = (t_pxl *)mlx_get_data_addr(hud[i].ptr, &hud[i].bpp,
				&hud[i].lenght, &hud[i].endian);
	}
}
