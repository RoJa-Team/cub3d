/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:32:36 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 19:45:08 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_full_map(t_map *full_map, t_map_objects *map_objs,
	t_player *player)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = full_map->map_y;
	while (map_objs->map[i] != NULL)
	{
		j = 0;
		x = full_map->map_x;
		while (map_objs->map[i][j] != '\0' && map_objs->map[i][j] != '\n')
		{
			draw_cell(full_map, x, y, get_cell_colour(map_objs->map[i][j]));
			x = x + full_map->cell;
			j++;
		}
		y = y + full_map->cell;
		i++;
	}
	x = full_map->map_x + (player->x * full_map->cell) - full_map->cell / 4;
	y = full_map->map_y + (player->y * full_map->cell) - full_map->cell / 4;
	draw_player(full_map, x, y, MAP_PLAYER);
}

void	draw_map_background(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y <= map->map_h)
	{
		x = 0;
		while (x <= map->map_w)
		{
			put_pixel_img(&map->map, x + map->border, y + map->border,
				MAP_WALL);
			put_pixel_img(&map->map, x + map->border,
				map->map_h - y + map->border, MAP_WALL);
			x++;
		}
		y++;
	}
}

void	create_full_map(t_map *full_map, t_map_objects *map_objs,
	t_player *player)
{
	new_image(&full_map->map, game()->game_height * 0.8,
		game()->game_height * 0.8);
	full_map->y = game()->game_height / 2 - full_map->map.h / 2;
	full_map->x = game()->game_width / 2 - full_map->map.w / 2;
	full_map->border = full_map->map.h * 0.05;
	full_map->map_w = full_map->map.w - full_map->border * 2;
	full_map->map_h = full_map->map_w;
	draw_border(&full_map->map, 0, 0, full_map->border);
	full_map->cell = calc_cell_size(full_map->map_w, full_map->map_h,
			map_objs->map_width, map_objs->map_height);
	draw_map_background(full_map);
	full_map->map_x = full_map->border
		+ ((full_map->map_w - (map_objs->map_width * full_map->cell)) / 2);
	full_map->map_y = full_map->border
		+ ((full_map->map_h - (map_objs->map_height * full_map->cell)) / 2);
	draw_full_map(full_map, map_objs, player);
}
