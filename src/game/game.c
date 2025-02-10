/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:58:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/02/10 22:39:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_attack(int key_stroked, t_data *data)
{
	if (key_stroked == 65362)
		spawn_sword(data, data->game.moves.up);
	if (key_stroked == 65364)
		spawn_sword(data, data->game.moves.down);
	if (key_stroked == 65361)
		spawn_sword(data, data->game.moves.left);
	if (key_stroked == 65363)
		spawn_sword(data, data->game.moves.right);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	return (0);
	(void)data;
	(void)y;
	(void)button;
	(void)x;
}

int	handle_keys(int key_stroked, t_data *data)
{
	if ((key_stroked == 119 || key_stroked == 97 || key_stroked == 115
			|| key_stroked == 100) && data->game.player.status == 0
		&& data->game.player.idle_frames >= 3)
		player_move(key_stroked, data);
	if ((key_stroked == 65362 || key_stroked == 65364 || key_stroked == 65361
			|| key_stroked == 65363) && data->game.player.status == 0
		&& data->game.actual_axes < 2)
		player_attack(key_stroked, data);
	if (key_stroked == 65307)
		return (free_collectibles(data->game.collectibles),
			mlx_loop_end(data->mlx), 0);
	return (0);
}

int	on_destroy(t_data *data)
{
	return (free_collectibles(data->game.collectibles), mlx_loop_end(data->mlx),
		0);
}

void	collectible_and_ennemy_move_print(t_data *data,
		t_collectible *collectible, t_ennemy *ennemy)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, ennemy->coords.x * PIXEL_PADDING,
		ennemy->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color(&data->textures.ennemies[ennemy->i_image], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		ennemy->next_coords.x * PIXEL_PADDING, ennemy->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	ennemy->coords = ennemy->next_coords;
	ennemy->next_coords = set_vector2(0, 0);
	collectible->is_printed = 1;
	ennemy->is_printed = 1;
}

void	reset_print(t_data *data)
{
	t_collectible	*collectible;
	t_ennemy		*ennemy;
	t_sword			*sword;

	collectible = data->game.collectibles;
	while (collectible)
	{
		collectible->is_printed = 0;
		collectible = collectible->next_collectible;
	}
	sword = data->game.player.swords;
	while (sword)
	{
		sword->is_printed = 0;
		sword = sword->next_sword;
	}
	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy->is_printed = 0;
		ennemy = ennemy->next_ennemy;
	}
}

void	collectible_and_sword_move_print(t_data *data,
		t_collectible *collectible, t_sword *sword)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, sword->coords.x * PIXEL_PADDING,
		sword->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color_offset(&data->textures.coins_r[collectible->i_image],
		&combined);
	set_front_color(&data->textures.player_axe[sword->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		sword->next_coords.x * PIXEL_PADDING, sword->next_coords.y
		* PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	sword->coords = sword->next_coords;
	sword->next_coords = set_vector2(0, 0);
	collectible->is_printed = 1;
	sword->is_printed = 1;
}

void	print_sword_move(t_data *data, t_sword *tmp)
{
	t_image	combined;

	mlx_put_image_to_window(data->mlx, data->window.ptr,
		data->textures.ground[0].image, tmp->coords.x * PIXEL_PADDING,
		tmp->coords.y * PIXEL_PADDING);
	combined.image = mlx_new_image(data->mlx, PIXEL_PADDING, PIXEL_PADDING);
	combined.addr = mlx_get_data_addr(combined.image, &combined.bpp,
			&combined.size_l, &combined.endian);
	combined.wh = data->textures.ground[0].wh;
	set_background_color(&data->textures.ground[0], &combined);
	set_front_color(&data->textures.player_axe[tmp->index], &combined);
	mlx_put_image_to_window(data->mlx, data->window.ptr, combined.image,
		tmp->next_coords.x * PIXEL_PADDING, tmp->next_coords.y * PIXEL_PADDING);
	mlx_destroy_image(data->mlx, combined.image);
	tmp->coords = tmp->next_coords;
	tmp->next_coords = set_vector2(0, 0);
	tmp->is_printed = 1;
}

void	print_object_on_map(t_data *data)
{
	t_collectible	*collectible;
	t_ennemy		*ennemy;
	t_sword			*sword;
	t_ennemy		*ennemy_next;
	t_sword			*sword_next;

	collectible = data->game.collectibles;
	reset_print(data);
	while (collectible)
	{
		ennemy = data->game.ennemies;
		while (ennemy)
		{
			ennemy_next = ennemy->next_ennemy;
			if (ennemy->next_coords.y == collectible->coords.y
				&& ennemy->next_coords.x == collectible->coords.x)
				collectible_and_ennemy_move_print(data, collectible, ennemy);
			if (ennemy->coords.y == collectible->coords.y
				&& ennemy->coords.x == collectible->coords.x)
				collectible_and_ennemy_print(data, collectible, ennemy);
			ennemy = ennemy_next;
		}
		sword = data->game.player.swords;
		while (sword)
		{
			sword_next = sword->next_sword;
			if (sword->next_coords.y == collectible->coords.y
				&& sword->next_coords.x == collectible->coords.x)
				collectible_and_sword_move_print(data, collectible, sword);
			if (sword->coords.y == collectible->coords.y
				&& sword->coords.x == collectible->coords.x)
				collectible_and_sword_print(data, collectible, sword);
			sword = sword_next;
		}
		if (!collectible->is_printed)
			print_collectibles(data, collectible);
		collectible = collectible->next_collectible;
	}
	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy_next = ennemy->next_ennemy;
		if (!ennemy->is_printed)
		{
			if (ennemy->next_coords.y || ennemy->next_coords.x)
				print_ennemies_move(data, ennemy);
			else
				print_ennemies(data, ennemy);
		}
		ennemy = ennemy_next;
	}
	sword = data->game.player.swords;
	while (sword)
	{
		sword_next = sword->next_sword;
		if (!sword->is_printed)
		{
			if (sword->next_coords.y || sword->next_coords.x)
				print_sword_move(data, sword);
			else
				print_sword(data, sword);
		}
		sword = sword_next;
	}
	if (data->game.player.status == 1)
		print_player_moving(data);
	if (data->game.player.status == 0 && data->frames % 2 == 0)
		print_player_idle(data);
}

void	update_image_index(t_data *data)
{
	t_collectible	*collectible;
	t_ennemy		*ennemy;
	t_ennemy		*ennemy_next;
	t_sword			*sword;

	collectible = data->game.collectibles;
	while (collectible)
	{
		if (collectible->i_image == 12)
			collectible->i_image = 0;
		collectible->i_image++;
		collectible = collectible->next_collectible;
	}
	ennemy = data->game.ennemies;
	while (ennemy)
	{
		ennemy_next = ennemy->next_ennemy;
		if (ennemy->i_image == 10)
			ennemy->i_image = 0;
		ennemy->i_image++;
		if (ennemy->i_image == 21)
			destroy_ennemy(&data->game.ennemies, ennemy->coords, data);
		ennemy = ennemy_next;
	}
	sword = data->game.player.swords;
	while (sword)
	{
		if (sword->index == 3)
			sword->index = 0;
		sword->index++;
		sword = sword->next_sword;
	}
}

void	update_entities(t_data *data)
{
	if (data->frames % 6 == 0)
		update_swords(data);
	if (data->frames % 18 == 0)
		update_ennemies(data);
}

int	update(t_data *data)
{
	struct timeval	current_time;
	const double	target_fps = 12.0;
	const double	frame_target = 1.0 / target_fps;

	gettimeofday(&current_time, NULL);
	data->timer.delta_time = (current_time.tv_sec
			- data->timer.last_frame.tv_sec) + (current_time.tv_usec
			- data->timer.last_frame.tv_usec) / 1000000.0;
	if (data->timer.delta_time >= frame_target)
	{
		data->frames++;
		data->game.player.idle_frames++;
		data->timer.time += data->timer.delta_time;
		print_object_on_map(data);
		update_image_index(data);
		update_entities(data);
		print_move_string(data);
		if (data->game.game_finished == 1)
			spawn_exit(data);
		if (data->game.game_finished == 3)
			return (mlx_loop_end(data->mlx), 0);
		data->timer.last_frame = current_time;
	}
	return (0);
}

void	init_game(t_data *data)
{
	data->timer.time = 0.0;
	gettimeofday(&data->timer.last_frame, NULL);
	data->game.player.moves = 0;
	data->game.actual_axes = 0;
	data->game.player.health = 3;
	data->game.player.idle_frames = 0;
	data->game.player.idle_index = 0;
	data->frames = 0;
	data->window.move = set_vector2(0, 0);
	data->game.game_finished = 0;
	data->game.player.status = 0;
	data->game.player.swords = NULL;
	data->game.moves = set_move();
	data->mlx = mlx_init();
	set_textures(data);
	init_window(data->map, &data->window, data->mlx, data->textures);
	update_collectible_coords(data->game.collectibles, data->window.min);
	update_ennemies_coords(data->game.ennemies, data->window.min);
	mlx_set_font(data->mlx, data->window.ptr,
		"-urw-urw gothic l-demibold-r-normal--0-0-0-0-p-0-iso8859-15");
	print_move_string(data);
}

void	game(t_data data)
{
	init_game(&data);
	mlx_hook(data.window.ptr, 2, (1L << 0), handle_keys, &data);
	mlx_mouse_hook(data.window.ptr, handle_mouse, &data);
	mlx_hook(data.window.ptr, 17, 0, on_destroy, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
	free_game(data);
}
