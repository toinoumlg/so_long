/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:57:39 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 09:52:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "textures_path.h"

void	set_texture_sword(t_img *sword, void *mlx)
{
	char	*sword_files[4];
	int		i;

	sword_files[0] = SWORD1;
	sword_files[1] = SWORD2;
	sword_files[2] = SWORD3;
	sword_files[3] = SWORD4;
	i = -1;
	while (i++ < 3)
	{
		sword[i].ptr = mlx_xpm_file_to_image(mlx, sword_files[i],
				&sword[i].width, &sword[i].height);
		sword[i].addr = (t_pxl *)mlx_get_data_addr(sword[i].ptr, &sword[i].bpp,
				&sword[i].lenght, &sword[i].endian);
	}
}

void	set_textures_player(t_img *player, t_img *sword, void *mlx)
{
	char	*player_files[5];
	int		i;

	player_files[0] = PLAYER_IDLE1;
	player_files[1] = PLAYER_IDLE2;
	player_files[2] = PLAYER_IDLE3;
	player_files[3] = PLAYER_IDLE4;
	player_files[4] = PLAYER_IDLE5;
	set_texture_sword(sword, mlx);
	i = -1;
	while (i++ < 4)
	{
		player[i].ptr = mlx_xpm_file_to_image(mlx, player_files[i],
				&player[i].width, &player[i].height);
		player[i].addr = (t_pxl *)mlx_get_data_addr(player[i].ptr, &player[i].bpp,
				&player[i].lenght, &player[i].endian);
	}
}
