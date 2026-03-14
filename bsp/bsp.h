/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:58:45 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 15:40:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_H
# define BSP_H

# include "./include/bsp_struct.h"

int		range(int min, int max);
float	frange(float min, float max);
void	free_hall(t_hall *hall);
void	save_to_file(char **array);
void	bsp(const int map_size);
t_room	*get_data(const int height, t_vector2 *size, char ***array,
			int *room_nbr);

#endif