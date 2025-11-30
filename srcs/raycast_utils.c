/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:01:39 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 15:01:41 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_door_open_amount(t_map_objects *mo, int x, int y)
{
	int	i;

	i = 0;
	while (i < mo->door_count)
	{
		if (mo->doors[i].x == x && mo->doors[i].y == y)
		{
			mo->doors[i].offset = mo->doors[i].open_amount * 0.5;
			return (mo->doors[i].open_amount);
		}
		i++;
	}
	return (0);
}

int	ray_hit_door(t_map_objects *mo, t_raycast *r, t_player *p)
{
	double	left_edge;
	double	right_edge;
	double	tmp_wall_x;
	double	perp;
	t_door	*door_hit;

	door_hit = find_door(mo->door_count, mo->doors, r->map_x, r->map_y);
	left_edge = 0.5 - door_hit->offset;
	right_edge = 0.5 + door_hit->offset;
	if (r->side == 0)
	{
		perp = r->side_dist_x - r->delta_dist_x;
		tmp_wall_x = p->y + perp * r->ray_dir_y;
	}
	else
	{
		perp = r->side_dist_y - r->delta_dist_y;
		tmp_wall_x = p->x + perp * r->ray_dir_x;
	}
	tmp_wall_x -= floor(tmp_wall_x);
	if (tmp_wall_x > left_edge && tmp_wall_x < right_edge)
		return (0);
	r->door = true;
	return (1);
}

t_door	*find_door(int max, t_door *d, int x, int y)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (x == d[i].x && y == d[i].y)
			return (&d[i]);
		i++;
	}
	return (NULL);
}

int	get_tex_color(int tex_x, int tex_y, t_texture *tex)
{
	char	*pixel;

	pixel = tex->img.addr + (tex_y * tex->img.line_len
			+ tex_x * (tex->img.bpp / 8));
	return (*(unsigned int *)pixel);
}
