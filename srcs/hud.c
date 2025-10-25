/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:25:44 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/25 21:28:24 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_hose(t_hud *hose)
{
	hose->x = (game()->game_width / 2) - (textures()->hose_idle.img.w / 2);
	hose->y = game()->game_height - textures()->hose_idle.img.h;
	hose->img = textures()->hose_idle.img;
}

void	create_minimap(t_hud *minimap)
{
	minimap->x = 0.05 * game()->game_width;
	minimap->y = 0.05 * game()->game_height;
	new_image(&minimap->img, game()->game_width * 0.1, game()->game_height * 0.1);
}

void	render_hud(t_screens *screens)
{
	put_img_to_img(&screens->canva, &screens->minimap, screens->minimap.x, screens->minimap.y);
	put_img_to_img(&screens->canva, &screens->hose, screens->hose.x, screens->hose.y);
}