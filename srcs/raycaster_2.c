/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:08:40 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 15:08:42 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tex_pixel(t_draw *draw, t_screens *screen, t_texture tex, int x)
{
	int	y;
	int	color;

	draw->step = 1.0 * tex.img.h / draw->line_height;
	draw->tex_pos = (draw->draw_start - game()->game_height / 2
			+ draw->line_height / 2) * draw->step;
	y = draw->draw_start;
	while (y <= draw->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos % tex.img.h;
		draw->tex_pos += draw->step;
		color = get_tex_color(draw->tex_x, draw->tex_y, &tex);
		put_pixel_img(&screen->canva, x, y, color);
		y++;
	}
}

t_texture	get_wall_texture(t_raycast *r, t_textures *t, t_draw *d)
{
	t_texture	tex;

	if (r->side == 0 && r->ray_dir_x > 0)
		tex = t->wall[EA];
	else if (r->side == 0 && r->ray_dir_x < 0)
		tex = t->wall[WE];
	else if (r->side == 1 && r->ray_dir_y > 0)
		tex = t->wall[SO];
	else if (r->side == 1 && r->ray_dir_y < 0)
		tex = t->wall[NO];
	d->tex_x = (int)(d->wall_x * (double)tex.img.w);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y > 0))
		d->tex_x = tex.img.w - d->tex_x - 1;
	return (tex);
}

void	dda(t_raycast *r, t_map_objects *mo)
{
	r->hit = 0;
	r->door = false;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (mo->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
		else if (mo->map[r->map_y][r->map_x] == 'D')
			r->hit = ray_hit_door(mo, r, player());
	}
}
