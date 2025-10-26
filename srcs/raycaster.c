/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:45:01 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/26 17:53:16 by joafern2         ###   ########.fr       */
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

void    raycaster(void)
{
 	int	x;

	x = 0;
	while (x < game()->game_width)
	{
		raycast()->camera_x = 2 * (x / (double)(game()->game_width)) - 1;
		calculate_delta_dist(raycast(), player());
		calculate_side_dist(raycast(), player());
		dda(raycast(), map_objects());
		calculate_wall(raycast(), draw(), player(), game());
		calculate_texture(x, raycast(), textures(), draw());
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

void	draw_tex_pixel(t_draw *draw, t_screen *screen, t_texture tex, int x)
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

void	calculate_texture(int x, t_raycast *raycast, t_textures *textures, t_draw *draw)
{
	t_texture	tex;

	if (raycast->side == 0 && raycast->ray_dir_x > 0)
		tex = textures->wall[EA];
	else if (raycast->side == 0 && raycast->ray_dir_x < 0)
		tex = textures->wall[WE];
	else if (raycast->side == 1 && raycast->ray_dir_y > 0)
		tex = textures->wall[SO];
	else if (raycast->side == 1 && raycast->ray_dir_y < 0)
		tex = textures->wall[NO];
	draw->tex_x = (int)(draw->wall_x * (double)tex.img.w);
	if ((raycast->side == 0 && raycast->ray_dir_x > 0) 
			|| (raycast->side == 1 && raycast->ray_dir_y > 0))
		draw->tex_x = tex.img.w - draw->tex_x - 1;
	draw_tex_pixel(draw, screen(), tex, x);
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
	else
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

void	dda(t_raycast *raycast, t_map_objects *map_objects)
{
	raycast->hit = 0;
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (map_objects->map[raycast->map_y][raycast->map_x] == '1')
			raycast->hit = 1;
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
