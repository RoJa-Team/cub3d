/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visuals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:44:19 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 16:44:20 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprites(t_sprite *s, t_textures *textures, int x, int y)
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
	s->frame_time = (double)(rand() % 100) / 100.0 * s->anim_speed;
	s->dissip = false;
	s->active = true;
	s->img = textures->fire_loop[s->frame].img;
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
				init_sprites(&s[i++], textures(), x, y);
			else if (mo->map[y][x] == 'D' && j < mo->door_count)
				init_doors(&d[j++], x, y);
			x++;
		}
		y++;
	}
}
