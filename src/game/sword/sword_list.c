/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:38:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/12 11:46:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destroy_sword_first(t_sword **swords, t_vector2 coords, t_data *data,
		t_sword *sword)
{
	*swords = sword->next_sword;
	if (check_sword_on_collectible(sword, data->game.collectibles))
		return ;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(sword);
}

void	destroy_sword(t_sword **swords, t_vector2 coords, t_data *data)
{
	t_sword	*previous;
	t_sword	*sword;

	sword = *swords;
	if (sword->coords.x == coords.x && sword->coords.y == coords.y)
	{
		destroy_sword_first(swords, coords, data, sword);
		return ;
	}
	while (sword != NULL && (sword->coords.x != coords.x
			|| sword->coords.y != coords.y))
	{
		previous = sword;
		sword = sword->next_sword;
	}
	previous->next_sword = sword->next_sword;
	if (check_sword_on_collectible(sword, data->game.collectibles))
		return ;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(sword);
}

t_sword	*set_new_sword(t_vector2 axe_pos, t_vector2 direction)
{
	t_sword	*new_sword;

	new_sword = ft_calloc(sizeof(t_sword), 1);
	new_sword->coords = set_vector2(axe_pos.y, axe_pos.x);
	new_sword->direction = set_vector2(direction.y, direction.x);
	new_sword->next_coords = set_vector2(0, 0);
	new_sword->index = set_sword_index(direction);
	new_sword->to_destroy = 0;
	new_sword->sword_timer = 0;
	new_sword->is_printed = 0;
	new_sword->next_sword = NULL;
	return (new_sword);
}

void	add_new_sword(t_data *data, t_vector2 axe_pos, t_vector2 direction)
{
	t_sword	*new_sword;
	t_sword	*tmp;

	data->game.actual_sword++;
	new_sword = set_new_sword(axe_pos, direction);
	if (!new_sword)
		return ;
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
	t_ennemy	*ennemy;
	t_vector2	axe_pos;

	axe_pos = set_vector2(data->window.actual.y + direction.y,
			data->window.actual.x + direction.x);
	ennemy = data->game.ennemies;
	data->game.player.attack_cd = 6;
	while (ennemy)
	{
		if (axe_pos.y == ennemy->coords.y && axe_pos.x == ennemy->coords.x)
		{
			ennemy->got_hit = 1;
			ennemy->i_image = 16;
			return ;
		}
		ennemy = ennemy->next_ennemy;
	}
	if (is_blocked(data->window.screen, axe_pos))
		add_new_sword(data, axe_pos, direction);
}
