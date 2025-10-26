/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:32:36 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/26 20:01:25 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int lerp(int a, int b, float t)
{
    return a + (int)((b - a) * t);
}

static int gradient_brown(float t)
{
    // Dark → light brown
    int r = lerp(60, 160, t);
    int g = lerp(35, 110, t);
    int b = lerp(20, 60, t);
    return create_rgb(r, g, b);
}

void draw_border(t_image *img, int x, int y, int w, int h, int border)
{
    for (int i = 0; i < border; i++)
    {
        float t = (float)i / (float)(border - 1);  // 0 → 1
        int color = gradient_brown(t);

        // Top border
        for (int px = x; px < x + w; px++)
            put_pixel_img(img, px, y + i, color);

        // Bottom border
        for (int px = x; px < x + w; px++)
            put_pixel_img(img, px, y + h - i - 1, color);

        // Left border
        for (int py = y; py < y + h; py++)
            put_pixel_img(img, x + i, py, color);

        // Right border
        for (int py = y; py < y + h; py++)
            put_pixel_img(img, x + w - i - 1, py, color);
    }
}

void	create_full_map(t_map *full_map, t_map_objects *map_objs)
{
	(void)map_objs;
	new_image(&full_map->map, game()->game_height * 0.8, 
		game()->game_height * 0.8);
	full_map->y = game()->game_height / 2 - full_map->map.h / 2;
	full_map->x = game()->game_width / 2 - full_map->map.w / 2;
	draw_border(&full_map->map, 0, 0, full_map->map.w, full_map->map.h, full_map->map.h * 0.05);
}

void	create_minimap(t_map *minimap)
{
	new_image(&minimap->map, game()->game_height * 0.2, 
		game()->game_height * 0.2);
	minimap->y = game()->game_height * 0.025;
	minimap->x = minimap->y;
	draw_border(&minimap->map, 0, 0, minimap->map.w, minimap->map.h, minimap->map.h * 0.05);
}



// void	apply_player_position()
// {

// }

// void	update_minimap(t_map *minimap, t_map *full_map)
// {
	
// }
