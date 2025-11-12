/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:51:11 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/08 18:35:08 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int fire_frame = 0;
static	int fire_tick = 0;

void	update_fire_anim(void)
{
	fire_tick += 1;
	if (fire_tick > 10)
	{
		fire_tick = 0;
		fire_frame = (fire_frame + 1) % 5;
	}
}

static t_texture	current_fire_tex(void)
{
	return (textures()->fire_loop[fire_frame]);
}

static void	count_fire_sprites(t_sprite **sprite, int *count, t_map_objects *map_objects, t_player *player)
{
	static	t_sprite	buf[4096];
	int	y;
	int	x;
	double	dx;
	double	dy;

	y = 0;
	while (y < map_objects->map_height)
	{
		x = 0;
		while (x < map_objects->map_width)
		{
			if (map_objects->map[y][x] == 'F')
			{
				if (count < (int)(sizeof(buf)/sizeof(buf[0])))
				{
					buf[count].x = x + 0.5;
					buf[count].y = y + 0.5;
					dx = buf[count].x - player->x;
					dy = buf[count].y - player->y;
					buf[count].dist = dx * dx + dy * dy;
				       	count++;	
				}
			}
			x++;
		}
		y++;
	}
	*sprite = buf;
}

void	render_fire_sprites(void)
{
	t_sprite	*sprite;
	t_texture	tex;
	int	n;
	int	k;

	k = 0;
	n = 0;
	count_fire_sprites(&sprite, &n, map_objects(), player());
	if (n <= 0)
		return ;
	sort_sprites(sprite, n);
	tex = current_fire_tex();
	while (k < n)
	{
		draw_fire_sprite(sprite[k].x, sprite[k].y, &tex);
		k++;
	}
}


