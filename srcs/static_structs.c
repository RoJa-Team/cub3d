/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:39:39 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/03 21:59:07 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_objects	*map_objects(void)
{
	static	t_map_objects map_objects;

	return (&map_objects);
}

t_player	*player(void)
{
	static	t_player player;

	return (&player);
}

t_textures	*textures(void)
{
	static	t_textures textures;

	return (&textures);
}

t_game	*game(void)
{
	static	t_game game;

	return (&game);
}