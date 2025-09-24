/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:39:39 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/24 23:09:14 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_objects	*map_objects(void)
{
	static t_map_objects	map_objects;
	static int				initialized;

	if (!initialized)
	{
		
	}

	return (&map_objects);
}

t_player	*player(void)
{
	static t_player	player;
	static int			initialized;

	if (!initialized)
	{
		
	}

	return (&player);
}

t_textures	*textures(void)
{
	static t_textures	textures;
	static int			initialized;

	if (!initialized)
	{
		textures.wall = malloc(sizeof(t_texture) * 4);
		textures.door = malloc(sizeof(t_texture) * 3);
		textures.ceiling = malloc(sizeof(t_texture) * 1);
		textures.floor = malloc(sizeof(t_texture) * 1);
		textures.ccolour = malloc(sizeof(int) * 3);
		textures.fcolour = malloc(sizeof(int) * 3);
	}

	return (&textures);
}

t_game	*game(void)
{
	static t_game	game;
	static int		initialized;

	if (!initialized)
	{
		
	}

	return (&game);
}