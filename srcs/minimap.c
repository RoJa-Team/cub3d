/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:33:30 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 19:45:08 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_map *minimap, t_map_objects *map_objs, t_player *player)
{
	t_helper	h;

	h.i = minimap->offsets.start_y;
	h.y = minimap->map_y;
	while (h.i < minimap->offsets.end_y)
	{
		h.j = minimap->offsets.start_x;
		h.x = minimap->map_x;
		while (h.j < minimap->offsets.end_x)
		{
			draw_cell(minimap, h.x, h.y,
				get_cell_colour(map_objs->map[h.i][h.j]));
			h.x = h.x + minimap->cell;
			h.j++;
		}
		h.y = h.y + minimap->cell;
		h.i++;
	}
	h.x = minimap->map_x + ((player->x - minimap->offsets.start_x) * \
minimap->cell - minimap->cell / 4);
	h.y = minimap->map_y + ((player->y - minimap->offsets.start_y) * \
minimap->cell - minimap->cell / 4);
	draw_player(minimap, h.x, h.y, MAP_PLAYER);
}

void	calc_minimap_offsets(t_offsets *offsets, t_map_objects *mo,
	t_player *player)
{
	offsets->start_y = (int)floor(player->y - offsets->radius - 0.5);
	offsets->end_y = (int)floor(player->y + offsets->radius + 0.5);
	if (offsets->start_y < 0)
		offsets->end_y = offsets->end_y + (-offsets->start_y);
	if (offsets->end_y > mo->map_height)
	{
		offsets->start_y = offsets->start_y - (offsets->end_y - mo->map_height);
	}
	if (offsets->start_y < 0)
		offsets->start_y = 0;
	if (offsets->end_y > mo->map_height)
		offsets->end_y = mo->map_height;
	offsets->start_x = (int)floor(player->x - offsets->radius - 0.5);
	offsets->end_x = (int)floor(player->x + offsets->radius + 0.5);
	if (offsets->start_x < 0)
		offsets->end_x = offsets->end_x + (-offsets->start_x);
	if (offsets->end_x > mo->map_width)
	{
		offsets->start_x = offsets->start_x - (offsets->end_x - mo->map_width);
	}
	if (offsets->start_x < 0)
		offsets->start_x = 0;
	if (offsets->end_x > mo->map_width)
		offsets->end_x = mo->map_width;
}

void	create_minimap(t_map *minimap, t_map_objects *map_objs,
	t_player *player)
{
	new_image(&minimap->map, game()->game_height * 0.2,
		game()->game_height * 0.2);
	minimap->y = game()->game_height * 0.025;
	minimap->x = minimap->y;
	minimap->border = minimap->map.h * 0.05;
	minimap->map_w = minimap->map.w - minimap->border * 2;
	minimap->map_h = minimap->map_w;
	draw_border(&minimap->map, 0, 0, minimap->border);
	minimap->offsets.radius = MINIMAP_RADIUS;
	if (minimap->offsets.radius < 1)
		minimap->offsets.radius = 1;
	calc_minimap_offsets(&minimap->offsets, map_objs, player);
	minimap->cell = minimap->map_w / (minimap->offsets.radius * 2 + 1);
	minimap->map_x = minimap->border + ((minimap->map_w - \
((minimap->offsets.end_x - minimap->offsets.start_x) * \
minimap->cell)) / 2);
	minimap->map_y = minimap->border + ((minimap->map_h - \
((minimap->offsets.end_y - minimap->offsets.start_y) * \
minimap->cell)) / 2);
	draw_minimap(minimap, map_objs, player);
}
