/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:39:40 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:43:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astar_globals.h"

const t_vector2		g_up = {-1, 0};
const t_vector2		g_down = {1, 0};
const t_vector2		g_right = {0, 1};
const t_vector2		g_left = {0, -1};

const t_cell_astar	g_default_cell = {{-1, -1}, __FLT_NORM_MAX__,
		__FLT_NORM_MAX__, __FLT_NORM_MAX__};
