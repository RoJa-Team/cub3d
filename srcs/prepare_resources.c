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

void	init_sprites(t_sprite *s, int x, int y)
{
	s->transform_x = 0;
	s->transform_y = 0;
	s->screen_x = 0;
	s->height = 0;
	s->width = 0;
	s->draw_start_x = 0;
	s->draw_end_x = 0;
	s->draw_start_y = 0;
	s->draw_end_y = 0;
	s->x = x + 0.5;
	s->y = y + 0.5;
	s->frame = rand() % 8;
	s->anim_speed = 0.2 + ((rand() % 40) / 1000.0);
	s->frame_time = (double)(rand() % 100) / 100.0
		* s->anim_speed;
}

void	init_doors(t_door *d, int x, int y)
{
	d->x = x;
	d->y = y;
	d->open_amount = 0;
	d->opening = -1;
	d->offset = 0;
	d->dist = 0;
}

void	init_map_textures(t_map_objects *mo, t_sprite *s, t_door *d)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = 0;
	i = 0;
	j = 0;
	while (y < mo->map_height)
	{
		x = 0;
		while (x < mo->map_width)
		{
			if (mo->map[y][x] == 'F' && i < mo->sprite_count)
			{
				init_sprites(&s[i], x, y);
				i++;
			}
			else if (mo->map[y][x] == 'D' && j < mo->door_count)
			{
				init_doors(&d[j], x, y);
				j++;
			}
			x++;
		}
		y++;
	}
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

void	prepare_resources()
{
	calculate_game_resolution(game());
	load_textures(textures());
	create_screens(screens());
	allocate_map_objects(map_objects());
	allocate_zbuffer(map_objects(), screens());
}