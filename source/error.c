/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/08 11:01:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_string.h"
#include "so_long.h"

int	parsing_error(t_map *map, char *error_string)
{
	free_map(map);
	ft_putstr_fd(RED "Error\nParsing :", 2);
	ft_putstr_fd(error_string, 2);
	ft_putstr_fd("\n" RESET, 2);
	return (1);
}