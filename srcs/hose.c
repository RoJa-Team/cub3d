/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hose.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:43:17 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/19 22:18:15 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_hose(t_hose *hose)
{
	static int	frame;

	if (hose->on == true)
	{
		if (frame > 11)
			frame = frame - 7;
		if (frame < 4)
			hose->curr_hose = textures()->hose_start[frame].img;
		else if (frame > 3)
			hose->curr_hose = textures()->hose_on[frame - 4].img;
		frame++;
	}
	else if (hose->on == false && frame != 0)
	{
		if (frame < 4)
		{
			frame = 0;
			return ;
		}
		hose->curr_hose = textures()->hose_end[frame - 4].img;
		frame--;
	}
	else if (hose->on == false && frame == 0)
		hose->curr_hose = textures()->hose_idle.img;
}

void	create_hose(t_hose *hose)
{
	hose->curr_hose = textures()->hose_idle.img;
	hose->x = (game()->game_width / 2) - (hose->curr_hose.w / 2);
	hose->y = game()->game_height - hose->curr_hose.h;
	hose->on = false;
}