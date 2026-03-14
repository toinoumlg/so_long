/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:01:42 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 22:01:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "data.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
void	init_engine(t_data *data);
int		parsing_error(t_data *data, char *error_string);
void	populate_rooms(t_room *rooms, char **array, t_vector2 *map_size);
void	load_map(t_data *data, char *path);
void	check_map(t_data *data);
void	add_collectible(t_data *data, int x, int y);
void	add_ennemy(t_data *data, int x, int y);
void	free_ennemies(t_ennemy *ennemies);
void	free_collectibles(t_collectible *collectibles);
void	free_map(t_map *map);

#endif