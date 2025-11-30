/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:03:49 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 16:03:51 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_camera(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin (rot_speed)
		+ player->dir_y * cos(rot_speed);
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
}

int	is_wall(t_map_objects *mo, double x, double y)
{
	int	my;
	int	mx;

	my = (int)y;
	mx = (int)x;
	if (mx < 0 || my >= mo->map_height || my < 0 || mx >= mo->map_width)
		return (1);
	return (mo->map[my][mx] == '1' || mo->map[my][mx] == 'F' ||
		(mo->map[my][mx] == 'D' && get_door_open_amount(mo, mx, my) < 0.95));
}

int	can_move(t_map_objects *map_objects, double x, double y)
{
	if (is_wall(map_objects, x - MARGIN, y - MARGIN))
		return (0);
	if (is_wall(map_objects, x + MARGIN, y - MARGIN))
		return (0);
	if (is_wall(map_objects, x - MARGIN, y + MARGIN))
		return (0);
	if (is_wall(map_objects, x + MARGIN, y + MARGIN))
		return (0);
	return (1);
}

void	move(t_player *player, t_map_objects *map_objects,
	double step_x, double step_y)
{
	if (can_move(map_objects, player->x + step_x, player->y))
		player->x += step_x;
	if (can_move(map_objects, player->x, player->y + step_y))
		player->y += step_y;
}

void	check_movement(t_player *player, t_map_objects *mo, t_frame *frame)
{
	if (player->move_front)
	{
		move(player, mo, player->dir_x * frame->move_speed,
			player->dir_y * frame->move_speed);
	}
	if (player->move_back)
	{
		move(player, mo, -player->dir_x * frame->move_speed,
			-player->dir_y * frame->move_speed);
	}
	if (player->move_right)
	{
		move(player, mo, -player->plane_x * frame->move_speed,
			-player->plane_y * frame->move_speed);
	}
	if (player->move_left)
	{
		move(player, mo, player->plane_x * frame->move_speed,
			player->plane_y * frame->move_speed);
	}
}
