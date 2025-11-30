/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:15:42 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 16:15:44 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dissipate_fire(t_sprite *s, t_map_objects *mo, t_textures *t)
{
	if (s->active == false)
		return ;
	if (s->dissip <= 5)
	{
		s->img = t->fire_end[s->dissip - 1].img;
		s->dissip++;
	}
	else
	{
		s->active = false;
		mo->map[(int)s->y][(int)s->x] = '0';
	}
}

void	animate_sprites(t_sprite *s, t_map_objects *mo,
	t_textures *textures, double delta)
{
	int	i;

	i = 0;
	while (i < mo->sprite_count)
	{
		s[i].frame_time += delta;
		if (s[i].frame_time >= s[i].anim_speed)
		{
			s[i].frame_time = 0.0;
			if (s[i].dissip == 0 && s[i].active == true)
			{
				s[i].frame = (s[i].frame + 1) % 8;
				s[i].img = textures->fire_loop[s[i].frame].img;
			}
			else
			{
				dissipate_fire(&s[i], mo, textures);
			}
		}
		i++;
	}
}

int	player_close_to_door(t_map_objects *mo, t_player *p)
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

void	sort_sprites(t_sprite *s, t_map_objects *mo, t_player *p)
{
	int			i;
	int			j;
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
