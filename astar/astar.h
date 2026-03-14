/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:58:45 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:45:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_H
# define ASTAR_H

# include "./include/astar_struct.h"

bool		astar(char **map, t_vector2 start, const t_vector2 *map_size);
t_vector2	*astar_single(const char **map, const t_vector2 *start,
				const t_vector2 *target, const t_vector2 *map_size);

#endif