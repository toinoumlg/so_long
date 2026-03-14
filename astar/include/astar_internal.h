/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:59:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:42:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_INTERNAL_H
# define ASTAR_INTERNAL_H

# include "astar_struct.h"

void	init_astar(t_astar *a_star, t_thread_data *data);
void	found_destination(t_vector2 *dest, t_vector2 *actual, t_astar *a_star,
			t_thread_data *data);
void	find_new_f(t_cell_astar *new, t_vector2 *actual, t_astar *a_star,
			t_thread_data *data);
void	swap_lowest_f(t_open **list);
void	add_to_open(t_open **list, t_cell_astar *values);
void	init_cells(t_astar *a_star, t_thread_data *data);
void	init_open(t_astar *a_star, t_thread_data *data);
void	init_closed(t_astar *a_star, t_thread_data *data);
void	*exit_thread(t_astar *a_star, t_thread_data *data);
void	free_routine(t_astar *a_star, t_thread_data *data);

#endif