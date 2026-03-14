/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:40:11 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 20:16:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_STRUCT_H
# define BSP_STRUCT_H

# define GRID_SIZE 2

# include "types.h"
# include <stdbool.h>

typedef struct s_cell
{
	t_vector2			min;
	t_vector2			max;
	float				width;
	float				height;
	struct s_cell		*left;
	struct s_cell		*right;
}						t_cell;

typedef struct s_hall
{
	t_cell				*value;
	struct s_hall		*next;
}						t_hall;

typedef struct s_neighbor
{
	t_cell				*value;
	struct s_neighbor	*next;
}						t_neighbor;

typedef struct s_leaf
{
	t_cell				*value;
	t_neighbor			*h_nei;
	t_neighbor			*v_nei;
	t_hall				*h_hall;
	t_hall				*v_hall;
	struct s_leaf		*next;
}						t_leaf;

typedef struct s_bsp_map
{
	t_cell				root;
	t_leaf				*leafs;
	int					nbr_room;
	int					min_cell;
}						t_bsp_map;

typedef struct s_bsp
{
	char				**array;
	t_vector2			size;
	t_bsp_map			map;
}						t_bsp;

typedef struct s_room_value
{
	t_vector2			min;
	t_vector2			max;
	int					size;
}						t_room_value;

typedef struct s_room
{
	t_room_value		value;
	t_hall				*v_hall;
	t_hall				*h_hall;
	struct s_room		*next;
}						t_room;

#endif