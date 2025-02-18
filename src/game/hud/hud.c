/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:59:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/18 17:01:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_hud_move(t_data *data)
{
	char	*str;
	char	*itoa;

	itoa = ft_itoa(data->game.player.moves);
	str = ft_strjoin("Player move: ", itoa);
	print_hud_empty(data, 1);
	print_hud_empty(data, 2);
	print_hud_empty(data, 3);
	print_hud_empty(data, 4);
	mlx_string_put(data->mlx, data->window.ptr, 42, 20, 0xfffff0, str);
	free(itoa);
	free(str);
}

void	print_hud_time(t_data *data)
{
	char	*str;

	str = string_hud(data);
	print_hud_left_corner(data, 0);
	mlx_string_put(data->mlx, data->window.ptr, 10, 20, 0xfffff0, str);
	free(str);
}

void	print_hud(t_data *data)
{
	int	i;

	i = -1;
	while (i++ < data->window.max.x + 1)
	{
		if (i == 0)
			print_hud_left_corner(data, i);
		else if (i == data->window.max.x + 1)
			print_hud_right_corner(data, i);
		else
			print_hud_empty(data, i);
	}
}
