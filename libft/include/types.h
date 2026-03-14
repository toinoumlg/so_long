/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 22:00:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_vector2
{
	int						x;
	int						y;
}							t_vector2;

typedef struct s_vector2_list
{
	t_vector2				value;
	struct s_vector2_list	*next;
	struct s_vector2_list	*prev;
}							t_vector2_list;

typedef struct s_float2
{
	float					x;
	float					y;
}							t_float2;

#endif