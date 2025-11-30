/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hose.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:43:17 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/24 21:44:53 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_flame(t_hose *hose, t_map_objects *mo, /*t_textures *textures,*/ int frame)
{
	int	i;

	if (hose->on == true && hose->power != true && frame > 3)
		hose->power = true;
	else if (hose->on == false && hose->power != false && frame < 8)
		hose->power = false;
	i = 0;
	while (i < mo->sprite_count)
	{
		if (hose->power == true && fabs(player()->x - mo->sprites[i].x) < 1.5 && fabs(player()->y - mo->sprites[i].y) < 1.5 && mo->sprites[i].dissip == 0)
			mo->sprites[i].dissip = 1;
		i++;
	}
}

void	update_hose(t_hose *h, t_textures *textures, double delta)
{
	h->frame_time += delta;
	if (h->on == true)
	{
		if (h->frame > 11)
			h->frame = h->frame - 7;
		if (h->frame < 4)
			h->curr_hose = textures->hose_start[h->frame].img;
		else if (h->frame > 3)
			h->curr_hose = textures->hose_on[h->frame - 4].img;
		if (h->frame_time >= h->anim_speed)
		{
			h->frame_time = 0.0;
			h->frame++;
		}	
	}
	else if (h->on == false && h->frame != 0)
	{
		if (h->frame < 4)
		{
			h->frame = 0;
			h->curr_hose = textures->hose_idle.img;
			return ;
		}
		h->curr_hose = textures->hose_end[h->frame - 4].img;
		if (h->frame_time >= h->anim_speed)
		{
			h->frame_time = 0.0;
			h->frame--;
		}
	}
	check_flame(h, map_objects(), /*textures,*/ h->frame);
}

void	create_hose(t_hose *hose)
{
	player()->hose = hose;
	hose->curr_hose = textures()->hose_idle.img;
	hose->x = (game()->game_width / 2) - (hose->curr_hose.w / 2);
	hose->y = game()->game_height - hose->curr_hose.h;
	hose->on = false;
	hose->frame = 0;
	hose->frame_time = 0;
	hose->anim_speed = 0.066;
}