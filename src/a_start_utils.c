/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_start_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:18:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/22 18:48:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_list(t_a_star_list *list, float f, int x, int y)
{
	list->coords.x = x;
	list->coords.x = y;
	list->f = f;
	list->next = NULL;
}

void	init_list(t_a_star_list *list, float f, int x, int y)
{
	t_a_star_list	*tmp;
	t_a_star_list	*new_list;

	new_list = ft_calloc(sizeof(t_a_star_list), 1);
	new_list->coords.x = x;
	new_list->coords.x = y;
	new_list->f = f;
	new_list->next = NULL;
	if (!list)
	{
		list = new_list;
		return ;
	}
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_list;
	return ;
}
