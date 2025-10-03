/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:39:39 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/03 19:27:32 by rafasant         ###   ########.fr       */
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
		initialized = 1;
	}

	return (&player);
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
		hose_idle = 
		textures.hose_shooting[0].path = "../textures/edited/fire_loop1.xpm"
		textures.fire_loop[0].path = "../textures/edited/fire_loop1.xpm"; 
		textures.fire_loop[1].path = "../textures/edited/fire_loop2.xpm"; 
		textures.fire_loop[2].path = "../textures/edited/fire_loop3.xpm"; 
		textures.fire_loop[3].path = "../textures/edited/fire_loop4.xpm"; 
		textures.fire_loop[4].path = "../textures/edited/fire_loop5.xpm"; 
		textures.fire_loop[5].path = "../textures/edited/fire_loop6.xpm"; 
		textures.fire_loop[6].path = "../textures/edited/fire_loop7.xpm"; 
		textures.fire_loop[7].path = "../textures/edited/fire_loop8.xpm"; 
		textures.fire_ending[0].path = "../textures/edited/burning_end_1.xpm"; 
		textures.fire_ending[1].path = "../textures/edited/burning_end_2.xpm"; 
		textures.fire_ending[2].path = "../textures/edited/burning_end_3.xpm"; 
		textures.fire_ending[3].path = "../textures/edited/burning_end_4.xpm"; 
		textures.fire_ending[4].path = "../textures/edited/burning_end_5.xpm"; 
		"textures/edited/burning_end_2.xpm",
		"textures/edited/burning_end_3.xpm", "textures/edited/burning_end_4.xpm", "textures/edited/burning_end_5.xpm" }
		door[3] = { "textures/edited/door_closed.xpm", "textures/edited/door_semi_open.xpm", "textures/edited/door_open.xpm" }
		clouds = "textures/edited/clouds.xpm"
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
