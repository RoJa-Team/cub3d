/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:46:43 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/19 20:27:59 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	struct	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1e6);
}

void	get_speed_modifiers(t_frame *frame)
{
	static double	old_time = 0.0;
	double		time;
	double		frame_time;

	time = get_time();
	if (old_time == 0.0)
		old_time = time;
	frame_time = time - old_time;
	old_time = time;
	frame->move_speed = frame_time * 5.0;
	frame->rot_speed = frame_time * 3.0;
	/*if (frame->rot_speed > 0.05)
		frame->rot_speed = 0.075;
	*/
}

void	turn_left(t_player *player, t_frame *frame)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (player->turn_left)
	{
		player->dir_x = player->dir_x * cos(-frame->rot_speed) 
			- player->dir_y * sin(-frame->rot_speed);
		player->dir_y = old_dir_x * sin (-frame->rot_speed) 
			+ player->dir_y * cos(-frame->rot_speed);
		player->plane_x = player->plane_x * cos(-frame->rot_speed)
			- player->plane_y * sin(-frame->rot_speed);
		player->plane_y = old_plane_x * sin(-frame->rot_speed)
			+ player->plane_y * cos(-frame->rot_speed);
	}
}

void	turn_right(t_player *player, t_frame *frame)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (player->turn_right)
	{
		player->dir_x = player->dir_x * cos(frame->rot_speed) 
			- player->dir_y * sin(frame->rot_speed);
		player->dir_y = old_dir_x * sin (frame->rot_speed) 
			+ player->dir_y * cos(frame->rot_speed);
		player->plane_x = player->plane_x * cos(frame->rot_speed)
			- player->plane_y * sin(frame->rot_speed);
		player->plane_y = old_plane_x * sin(frame->rot_speed)
			+ player->plane_y * cos(frame->rot_speed);
	}
}


int	is_wall(t_map_objects *map_objects, double x, double y)
{
	int	my;
	int	mx;

	my = (int)y;
	mx = (int)x;
	if (mx < 0 || my >= map_objects->map_height || my < 0 || mx >= map_objects->map_width)
		return (1);
	return (map_objects->map[my][mx] == '1' || map_objects->map[my][mx] == 'D' || map_objects->map[my][mx] == 'F');
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

void	move_left(t_player *player, t_map_objects *map_objects, t_frame *frame)
{
	double	step_x;
	double	step_y;

	step_x = player->plane_x * frame->move_speed;
	step_y = player->plane_y * frame->move_speed;
	
	if (player->move_left)
	{
		if (can_move(map_objects, player->x + step_x, player->y))
			player->x += step_x;
		if (can_move(map_objects, player->x, player->y + step_y))
			player->y += step_y;
	}
}

void	move_right(t_player *player, t_map_objects *map_objects, t_frame *frame)
{
	double	step_x;
	double	step_y;

	step_x = -player->plane_x * frame->move_speed;
	step_y = -player->plane_y * frame->move_speed;
	
	if (player->move_right)
	{
		if (can_move(map_objects, player->x + step_x, player->y))
			player->x += step_x;
		if (can_move(map_objects, player->x, player->y + step_y))
			player->y += step_y;
	}
}

void	move_front(t_player *player, t_map_objects *map_objects, t_frame *frame)
{
	double	step_x;
	double	step_y;

	step_x = player->dir_x * frame->move_speed;
	step_y = player->dir_y * frame->move_speed;
	if (player->move_front)
	{
		if (can_move(map_objects, player->x + step_x, player->y))
			player->x += step_x;
		if (can_move(map_objects, player->x, player->y + step_y))
			player->y += step_y;
	}
}

void	move_back(t_player *player, t_map_objects *map_objects, t_frame *frame)
{
	double	step_x;
	double	step_y;

	step_x = -player->dir_x * frame->move_speed;
	step_y = -player->dir_y * frame->move_speed;
	if (player->move_back)
	{
		if (can_move(map_objects, player->x + step_x, player->y))
			player->x += step_x;
		if (can_move(map_objects, player->x, player->y + step_y))
			player->y += step_y;
	}
}

