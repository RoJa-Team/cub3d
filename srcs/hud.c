/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:25:44 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 19:47:19 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_hose(t_hose *hose)
{
	hose->curr_hose = textures()->hose_idle.img;
	hose->x = (game()->game_width / 2) - (hose->curr_hose.w / 2);
	hose->y = game()->game_height - hose->curr_hose.h;
	hose->on = false;
}

// void	update_hose(t_hud *hose)
// {

// }

void	render_hud(t_screens *screens)
{
	put_img_to_img(&screens->canva, &screens->hud.hose.curr_hose, 
		screens->hud.hose.x, screens->hud.hose.y);
	if (game()->open_map == true)
		put_img_to_img(&screens->canva, &screens->hud.full_map.map, 
		screens->hud.full_map.x, screens->hud.full_map.y);
	else
		put_img_to_img(&screens->canva, &screens->hud.minimap.map, 
		screens->hud.minimap.x, screens->hud.minimap.y);
}