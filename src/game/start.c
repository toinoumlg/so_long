/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/28 16:31:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	start(t_data data)
{
	set_textures(&data.textures, data.mlx);
	init_window(data.map, &data.window, data.mlx, data.textures);
	mlx_loop(data.mlx);
	free_game(data);
}