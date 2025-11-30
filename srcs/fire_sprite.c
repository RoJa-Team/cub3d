/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:51:11 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 19:45:08 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	s->screen_x = (int)((r->game_width / 2)
			* (1 + s->transform_x / s->transform_y));
}

void	project_sprite(t_sprite *s, t_game *r)
{
	s->height = abs((int)(r->game_height / s->transform_y));
	s->width = fabs((int)(r->game_width / s->transform_y) * 0.7);
	s->draw_start_y = -s->height / 2 + r->game_height / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->height / 2 + r->game_height / 2;
	if (s->draw_end_y >= r->game_height)
		s->draw_end_y = r->game_height - 1;
	s->draw_start_x = -s->width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->width / 2 + s->screen_x;
	if (s->draw_end_x >= r->game_width)
		s->draw_end_x = r->game_width - 1;
}

void	draw_sprite_column(t_sprite *s, int stripe, t_game *g)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	d;
	int	color;

	tex_x = (int)(256 * (stripe - (-s->width / 2 + s->screen_x))
			* s->img.w / s->width) / 256;
	if (s->transform_y <= 0 || stripe < 0 || stripe >= g->game_width
		|| s->transform_y > map_objects()->zbuff[stripe])
		return ;
	y = s->draw_start_y;
	while (y < s->draw_end_y)
	{
		d = y * 256 - g->game_height * 128 + s->height * 128;
		tex_y = ((d * s->img.h) / s->height) / 256;
		color = get_pixel_colour(&s->img, tex_x, tex_y);
		put_pixel_img(&screens()->canva, stripe, y, color);
		y++;
	}
}

void	render_fire_sprites(t_game *g, t_map_objects *mo,
	t_sprite *s, double delta)
{
	int			i;
	int			stripe;
	t_player	*_player;

	_player = player();
	animate_sprites(s, mo, textures(), delta);
	sort_sprites(s, mo, _player);
	i = 0;
	while (i < mo->sprite_count)
	{
		if (s[i].active == true)
		{
			transform_sprite(_player, &s[i], g);
			project_sprite(&s[i], g);
			stripe = s[i].draw_start_x;
			while (stripe < s[i].draw_end_x)
			{
				draw_sprite_column(&s[i], stripe, g);
				stripe++;
			}
		}
		i++;
	}
}
