/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:57:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/09 15:05:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_COLORS_H
# define PRINT_COLORS_H

# ifndef FRONT_COLORS
#  define BLACK "\x1B[30m"
#  define RED "\x1B[31m"
#  define GREEN "\x1B[32m"
#  define YELLOW "\x1B[33m"
#  define BLUE "\x1B[34m"
#  define MAGENTA "\x1B[35m"
#  define CYAN "\x1B[36m"
#  define WHITE "\x1B[37m"
# endif

# ifndef BACKGROUND_COLORS
#  define BG_BLACK "\x1B[40m"
#  define BG_RED "\x1B[41m"
#  define BG_GREEN "\x1B[42m"
#  define BG_YELLOW "\x1B[43m"
#  define BG_BLUE "\x1B[44m"
#  define BG_MAGENTA "\x1B[45m"
#  define BG_CYAN "\x1B[46m"
#  define BG_WHITE "\x1B[47m"
# endif

# define RESET "\x1B[0m"

#endif
