/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:39:39 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/25 16:57:05 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_objects	*map_objects(void)
{
	static t_map_objects	map_objects;
	static int				initialized;

	if (!initialized)
	{
		map_objects.player_count = 0;
		initialized = 1;
	}

	return (&map_objects);
}

t_player	*player(void)
{
	static t_player	player;
	static int			initialized;

	if (!initialized)
	{	
		player.x = 0;
		player.y = 0;
		player.dir_x = 0;
		player.dir_x = 0;
		player.plane_x = 0;
		player.plane_y = 0;
		//player->tool = NULL;
		initialized = 1;
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
		textures.ccolour = -1;
		textures.fcolour = -1;
		initialized = 1;
	}

	return (&textures);
}

t_screen	*screen(void)
{
	static t_screen	screen;
	static int		initialized;

	if (!initialized)
	{
		initialized = 1;
	}

	return (&screen);
}

t_game	*game(void)
{
	static t_game	game;
	static int		initialized;

	if (!initialized)
	{
		initialized = 1;
	}

	return (&game);
}
