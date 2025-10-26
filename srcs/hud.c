/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:25:44 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 18:04:48 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_hose(t_hud *hose)
{
	hose->x = (game()->game_width / 2) - (textures()->hose_idle.img.w / 2);
	hose->y = game()->game_height - textures()->hose_idle.img.h;
	hose->img = textures()->hose_idle.img;
}

// void	update_hose(t_hud *hose)
// {

// }

void	create_minimap(t_hud *minimap)
{
	minimap->x = 0.025 * game()->game_width;
	minimap->y = 0.025 * game()->game_width;
	new_image(&minimap->img, game()->game_width * 0.125, game()->game_width * 0.125);
}

// void	update_minimap(t_hud *minimap)
// {
	
// }

void	render_hud(t_screens *screens)
{
	put_img_to_img(&screens->canva, &screens->minimap.img, screens->minimap.x, screens->minimap.y);
	put_img_to_img(&screens->canva, &screens->hose.img, screens->hose.x, screens->hose.y);
}