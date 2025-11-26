/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:45:01 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/27 22:53:08 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_raycast	*raycast(void)
{
	static t_raycast	raycast;
	static int		initialized;

	if (!initialized)
	{
		raycast.camera_x = 0;
		raycast.ray_dir_x = 0;
		raycast.ray_dir_y = 0;
		raycast.delta_dist_x = 1;
		raycast.delta_dist_y = 1;
		raycast.step_x = 0;
		raycast.step_y = 0;
		raycast.side_dist_x = 0;
		raycast.side_dist_y = 0;
		raycast.map_x = 0;
		raycast.map_y = 0;
		raycast.side = -1;
		raycast.hit = 0;
		raycast.perp_wall_dist = 0;
		raycast.door = false;
		initialized = 1;
	}
	return (&raycast);
}

t_draw		*draw(void)
{
	static t_draw	draw;
	static int	initialized;

	if (!initialized)
	{
		draw.line_height = 0;
		draw.draw_start = 0;
		draw.draw_end = 0;
		initialized = 1;
	}
	return (&draw);
}

void    raycaster(t_game *game, t_raycast *raycast, t_player *player, t_draw *draw)
{
 	int	x;
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

int	get_tex_color(int tex_x, int tex_y, t_texture *tex)
{
	char	*pixel;

	pixel = tex->img.addr + (tex_y * tex->img.line_len
			+ tex_x * (tex->img.bpp / 8));
	return (*(unsigned int *)pixel);
}

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

t_texture	calculate_texture(t_map_objects *mo, t_raycast *r, t_textures *t, t_draw *d)
{
	t_texture	tex;
	t_door	*door_hit;

	door_hit = find_door(mo->door_count, mo->doors, r->map_x, r->map_y);
	if (r->door == false)
	{
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
	}
	else 
	{
		tex = t->door;
		if (d->wall_x < 0.5)
			d->tex_x = (int)(((d->wall_x + door_hit->offset) / 0.5) * (tex.img.w / 2));
		else
			d->tex_x = (int)(((d->wall_x  - door_hit->offset) / 0.5) * (tex.img.w / 2));		
	}
	return (tex);
}

void	calculate_wall(t_raycast *raycast, t_draw *draw, t_player *player, t_game *game)
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

double get_door_open_amount(t_map_objects *mo, int x, int y)
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
	//get_door_open_amount(mo, r->map_y, r->map_x);
	left_edge = 0.5 - door_hit->offset;
	right_edge = 0.5 + door_hit->offset;
	//printf("offset: %f\n", mo->offset);
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

void	calculate_side_dist(t_raycast *raycast, t_player *player)
{
	raycast->map_x = (int)player->x;
	raycast->map_y = (int)player->y;
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (player->x - raycast->map_x)
			* raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - player->x)
			* raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (player->y - raycast->map_y)
			* raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - player->y)
			* raycast->delta_dist_y;
	}
}
