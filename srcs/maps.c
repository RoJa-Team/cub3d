/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:32:36 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/12 23:34:43 by rafasant         ###   ########.fr       */
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

void	draw_border(t_image *img, int x, int y, int border)
{
	int		i;
	int		init;
	int		color;
	float	t;

	i = 0;
	while (i < border)
	{
		t = (float)i / (float)(border - 1);
		color = gradient_brown(t);
		init = x - 1;
		while (++init <= x + img->w)
		{
			put_pixel_img(img, init, y + i, color);
			put_pixel_img(img, init, y + img->h - i, color);
		}
		init = y - 1;
		while (++init <= y + img->h)
		{
			put_pixel_img(img, x + i, init, color);
			put_pixel_img(img, x + img->w - i, init, color);
		}
		i++;
	}
}

float	calc_cell_size(t_map *full_map, t_map_objects *map_objs)
{
	float	cell_x;
	float	cell_y;
	float	cell;

	cell_x = (float)full_map->map_w / (float)map_objs->map_width;
	cell_y = (float)full_map->map_h / (float)map_objs->map_height;
	if (cell_x < cell_y)
		cell = cell_x;
	else
		cell = cell_y;
	return cell;
}

int	get_cell_colour(char cell)
{
	if (cell == '1')
		return (MAP_WALL);
	else if (cell == '0')
		return (MAP_FLOOR);
	else if (cell == ' ')
		return (MAP_EMPTY);
	else if (cell == 'F')
		return (MAP_FIRE);
	return (MAP_FLOOR);
}

// int	handle_transparency(int colour)
// {

// }


// int	normalize_map_size(t_map *full_map, t_map_objects *map_objs, int cell)
// {
// 	float	result;
// 	float	normalization_factor;
// 	int		zoom;

// 	zoom = map_objs->map_width;
// 	if (map_objs->map_width < 20)
// 		zoom = 20;
// 	normalization_factor = zoom / log(full_map->map_w + 1.0);
// 	if (cell >= 0)
// 		result = logf(cell + 1.0f) * normalization_factor;
// 	else
// 		result = -logf(-cell + 1.0f) * normalization_factor;
// 	return ((int)result);
// }

void    draw_full_map(t_map *full_map, t_map_objects *map_objs)
{
	int	i;
	int	j;
    int x;
    int y;
	int	c_y;
	int	c_x;
	
    i = 0;
	y = full_map->border;
    while (map_objs->map[i] != NULL)
    {
        j = 0;
		x = full_map->border;
        while (map_objs->map[i][j] != '\0' && map_objs->map[i][j] != '\n')
        {
			c_y = 0;
			while (c_y <= full_map->cell_size / 2)
			{
				c_x = 0;
				while (c_x < full_map->cell_size)
				{
					put_pixel_img(&full_map->map, x + c_x, y + c_y, get_cell_colour(map_objs->map[i][j]));
					put_pixel_img(&full_map->map, x + c_x, y + full_map->cell_size - c_y, get_cell_colour(map_objs->map[i][j]));
					c_x++;
				}
				c_y++;
			}
			x = x + full_map->cell_size;
            j++;
        }
		y = y + full_map->cell_size;
        i++;
    }
}

void	apply_player_position(t_map *full_map, t_player *player)
{
	int	c_y;
	int	c_x;
	
	c_y = full_map->cell_size / 4;
	while (c_y <= full_map->cell_size / 2)
	{
		c_x = full_map->cell_size / 2;
		while (c_x < full_map->cell_size)
		{
			put_pixel_img(&full_map->map, player->x * full_map->cell_size + full_map->border - full_map->cell_size / 2 + c_x, player->y * full_map->cell_size + full_map->border - full_map->cell_size / 2 + c_y, MAP_PLAYER);
			put_pixel_img(&full_map->map, player->x * full_map->cell_size + full_map->border - full_map->cell_size / 2 + c_x, player->y * full_map->cell_size + full_map->border - full_map->cell_size / 2 + full_map->cell_size - c_y, MAP_PLAYER);
			c_x++;
		}
		c_y++;
	}
}

void	create_full_map(t_map *full_map, t_map_objects *map_objs, t_player *player)
{
	new_image(&full_map->map, game()->game_height * 0.8, 
		game()->game_height * 0.8);
	full_map->y = game()->game_height / 2 - full_map->map.h / 2;
	full_map->x = game()->game_width / 2 - full_map->map.w / 2;
    full_map->border = full_map->map.h * 0.05;
	full_map->map_w = full_map->map.w - full_map->border * 2;
	full_map->map_h = full_map->map_w;
	draw_border(&full_map->map, 0, 0, full_map->border);
	full_map->cell_size = calc_cell_size(full_map, map_objs);
    draw_full_map(full_map, map_objs);
	apply_player_position(full_map, player);
}

void	update_full_map(t_map *full_map, t_map_objects *map_objs, t_player *player)
{
	draw_full_map(full_map, map_objs);
	apply_player_position(full_map, player);
}

void    draw_minimap(t_map *minimap, t_map_objects *map_objs, t_player *player)
{	
	int	i;
	int	j;
    int x;
    int y;
	int	c_y;
	int	c_x;

	int	offset_y_up = 0;
	int	offset_y_down = 0;
	int	offset_x_left = 0;
	int	offset_x_right = 0;
	int max_i = 0;
	int max_j = 0;
	int	init_j = 0;

	i = player->y - MINIMAP_RADIUS;
	if (i < 0)
	{
		offset_y_up = -i;
	}
	max_i = player->y + MINIMAP_RADIUS;
	if (max_i >= map_objs->map_height)
	{
		offset_y_down = max_i - map_objs->map_height;
	}
	if (i - offset_y_down >= 0)
		i = i - offset_y_down;
	if (max_i + offset_y_up < map_objs->map_height)
		max_i = max_i + offset_y_up;

	j = player->x - MINIMAP_RADIUS;
	if (j < 0)
	{
		offset_x_left = -j;
	}
	max_j = player->x + MINIMAP_RADIUS;
	if (max_j >= map_objs->map_width)
	{
		offset_x_right = max_j - map_objs->map_width;
	}
	if (j - offset_x_left >= 0)
		j = j - offset_x_left;
	if (max_j + offset_x_right < map_objs->map_width)
		max_j = max_j + offset_x_right;
	if (i < 0)
		i = 0;
	if (max_i >= map_objs->map_height)
		max_i = map_objs->map_height;
	if (j < 0)
		j = 0;
	if (max_j >= map_objs->map_width)
		max_j = map_objs->map_width;
	init_j = j;
	y = minimap->border;
	debug("i", i);
	debug("init_j", j);
	while (i != max_i)
	{
		j = init_j;
		x = minimap->border;
		while (j != max_j)
		{
			c_y = 0;
			while (c_y <= minimap->cell_size / 2)
			{
				c_x = 0;
				while (c_x < minimap->cell_size)
				{
					put_pixel_img(&minimap->map, x + (minimap->cell_size / 2) + c_x, y + (minimap->cell_size / 2) + c_y, get_cell_colour(map_objs->map[i][j]));
					put_pixel_img(&minimap->map, x + (minimap->cell_size / 2) + c_x, y - (minimap->cell_size / 2) + minimap->cell_size - c_y, get_cell_colour(map_objs->map[i][j]));
					c_x++;
				}
				c_y++;
			}
			x = x + minimap->cell_size;
            j++;
		}
		y = y + minimap->cell_size;
		i++;
	}

	// c_y = minimap->cell_size / 4;
	// while (c_y <= minimap->cell_size / 2)
	// {
	// 	c_x = minimap->cell_size / 2;
	// 	while (c_x < minimap->cell_size)
	// 	{
	// 		put_pixel_img(&minimap->map, player->x * minimap->cell_size + minimap->border - minimap->cell_size / 2 + c_x, player->y * minimap->cell_size + minimap->border - minimap->cell_size / 2 + c_y, MAP_PLAYER);
	// 		put_pixel_img(&minimap->map, player->x * minimap->cell_size + minimap->border - minimap->cell_size / 2 + c_x, player->y * minimap->cell_size + minimap->border - minimap->cell_size / 2 + minimap->cell_size - c_y, MAP_PLAYER);
	// 		c_x++;
	// 	}
	// 	c_y++;
	// }

	// int	offset_y = 0;
	// int	offset_x = 0;
	// i = player->y - MINIMAP_RADIUS;
	// if (i < 0)
	// {
	// 	offset_y = -i;
	// }
	// max_i = player->y + MINIMAP_RADIUS + offset_y;
	// if (max_i > map_objs->map_height)
	// {
	// 	offset_y = max_i - map_objs->map_height;
	// 	max_i = map_objs->map_height;
	// }
	// init_j = player->x - MINIMAP_RADIUS;
	// if (init_j < 0)
	// {
	// 	offset_x = -init_j;
	// 	init_j = 0;
	// }
	// max_j = player->x + MINIMAP_RADIUS + offset_x;
	// if (max_j > map_objs->map_width)
	// {
	// 	offset_x = map_objs->map_width - max_j;
	// 	max_j = map_objs->map_width;
	// }
	// y = minimap->border;
	// while (i != max_i)
	// {
	// 	j = init_j;
	// 	x = minimap->border;
	// 	while (j != max_j)
	// 	{
	// 		c_y = 0;
	// 		while (c_y <= minimap->cell_size / 2)
	// 		{
	// 			c_x = 0;
	// 			while (c_x < minimap->cell_size)
	// 			{
	// 				put_pixel_img(&minimap->map, x + (offset_x * minimap->cell_size / 2) + c_x, y + (offset_y * minimap->cell_size / 2) + c_y, get_cell_colour(map_objs->map[i][j]));
	// 				put_pixel_img(&minimap->map, x + (offset_x * minimap->cell_size / 2) + c_x, y - (offset_y * minimap->cell_size / 2) + minimap->cell_size - c_y, get_cell_colour(map_objs->map[i][j]));
	// 				c_x++;
	// 			}
	// 			c_y++;
	// 		}
	// 		x = x + minimap->cell_size;
    //         j++;
	// 	}
	// 	y = y + minimap->cell_size;
	// 	i++;
	// }

	// c_y = minimap->cell_size / 4;
	// while (c_y <= minimap->cell_size / 2)
	// {
	// 	c_x = minimap->cell_size / 2;
	// 	while (c_x < minimap->cell_size)
	// 	{
	// 		put_pixel_img(&minimap->map, (player->x * minimap->cell_size + minimap->border - minimap->cell_size / 2 + c_x) - (offset_x * minimap->cell_size), (player->y * minimap->cell_size + minimap->border - minimap->cell_size / 2 + c_y) - (offset_y * minimap->cell_size), MAP_PLAYER);
	// 		put_pixel_img(&minimap->map, (player->x * minimap->cell_size + minimap->border - minimap->cell_size / 2 + c_x) - (offset_x * minimap->cell_size), (player->y * minimap->cell_size + minimap->border - minimap->cell_size / 2 + minimap->cell_size - c_y) - (offset_y * minimap->cell_size), MAP_PLAYER);
	// 		c_x++;
	// 	}
	// 	c_y++;
	// }
}

void	calc_minimap_area(t_map *minimap, t_map_objects *map_objs, t_player *player)
{
	int	map_x;
	int	final_x;
	int map_y;
	int	final_y;

	map_x = player->x - MINIMAP_RADIUS;
	final_x = player->x + MINIMAP_RADIUS;
	map_y = player->y - MINIMAP_RADIUS;
	final_y = player->y + MINIMAP_RADIUS;
	if (map_y < 0)
	{
		final_y = final_y + -map_y;
		map_y = 0;
	}
	else if (final_y > map_objs->map_height)
	{
		map_y = map_y - (final_y - map_objs->map_height);
		final_y = map_objs->map_height;
	}
	if (map_x < 0)
	{
		final_x = final_x + -map_x;
		map_x = 0;
	}
	else if (final_x > map_objs->map_width)
	{
		map_x = map_x - (final_x - map_objs->map_width);
		final_x = map_objs->map_width;
	}

	int	i;
	int	j;
    int x;
    int y;
	int	c_y;
	int	c_x;
	
    i = map_y;
	y = minimap->border;
	while (i < final_y)
	{
		j = map_x;
		x = minimap->border;
		while (j < final_x)
		{
			c_y = 0;
			while (c_y <= minimap->cell_size / 2)
			{
				c_x = 0;
				while (c_x < minimap->cell_size)
				{
					put_pixel_img(&minimap->map, x + c_x, y + c_y, get_cell_colour(map_objs->map[i][j]));
					put_pixel_img(&minimap->map, x + c_x, y + minimap->cell_size - c_y, get_cell_colour(map_objs->map[i][j]));
					c_x++;
				}
				c_y++;
			}
			x = x + minimap->cell_size;
			j++;
		}
		y = y + minimap->cell_size;
		i++;
	}
}

float	calc_minimap_cell_size(t_map *minimap, t_map_objects *map_objs)
{
	int		radius;
	float	cell_x;
	float	cell_y;
	float	cell;

	radius = MINIMAP_RADIUS;
    if (map_objs->map_width < radius)
		radius = map_objs->map_width;
	if (map_objs->map_height < radius)
		radius = map_objs->map_height;
	cell_x = (float)minimap->map_w / (radius * 2);
	cell_y = (float)minimap->map_h / (radius * 2);
	if (cell_x < cell_y)
		cell = cell_x;
	else
		cell = cell_y;
	debug("cell", cell);
	return cell;
}

void	create_minimap(t_map *minimap, t_map_objects *map_objs, t_player *player)
{
	new_image(&minimap->map, game()->game_height * 0.2, 
		game()->game_height * 0.2);
	minimap->y = game()->game_height * 0.025;
	minimap->x = minimap->y;
	minimap->border = minimap->map.h * 0.05;
	minimap->map_w = minimap->map.w - minimap->border * 2;
	minimap->map_h = minimap->map_w;
	draw_border(&minimap->map, 0, 0, minimap->border);
	minimap->cell_size = calc_minimap_cell_size(minimap, map_objs);
    draw_minimap(minimap, map_objs, player);
	// apply_player_position(minimap, player);
}

void	update_minimap(t_map *minimap, t_map_objects *map_objs, t_player *player)
{
	draw_minimap(minimap, map_objs, player);
	// apply_player_position(minimap, player);
}
