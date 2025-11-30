/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:39:39 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 16:14:18 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_objects	*map_objects(void)
{
	static t_map_objects	map_objects;
	static int				initialized;

	if (!initialized)
	{
		initialized = 1;
		map_objects.map_width = 0;
		map_objects.map_height = 0;
		map_objects.map = NULL;
		map_objects.player_count = 0;
		map_objects.sprite_count = 0;
		map_objects.door_count = 0;
	}

	return (&map_objects);
}

t_player	*player(void)
{
	static t_player	player;
	static int			initialized;

	if (!initialized)
	{	
		initialized = 1;
		player.x = 0;
		player.y = 0;
		player.dir_x = 0;
		player.dir_x = 0;
		player.plane_x = 0;
		player.plane_y = 0;
		player.move_left = 0;
		player.move_right = 0;
		player.move_front = 0;
		player.move_back = 0;
		//player->tool = NULL;
	}
	return (&player);
}

t_frame	*frame(void)
{
	static t_frame	frame;
	static int			initialized;

	if (!initialized)
	{	
		frame.move_speed = 0;	
		frame.rot_speed = 0;	
		initialized = 1;
	}
	return (&frame);
}

t_textures	*textures(void)
{
	static t_textures	textures;
	static int			initialized;

	if (!initialized)
	{
		initialized = 1;
		textures.ccolour = -1;
		textures.fcolour = -1;
	}
	return (&textures);
}

t_screens	*screens(void)
{
	static t_screens	screens;
	static int		initialized;

	if (!initialized)
	{
		initialized = 1;
	}
	return (&screens);
}

t_game	*game(void)
{
	static t_game	game;
	static int		initialized;

	if (!initialized)
	{
		initialized = 1;
		game.mlx = mlx_init();
	}
	return (&game);
}

t_helper	*helper(void)
{
	static t_helper	helper;

	helper.i = 0;
	helper.j = 0;
	helper.x = 0;
	helper.y = 0;
	helper.column = 0;
	helper.row = 0;
	return (&helper);
}
