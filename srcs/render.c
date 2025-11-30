/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:22:44 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/26 21:08:13 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_image *canva, int game_width, int game_height)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	y = 0;
	while (y <= game_height / 2)
	{
		x = 0;
		while (x < game_width)
		{
			put_pixel(canva, x, y, ceiling);
			put_pixel(canva, x, game_height - y, floor);
			x++;
		}
		y++;
	}
}

void	render_hud(t_screens *screens, t_map_objects *map_objs, t_player *player, double delta)
{
	update_hose(&screens->hud.hose, textures(), delta);
	put_img_to_img(&screens->canva, &screens->hud.hose.curr_hose,
		screens->hud.hose.x, screens->hud.hose.y);
	if (game()->open_map == true)
	{
		draw_full_map(&screens->hud.full_map, map_objs, player);
		put_img_to_img(&screens->canva, &screens->hud.full_map.map,
			screens->hud.full_map.x, screens->hud.full_map.y);
	}
	else
	{
		calc_minimap_offsets(&screens->hud.minimap.offsets, map_objs, player);
		draw_minimap(&screens->hud.minimap, map_objs, player);
		put_img_to_img(&screens->canva, &screens->hud.minimap.map,
			screens->hud.minimap.x, screens->hud.minimap.y);
	}
}

void	render(void)
{
	t_game			*_game;
	t_frame			*_frame;
	t_player		*_player;
	t_screens		*_screens;
	t_map_objects 	*mo;
	
	_game = game();
	_frame = frame();
	_player = player();
	_screens = screens();
	mo = map_objects();
	check_movement(_player, mo, _frame);
	if (_player->turn_left)
		rotate_camera(_player, -_frame->rot_speed);
	else if (_player->turn_right)
		rotate_camera(_player, _frame->rot_speed);
	render_background(&_screens->canva, _game->game_width, _game->game_height);
	get_speed_modifiers(_frame);
	animate_doors(mo->doors, mo, _player, _frame->frame_time);
	raycaster(_game, raycast(), _player, draw());
	render_fire_sprites(_game, mo, mo->sprites, _frame->frame_time);
	render_hud(_screens, mo, _player, _frame->frame_time);
	mlx_put_image_to_window(_game->mlx, _game->win, _screens->canva.img_ptr, _game->image_x, _game->image_y);
}
