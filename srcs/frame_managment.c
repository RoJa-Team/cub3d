/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:46:43 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/26 16:53:29 by joafern2         ###   ########.fr       */
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
	//printf("FPS %f\n", (1.0 / frame_time));
	//frame()->move_speed = frame_time * 5.0;
	frame()->move_speed = 0.3;
	frame()->rot_speed = frame_time * 0.7;
	if (frame()->rot_speed > 0.05)
		frame()->rot_speed = 0.05;
}

void	turn_left(void)
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
		- player()->plane_y * sin(-frame()->rot_speed);
	player()->plane_y = old_plane_x * sin(-frame()->rot_speed)
		+ player()->plane_y * cos(-frame()->rot_speed);
}

void	turn_right(void)
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
void	move_front(void)
{
	int	sign_x;
	int	sign_y;
	double	step_x = player()->dir_x * frame()->move_speed;
	double	step_y = player()->dir_y * frame()->move_speed;

	sign_x = (step_x > 0);
	if (sign_x == 0)
		sign_x = -1;
	sign_y = (step_y > 0);
	if (sign_y == 0)
		sign_y = -1;
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x + step_x + sign_x * MARGIN)] != '1')
		player()->x += step_x;
	if (map_objects()->map[(int)(player()->y + step_y + sign_y * MARGIN)][(int)(player()->x)] != '1')
		player()->y += step_y;;

}
void	move_left(void)
{
	int	sign_x;
	int	sign_y;
	double	step_x = player()->dir_y * frame()->move_speed;
	double	step_y = -player()->dir_x * frame()->move_speed;

	sign_x = (step_x > 0);
	if (sign_x == 0)
		sign_x = -1;
	sign_y = (step_y > 0);
	if (sign_y == 0)
		sign_y = -1;
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x + step_x + sign_x * MARGIN)] != '1')
		player()->x += step_x;
	if (map_objects()->map[(int)(player()->y + step_y + sign_y * MARGIN)][(int)(player()->x)] != '1')
		player()->y += step_y;;


}
void	move_back(void)
{
	int	sign_x;
	int	sign_y;
	double	step_x = -player()->dir_x * frame()->move_speed;
	double	step_y = -player()->dir_y * frame()->move_speed;

	sign_x = (step_x > 0);
	if (sign_x == 0)
		sign_x = -1;
	sign_y = (step_y > 0);
	if (sign_y == 0)
		sign_y = -1;
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x + step_x + sign_x * MARGIN)] != '1')
		player()->x += step_x;
	if (map_objects()->map[(int)(player()->y + step_y + sign_y * MARGIN)][(int)(player()->x)] != '1')
		player()->y += step_y;;
}
void	move_right(void)
{
	int	sign_x;
	int	sign_y;
	double	step_x = -player()->dir_y * frame()->move_speed;
	double	step_y = player()->dir_x * frame()->move_speed;

	sign_x = (step_x > 0);
	if (sign_x == 0)
		sign_x = -1;
	sign_y = (step_y > 0);
	if (sign_y == 0)
		sign_y = -1;
	if (map_objects()->map[(int)(player()->y)][(int)(player()->x + step_x + sign_x * MARGIN)] != '1')
		player()->x += step_x;
	if (map_objects()->map[(int)(player()->y + step_y + sign_y * MARGIN)][(int)(player()->x)] != '1')
		player()->y += step_y;;
}
