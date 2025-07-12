/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/12 07:40:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "print_colors.h"
#include "so_long.h"

void	free_data(t_data *data)
{
	free_map(&data->map);
	if (data->player)
		free(data->player);
	if (data->collectibles)
		free_collectibles(data->collectibles);
	if (data->ennemies)
		free_ennemies(data->ennemies);
}

int	pathfinding_error(t_a_star *a_star, t_data *data, char *error_string)
{
	ft_putstr_fd(RED "Error\nParsing: ", 2);
	ft_putstr_fd(error_string, 2);
	ft_putstr_fd("\n" RESET, 2);
	free_a_star_routine(a_star);
	free_data(data);
	return (1);
}

int	parsing_error(t_data *data, char *error_string)
{
	ft_putstr_fd(RED "Error\nParsing: ", 2);
	ft_putstr_fd(error_string, 2);
	ft_putstr_fd("\n" RESET, 2);
	free_data(data);
	return (1);
}