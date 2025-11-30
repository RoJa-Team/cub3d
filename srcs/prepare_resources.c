/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:56:14 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 15:20:41 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_textures *textures)
{
	load_textures_wall(textures);
	load_textures_fire(textures);
	load_textures_hose(textures);
	load_textures_misc(textures);
	scale_hose_images(textures, calc_zoom_ratio);
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

void	allocate_map_objects(t_map_objects *mo)
{
	mo->sprites = malloc(sizeof(t_sprite) * mo->sprite_count);
	if (!mo->sprites)
		return ((void)catch()->set("Error\n%s: Error allocating sprites.",
				__func__), deallocate());
	mo->doors = malloc(sizeof(t_door) * mo->door_count);
	if (!mo->doors)
		return ((void)catch()->set("Error\n%s: Error allocating doors.",
				__func__), deallocate());
	init_map_textures(mo, mo->sprites, mo->doors);
}

void	allocate_zbuffer(t_map_objects *mo, t_screens *sc)
{
	mo->zbuff = malloc(sizeof(double) * sc->canva.w);
	if (!mo->zbuff)
		return ((void)catch()->set("Error\n%s: Error allocating z buffer.",
				__func__), deallocate());
}

void	prepare_resources(void)
{
	calculate_game_resolution(game());
	load_textures(textures());
	create_screens(screens());
	allocate_map_objects(map_objects());
	allocate_zbuffer(map_objects(), screens());
}
