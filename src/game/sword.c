/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:55:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/09 17:21:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_sword(t_data *data, t_sword *sword)
{
	t_image	combined;

	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.player_axe[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		sword->coords.x * PIXEL_PADDING, sword->coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
}

void	destroy_sword(t_sword **swords, t_vector2 coords, t_data *data)
{
	t_sword	*previous;
	t_sword	*tmp;

	tmp = *swords;
	if (tmp->coords.x == coords.x && tmp->coords.y == coords.y)
	{
		*swords = tmp->next_sword;
		mlx_put_image_to_window(data->mlx, data->window.ptr,
			data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
			* PIXEL_PADDING);
		free(tmp);
		return ;
	}
	while (tmp != NULL && (tmp->coords.x != coords.x
			|| tmp->coords.y != coords.y))
	{
		previous = tmp;
		tmp = tmp->next_sword;
	}
	previous->next_sword = tmp->next_sword;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(tmp);
}

void	sword_next_pos(t_data *data, t_sword *sword)
{
	t_vector2	next_pos;
	t_ennemy	*tmp;

	next_pos.y = sword->coords.y + sword->direction.y;
	next_pos.x = sword->coords.x + sword->direction.x;
	tmp = data->game.ennemies;
	while (tmp)
	{
		if (next_pos.y == tmp->coords.y && next_pos.x == tmp->coords.x)
		{
			tmp->health = 0;
			tmp->i_image = 14;
			destroy_sword(&data->game.player.swords, sword->coords, data);
			data->game.actual_axes--;
			return ;
		}
		tmp = tmp->next_ennemy;
	}
	if (!is_blocked(data->window.screen, next_pos))
	{
		destroy_sword(&data->game.player.swords, sword->coords, data);
		data->game.actual_axes--;
		return ;
	}
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, sword->coords.x * PIXEL_PADDING,
		sword->coords.y * PIXEL_PADDING);
	sword->coords.y = next_pos.y;
	sword->coords.x = next_pos.x;
}

void	update_swords(t_data *data)
{
	t_sword	*tmp;
	t_sword	*next;

	tmp = data->game.player.swords;
	if (data->frames % 2 == 0)
	{
		while (tmp)
		{
			next = tmp->next_sword;
			if (data->frames % 6 == 0)
			{
				sword_next_pos(data, tmp);
			}
			// print_sword(data, tmp);
			tmp->index++;
			if (tmp->index > 3)
				tmp->index = 0;
			tmp = next;
		}
	}
}

void	add_new_sword(t_data *data, t_vector2 axe_pos, t_vector2 direction)
{
	t_sword	*new_sword;
	t_sword	*tmp;

	new_sword = ft_calloc(sizeof(t_sword), 1);
	if (!new_sword)
		return ;
	new_sword->coords = set_vector2(axe_pos.y, axe_pos.x);
	new_sword->direction = set_vector2(direction.y, direction.x);
	new_sword->is_printed = 0;
	if (direction.y == 1)
		new_sword->index = 1;
	if (direction.y == -1)
		new_sword->index = 3;
	if (direction.x == 1)
		new_sword->index = 0;
	if (direction.x == -1)
		new_sword->index = 2;
	new_sword->next_sword = NULL;
	if (!data->game.player.swords)
	{
		data->game.player.swords = new_sword;
		return ;
	}
	tmp = data->game.player.swords;
	while (tmp->next_sword)
		tmp = tmp->next_sword;
	tmp->next_sword = new_sword;
	return ;
}

void	spawn_sword(t_data *data, t_vector2 direction)
{
	t_vector2 axe_pos;

	axe_pos.y = data->window.actual.y + direction.y;
	axe_pos.x = data->window.actual.x + direction.x;
	if (is_blocked(data->window.screen, axe_pos))
		add_new_sword(data, axe_pos, direction);
}