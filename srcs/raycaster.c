/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:45:01 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 19:31:35 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycaster(t_game *game, t_raycast *raycast,
	t_player *player, t_draw *draw)
{
	int			x;
	t_texture	tex;

	x = 0;
	while (x < game->game_width)
	{
		raycast->transparent = false;
		raycast->camera_x = 2 * (x / (double)(game->game_width)) - 1;
		calculate_delta_dist(raycast, player);
		calculate_side_dist(raycast, player);
		dda(raycast, map_objects());
		calculate_wall(raycast, draw, player, game);
		tex = calculate_texture(map_objects(), raycast, textures(), draw);
		draw_tex_pixel(draw, screens(), tex, x);
		map_objects()->zbuff[x] = raycast->perp_wall_dist;
		x++;
	}
}

t_texture	calculate_texture(t_maps_objects *mo, t_raycast *r,
	t_textures *t, t_draw *d)
{
	t_texture	tex;
	t_door		*door_hit;

	door_hit = find_door(mo->door_count, mo->doors, r->map_x, r->map_y);
	if (r->door == false)
		tex = get_wall_texture(r, t, d);
	else
	{
		tex = t->door;
		if (d->wall_x < 0.5)
			d->tex_x = (int)(((d->wall_x + door_hit->offset) / 0.5)
					* (tex.img.w / 2));
		else
			d->tex_x = (int)(((d->wall_x - door_hit->offset) / 0.5)
					* (tex.img.w / 2));
	}
	return (tex);
}

void	calculate_wall(t_raycast *raycast, t_draw *draw,
	t_player *player, t_game *game)
{
	if (raycast->side == 0)
	{
		raycast->perp_wall_dist = raycast->side_dist_x
			- raycast->delta_dist_x;
		draw->wall_x = player->y + raycast->perp_wall_dist
			* raycast->ray_dir_y;
	}
	else if (raycast->side == 1)
	{
		raycast->perp_wall_dist = raycast->side_dist_y
			- raycast->delta_dist_y;
		draw->wall_x = player->x + raycast->perp_wall_dist
			* raycast->ray_dir_x;
	}
	draw->wall_x -= floor(draw->wall_x);
	draw->line_height = (int)(game->game_height / raycast->perp_wall_dist);
	draw->draw_start = (-draw->line_height / 2) + (game->game_height / 2);
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = (draw->line_height / 2) + (game->game_height / 2);
	if (draw->draw_end >= game->game_height)
		draw->draw_end = game->game_height - 1;
}

void	calculate_delta_dist(t_raycast *raycast, t_player *player)
{
	raycast->ray_dir_x = player->dir_x + (player->plane_x
			* raycast->camera_x);
	raycast->ray_dir_y = player->dir_y + (player->plane_y
			* raycast->camera_x);
	if (raycast->ray_dir_x == 0)
		raycast->delta_dist_x = 1e30;
	else
		raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	if (raycast->ray_dir_y == 0)
		raycast->delta_dist_y = 1e30;
	else
		raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
}

void	calculate_side_dist(t_raycast *r, t_player *p)
{
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
	}
}
