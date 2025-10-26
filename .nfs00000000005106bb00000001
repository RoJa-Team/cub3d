/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:46:43 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/25 18:29:13 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	struct	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1e6);
}

void	get_speed_modifiers(void)
{
	double	old_time;
	double	time;
	double	frame_time;

	time = 0.0;
	old_time = time;
	time = get_time();
	frame_time = (time - old_time) / 1e3;
	printf("FPS %f\n", (1.0 / frame_time));
	frame()->move_speed = frame_time * 5.0;
	frame()->rot_speed = frame_time * 3.0;
}

void	turn_left(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player()->dir_x;
	player()->dir_x = player()->dir_x * cos(frame()->rot_speed) 
		- player()->dir_y * sin(frame()->rot_speed);
	player()->dir_y = old_dir_x * sin (frame()->rot_speed) 
		+ player()->dir_y * cos(frame()->rot_speed);
	old_plane_x = player()->plane_x;
	player()->plane_x = player()->plane_x * cos(frame()->rot_speed)
		- player()->plane_y * sin(frame()->rot_speed);
	player()->plane_y = old_plane_x * sin(frame()->rot_speed)
		+ player()->plane_y * cos(frame()->rot_speed);

}

void	turn_right(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player()->dir_x;
	player()->dir_x = player()->dir_x * cos(-frame()->rot_speed) 
		- player()->dir_y * sin(-frame()->rot_speed);
	player()->dir_y = old_dir_x * sin (-frame()->rot_speed) 
		+ player()->dir_y * cos(-frame()->rot_speed);
	old_plane_x = player()->plane_x;
	player()->plane_x = player()->plane_x * cos(-frame()->rot_speed)
		- player()->plane_y * cos (-frame()->rot_speed);
	player()->plane_y = old_plane_x * sin(-frame()->rot_speed)
		+ player()->plane_y * cos(-frame()->rot_speed);
}
void	move_front(void)
{
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x 
		+ player()->dir_x * frame()->move_speed)] != '1')
		player()->x += player()->dir_x * frame()->move_speed;
	if (map_objects()->map[(int)(player()->y + player()->dir_y 
		* frame()->move_speed)][(int)(player()->x)] != '1')
		player()->y += player()->dir_y * frame()->move_speed;
}
void	move_left(void)
{
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x 
		- player()->dir_y * frame()->move_speed)] != '1')
		player()->x -= player()->dir_y * frame()->move_speed;
	if (map_objects()->map[(int)(player()->y - player()->dir_x 
		* frame()->move_speed)][(int)(player()->x)] != '1')
		player()->y -= player()->dir_x * frame()->move_speed;

}
void	move_back(void)
{
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x 
		+ player()->dir_x * frame()->move_speed)] != '1')
		player()->x -= player()->dir_x * frame()->move_speed;
	if (map_objects()->map[(int)(player()->y + player()->dir_y 
		* frame()->move_speed)][(int)(player()->x)] != '1')
		player()->y -= player()->dir_y * frame()->move_speed;

}
void	move_right(void)
{
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x 
		+ player()->dir_y * frame()->move_speed)] != '1')
		player()->x += player()->dir_y * frame()->move_speed;
	if (map_objects()->map[(int)(player()->y + player()->dir_x 
		* frame()->move_speed)][(int)(player()->x)] != '1')
		player()->y += player()->dir_x * frame()->move_speed;

}
