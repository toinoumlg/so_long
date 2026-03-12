/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:30:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/12 08:29:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_H
# define WORKER_H

# include "data.h"

t_worker_routine	*init_workers(t_vector2 screen_res,
						t_pthread_locks *locks_data, t_img screen_image,
						t_data *data);

#endif