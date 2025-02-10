/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:55:10 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/10 22:35:25 by amalangu         ###   ########.fr       */
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
	sword->is_printed = 1;
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

t_vector2	sword_next_pos(t_sword *sword)
{
	t_vector2	next_pos;

	next_pos.y = sword->coords.y + sword->direction.y;
	next_pos.x = sword->coords.x + sword->direction.x;
	return (next_pos);
}

void	update_swords(t_data *data)
{
	t_sword		*tmp;
	t_sword		*next;
	t_ennemy	*ennemy;
	t_ennemy	*ennemy_next;

	ennemy = data->game.ennemies;
	tmp = data->game.player.swords;
	while (tmp)
	{
		next = tmp->next_sword;
		tmp->next_coords = sword_next_pos(tmp);
		while (ennemy)
		{
			ennemy_next = ennemy->next_ennemy;
			if (tmp->next_coords.y == ennemy->coords.y
				&& tmp->next_coords.x == ennemy->coords.x)
			{
				ennemy->health = 0;
				ennemy->i_image = 14;
				destroy_sword(&data->game.player.swords, tmp->coords, data);
				data->game.actual_axes--;
			}
			ennemy = ennemy_next;
		}
		tmp = next;
	}
	tmp = data->game.player.swords;
	while (tmp)
	{
		next = tmp->next_sword;
		if (!is_blocked(data->window.screen, tmp->next_coords))
		{
			destroy_sword(&data->game.player.swords, tmp->coords, data);
			data->game.actual_axes--;
		}
		tmp = next;
	}
}

void	add_new_sword(t_data *data, t_vector2 axe_pos, t_vector2 direction)
{
	t_sword	*new_sword;
	t_sword	*tmp;

	data->game.actual_axes++;
	new_sword = ft_calloc(sizeof(t_sword), 1);
	if (!new_sword)
		return ;
	new_sword->coords = set_vector2(axe_pos.y, axe_pos.x);
	new_sword->direction = set_vector2(direction.y, direction.x);
	new_sword->next_coords = set_vector2(0, 0);
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