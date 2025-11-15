/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:56:14 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 17:07:21 by rafasant         ###   ########.fr       */
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
	create_hose(&screens->hose);
	create_minimap(&screens->minimap);
	create_canva(&screens->canva);
	create_start(&screens->start);
	create_pause(&screens->pause);
	create_death(&screens->death);
	create_finish(&screens->finish);
}

void	init_sprites(t_map_objects *mo, t_sprite *s, int count)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < mo->map_height)
	{
		x = 0;
		while (x < mo->map_width)
		{
			if (mo->map[y][x] == 'F' && i < count)
			{
				s[i].transform_x = 0;
				s[i].transform_y = 0;
				s[i].screen_x = 0;
				s[i].height = 0;
				s[i].width = 0;
				s[i].draw_start_x = 0;
				s[i].draw_end_x = 0;
				s[i].draw_start_y = 0;
				s[i].draw_end_y = 0;
				s[i].x = x + 0.5;
				s[i].y = y + 0.5;
				s[i].frame = rand() % 8;
				s[i].anim_speed = 0.10 + ((rand() % 40) / 1000.0);
				s[i].frame_time = (double)(rand() % 100) / 100.0
					* s[i].anim_speed;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	allocate_sprites(t_map_objects *mo)
{
	mo->sprites = malloc(sizeof(t_sprite) * mo->sprite_count);
	if (!mo->sprites)
		return ((void)catch()->set("Error\n%s: Error allocating sprites.", 
			__func__), deallocate());
	init_sprites(mo, mo->sprites, mo->sprite_count);
}

void	allocate_zbuffer(t_map_objects *mo, t_screens *sc)
{
	mo->zbuff = malloc(sizeof(double) * sc->canva.w);
	if (!mo->zbuff)
		return ((void)catch()->set("Error\n%s: Error allocating z buffer.", 
			__func__), deallocate());
}

void	prepare_resources()
{
	calculate_game_resolution(game());
	load_textures(textures());
	create_screens(screens());
	allocate_sprites(map_objects());
	allocate_zbuffer(map_objects(), screens());
}