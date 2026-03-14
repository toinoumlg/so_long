/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_globals.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:40:09 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:43:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_GLOBALS_H
# define ASTAR_GLOBALS_H

# include "astar_struct.h"
# include <pthread.h>

extern const t_vector2	g_up;
extern const t_vector2	g_down;
extern const t_vector2	g_right;
extern const t_vector2	g_left;

extern const t_cell_astar		g_default_cell;

#endif