/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:57:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 15:08:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_texture_sword(t_image *sword, void *mlx)
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
		sword[i].image = mlx_xpm_file_to_image(mlx, sword_files[i],
				&sword[i].wh.x, &sword[i].wh.y);
		sword[i].addr = mlx_get_data_addr(sword[i].image, &sword[i].bpp,
				&sword[i].size_l, &sword[i].endian);
	}
}

void	set_textures_player(t_image *player, t_image *sword, void *mlx)
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
		player[i].image = mlx_xpm_file_to_image(mlx, player_files[i],
				&player[i].wh.x, &player[i].wh.y);
		player[i].addr = mlx_get_data_addr(player[i].image, &player[i].bpp,
				&player[i].size_l, &player[i].endian);
	}
}
