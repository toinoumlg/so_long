/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:14:49 by amalangu          #+#    #+#             */
/*   Updated: 2026/04/03 10:48:11 by toinou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../libft/include/mem.h"
#include "../libft/include/put.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd(RED "Error\nNo or too much arguments\n" RESET,2),
			-1);
	data.map = ft_calloc(sizeof(t_map), 1);
	if (!data.map)
		return (ft_putstr_fd(RED "Error\nFailed calloc on map\n" RESET,2), -1);
	else
		data.map->file_name = av[1];
	if (set_map(data.map))
		return (-1);
	game(data);
}
