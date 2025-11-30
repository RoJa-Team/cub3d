/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:46:43 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/26 20:28:34 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1e6);
}

void	get_speed_modifiers(t_frame *frame)
{
	static double	old_time = 0.0;
	double			time;
	double			frame_time;

	time = get_time();
	if (old_time == 0.0)
		old_time = time;
	frame_time = time - old_time;
	old_time = time;
	frame->frame_time = frame_time;
	frame->move_speed = frame_time * 5.0;
	frame->rot_speed = frame_time * 3.0;
}
