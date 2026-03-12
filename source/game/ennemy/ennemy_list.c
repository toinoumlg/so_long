/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:04 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 10:45:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "exit_error.h"
#include "so_long.h"

void	destroy_ennemy(t_ennemy **ennemies, t_vector2 coords, t_data *data)
{
	t_ennemy	*previous;
	t_ennemy	*ennemy;

	ennemy = *ennemies;
	if (ennemy->coords.x == coords.x && ennemy->coords.y == coords.y)
	{
		*ennemies = ennemy->next;
		mlx_put_image_to_window(data->mlx, data->window.ptr,
			data->textures.ground[0].ptr, coords.x * PIXEL_PADDING, coords.y
			* PIXEL_PADDING);
		free(ennemy);
		return ;
	}
	while (ennemy != NULL && (ennemy->coords.x != coords.x
			|| ennemy->coords.y != coords.y))
	{
		previous = ennemy;
		ennemy = ennemy->next;
	}
	previous->next = ennemy->next;
	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].ptr, coords.x * PIXEL_PADDING, coords.y
		* PIXEL_PADDING);
	free(ennemy);
}

t_ennemy	*set_new_ennemy(t_data *data)
{
	t_ennemy	*new;

	new = malloc(sizeof(t_ennemy));
	if (!new)
		exit(parsing_error(data, ALLOC_ERROR));
	ft_memset(new, 0, sizeof(t_ennemy));
	return (new);
}

void	append_new_ennemy(t_ennemy **ennemies, t_ennemy *new)
{
	t_ennemy	*tmp;
	t_ennemy	*head;

	tmp = *ennemies;
	if (!tmp)
	{
		*ennemies = new;
		return ;
	}
	head = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*ennemies = head;
}

void	add_ennemy(t_data *data, int x, int y)
{
	t_ennemy	*new;

	new = set_new_ennemy(data);
	new->coords = set_vector2(y, x);
	append_new_ennemy(&data->ennemies, new);
}

void	update_ennemies_coords(t_ennemy *ennemies, t_vector2 coords)
{
	t_ennemy	*tmp;

	tmp = ennemies;
	while (tmp)
	{
		tmp->coords.x += coords.x;
		tmp->coords.y += coords.y;
		tmp = tmp->next;
	}
}
