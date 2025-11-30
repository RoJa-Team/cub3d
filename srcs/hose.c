/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hose.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:43:17 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 14:54:36 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_flame(t_hose *hose, t_map_objects *mo, int frame)
{
	int	i;

	if (hose->on == true && hose->power != true && frame > 3)
		hose->power = true;
	else if (hose->on == false && hose->power != false && frame < 8)
		hose->power = false;
	i = 0;
	while (i < mo->sprite_count)
	{
		if (hose->power == true && fabs(player()->x - mo->sprites[i].x) < 1.5
			&& fabs(player()->y - mo->sprites[i].y) < 1.5
			&& mo->sprites[i].dissip == 0)
			mo->sprites[i].dissip = 1;
		i++;
	}
}

void	update_hose(t_hose *hose, t_textures *textures)
{
	static int	frame;

	if (hose->on == true)
	{
		if (frame > 11)
			frame = frame - 7;
		if (frame < 4)
			hose->curr_hose = textures->hose_start[frame].img;
		else if (frame > 3)
			hose->curr_hose = textures->hose_on[frame - 4].img;
		frame++;
	}
	else if (hose->on == false && frame != 0)
	{
		if (frame < 4)
		{
			frame = 0;
			hose->curr_hose = textures->hose_idle.img;
			return ;
		}
		hose->curr_hose = textures->hose_end[frame - 4].img;
		frame--;
	}
	check_flame(hose, map_objects(), frame);
}

void	create_hose(t_hose *hose)
{
	player()->hose = hose;
	hose->curr_hose = textures()->hose_idle.img;
	hose->x = (game()->game_width / 2) - (hose->curr_hose.w / 2);
	hose->y = game()->game_height - hose->curr_hose.h;
	hose->on = false;
}
