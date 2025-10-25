/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:39:39 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/25 21:14:20 by rafasant         ###   ########.fr       */
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

t_textures	*textures(void)
{
	static t_textures	textures;
	static int			initialized;

	if (!initialized)
	{
		load_textures_fire(&textures);
		load_textures_hose(&textures);
		load_textures_misc(&textures);
		scale_hose_images(&textures);
		textures.ccolour = -1;
		textures.fcolour = -1;
		initialized = 1;
	}
	return (&textures);
}

t_screens	*screens(void)
{
	static t_screens	screens;
	static int		initialized;

	if (!initialized)
	{
		create_hose(&screens.hose);
		create_minimap(&screens.minimap);
		create_canva(&screens.canva);
		create_start(&screens.start);
		create_pause(&screens.pause);
		create_death(&screens.death);
		create_finish(&screens.finish);
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
		game.mlx = mlx_init();
		calculate_resolution(&game);
		initialized = 1;
	}
	return (&game);
}
