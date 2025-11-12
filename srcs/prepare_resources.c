/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:56:14 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/12 21:28:22 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_textures *textures)
{
	load_textures_wall(textures);
	load_textures_fire(textures);
	load_textures_hose(textures);
	load_textures_misc(textures);
	scale_hose_images(textures);
}

void	create_screens(t_screens *screens)
{
	create_hose(&screens->hud.hose);
	create_full_map(&screens->hud.full_map, map_objects(), player());
	create_minimap(&screens->hud.minimap, map_objects(), player());
	create_canva(&screens->canva);
	create_start(&screens->start);
	create_pause(&screens->pause);
	create_death(&screens->death);
	create_finish(&screens->finish);
}

void	prepare_resources()
{
	calculate_game_resolution(game());
	load_textures(textures());
	create_screens(screens());
}
