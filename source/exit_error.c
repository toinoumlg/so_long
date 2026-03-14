/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 21:42:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "error_string.h"
#include "internal.h"
#include "print_colors.h"
#include "put.h"

void	free_data(t_data *data)
{
	free_map(&data->map);
	if (data->collectibles)
		free_collectibles(data->collectibles);
	if (data->ennemies)
		free_ennemies(data->ennemies);
}

int	parsing_error(t_data *data, char *error_string)
{
	ft_putstr_fd(RED "Error\nParsing: ", 2);
	ft_putstr_fd(error_string, 2);
	ft_putstr_fd("\n" RESET, 2);
	if (data)
		free_data(data);
	return (1);
}