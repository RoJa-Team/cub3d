/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:51:11 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/14 23:15:12 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	animate_sprites(t_sprite *s, t_map_objects *mo, double delta)
{
	int	i;

	i = 0;
	while (i < mo->sprite_count)
	{
		s[i].frame_time += delta;
		if (s[i].frame_time >= s[i].anim_speed)
		{
			s[i].frame_time = 0.0;
			s[i].frame = (s[i].frame + 1) % 8; 
		}
		i++;
	}
}

int		player_close_to_door(t_map_objects *mo, t_player *p)
{
	int		step_x;
	int		step_y;

	step_x = (int)(p->plane_x * frame()->move_speed - MARGIN);
	step_y = (int)(p->plane_y * frame()->move_speed - MARGIN);

	return (mo->map[step_y][step_x] == 'D');
}

void	animate_doors(t_door *d, t_map_objects *mo, t_player *p, double delta)
{
	int	i;

	i = 0;
	while (i < mo->door_count)
	{
		d[i].dist = ((p->x - 0.5) - d[i].x) * ((p->x - 0.5) - d[i].x) 
			+ ((p->y - 0.5) - d[i].y) * ((p->y - 0.5) - d[i].y);
		if (d[i].dist <= 2)
			d[i].opening = 1;
		else
			d[i].opening = -1;
		if (d[i].opening == 1)
			d[i].open_amount += delta * 1.5;
		else if (d[i].opening == -1)
			d[i].open_amount -= delta * 1.5;
		if (d[i].open_amount >= 1)
			d[i].open_amount = 1;
		else if (d[i].open_amount <= 0)
			d[i].open_amount = 0;
		d[i].offset = mo->doors[i].open_amount * 0.5;
		i++;
	}
}

void	transform_sprite(t_player *p, t_sprite *s, t_game *r)
{
	double	inv_det;
	double	sx;
	double	sy;

	sx = s->x - p->x;
	sy = s->y - p->y;
	inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	s->transform_x = inv_det * (p->dir_y * sx - p->dir_x * sy);
	s->transform_y = inv_det * (-p->plane_y * sx + p->plane_x * sy);
	s->screen_x = (int)((r->game_width / 2) * (1 + s->transform_x / s->transform_y));
}

void	project_sprite(t_sprite *s, t_game *r)
{
	s->height = abs((int)(r->game_height / s->transform_y));
	s->width = fabs((int)(r->game_width / s->transform_y) * 0.7);
	s->draw_start_y = -s->height / 2 + r->game_height / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->height / 2 + r->game_height /2;
	if (s->draw_end_y >= r->game_height)
		s->draw_end_y = r->game_height - 1;
	s->draw_start_x = -s->width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->width / 2 + s->screen_x;
	if (s->draw_end_x >= r->game_width)
		s->draw_end_x = r->game_width - 1;
}

void	draw_sprite_column(t_sprite *s, int stripe, t_game *g, t_texture *tx)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	d;
	int	color;

	tex_x = (int)(256 * (stripe - (-s->width / 2 + s->screen_x))
			* tx->img.w / s->width) / 256;
	if (s->transform_y <= 0 || stripe < 0 || stripe >= g->game_width
	|| s->transform_y > map_objects()->zbuff[stripe])
		return ;
	y = s->draw_start_y;
	while (y < s->draw_end_y)
	{
		d = y * 256 - g->game_height * 128 + s->height * 128;
		tex_y = ((d * tx->img.h) / s->height) / 256;
		color = get_pixel_colour(&tx->img, tex_x, tex_y);
		put_pixel_img(&screens()->canva, stripe, y, color);
		y++;
	}
}

void	sort_sprites(t_sprite *s, t_map_objects *mo, t_player *p)
{
	int		i;
	int		j;
	t_sprite	tmp;

	i = -1;
	while (++i < mo->sprite_count)
	{
		s[i].dist = (p->x - s[i].x) * (p->x - s[i].x) 
			+ (p->y - s[i].y) * (p->y - s[i].y);
	}
	i = -1;
	while (++i < mo->sprite_count - 1)
	{
		j = i;
		while (++j < mo->sprite_count)
		{
			if (s[i].dist < s[j].dist)
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}
}

void	render_fire_sprites(t_game *g, t_map_objects *mo, t_sprite *s, double delta)
{
	int	i;
	int	stripe;

	animate_sprites(s, mo, delta);
	sort_sprites(s, mo, player());
	i = 0;
	while (i < mo->sprite_count)
	{
		transform_sprite(player(), &s[i], g);
		project_sprite(&s[i], g);
		stripe = s[i].draw_start_x;
		while (stripe < s[i].draw_end_x)
		{
			draw_sprite_column(&s[i], stripe, g, &textures()->fire_loop[s[i].frame]);
			stripe++;
		}
		i++;
	}
}
