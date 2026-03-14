/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:40:11 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 12:42:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_STRUCT_H
# define ASTAR_STRUCT_H

# define MAX_THREAD 200

# include "types.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_cell_astar
{
	t_vector2			coords;
	float				g;
	float				h;
	float				f;
}						t_cell_astar;

typedef struct s_open
{
	t_cell_astar		cell;
	struct s_open		*next;
	struct s_open		*prev;
}						t_open;

typedef char			t_closed;

typedef struct s_astar
{
	t_cell_astar		**cells;
	t_open				*open;
	t_closed			**closed;
}						t_astar;

typedef struct s_results
{
	t_vector2_list		*final_path;
	struct s_results	*next;
}						t_results;

typedef struct s_thread_data
{
	t_vector2			start;
	t_vector2			end;
	const char			**map;
	const t_vector2		*map_size;
}						t_thread_data;

typedef struct s_watcher
{
	const char			**map;
	pthread_t			threads[MAX_THREAD];
	int					started_thread;
	const t_vector2		*map_size;
}						t_watcher;

#endif