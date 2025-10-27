/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:32:36 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/27 22:52:02 by rafasant         ###   ########.fr       */
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
	float cell_x = (float)full_map->map_w / (float)map_objs->map_width;
	float cell_y = (float)full_map->map_h / (float)map_objs->map_height;
	float cell = (cell_x < cell_y) ? cell_x : cell_y;
	return cell;
}

int	get_cell_colour(char cell)
{
	if (cell == '1')
		return (0x00404040);
	else if (cell == '0')
		return (0x00A0A0A0);
	else if (cell == ' ')
		return (0x00E0E0E0);
	else
		return (0x00FF00FF);
}

// int	handle_transparency(int colour)
// {

// }


int	normalize_map_size(t_map *full_map, t_map_objects *map_objs, int cell)
{
	float	result;
	float	normalization_factor;
	int		zoom;

	zoom = map_objs->map_width;
	if (map_objs->map_width < 20)
		zoom = 20;
	normalization_factor = zoom / log(full_map->map_w + 1.0);
	if (cell >= 0)
		result = logf(cell + 1.0f) * normalization_factor;
	else
		result = -logf(-cell + 1.0f) * normalization_factor;
	return ((int)result);
}

void    draw_full_map(t_map *full_map, t_map_objects *map_objs)
{
	int	i;
	int	j;
    int x;
    int y;
	int	c_y;
	int	c_x;
	int	cell;
	
	cell = calc_cell_size(full_map, map_objs);
	cell = normalize_map_size(full_map, map_objs, cell);
    i = 0;
	y = full_map->border;
    while (map_objs->map[i] != NULL)
    {
        j = 0;
		x = full_map->border;
        while (map_objs->map[i][j] != '\0' && map_objs->map[i][j] != '\n')
        {
			c_y = 0;
			while (c_y <= cell / 2)
			{
				c_x = 0;
				while (c_x < cell)
				{
					put_pixel_img(&full_map->map, x + c_x, y + c_y, get_cell_colour(map_objs->map[i][j]));
					put_pixel_img(&full_map->map, x + c_x, y + cell - c_y, get_cell_colour(map_objs->map[i][j]));
					c_x++;
				}
				c_y++;
			}
			x = x + cell;
            j++;
        }
		y = y + cell;
        i++;
    }
}

// void    draw_minimap(t_map *full_map, t_map_objects *map_objs)
// {
//     int x;
//     int y;

//     y = 0;
//     while (map_objs->map[y] != NULL)
//     {
//         x = 0;
//         while (map_objs->map[y][x] != '\0')
//         {

//             x++;
//         }
//         y++;
//     }
// }


void	create_full_map(t_map *full_map, t_map_objects *map_objs)
{
	new_image(&full_map->map, game()->game_height * 0.8, 
		game()->game_height * 0.8);
	full_map->y = game()->game_height / 2 - full_map->map.h / 2;
	full_map->x = game()->game_width / 2 - full_map->map.w / 2;
    full_map->border = full_map->map.h * 0.05;
	full_map->map_w = full_map->map.w - full_map->border * 2;
	full_map->map_h = full_map->map_w;
	draw_border(&full_map->map, 0, 0, full_map->border);
	(void)map_objs;
    draw_full_map(full_map, map_objs);
}

void	create_minimap(t_map *minimap, t_map_objects *map_objs)
{
	new_image(&minimap->map, game()->game_height * 0.2, 
		game()->game_height * 0.2);
	minimap->y = game()->game_height * 0.025;
	minimap->x = minimap->y;
	minimap->border = minimap->map.h * 0.05;
	draw_border(&minimap->map, 0, 0, minimap->border);
	(void)map_objs;
    // draw_minimap(minimap, map_objs);
}



// void	apply_player_position()
// {

// }

// void	update_minimap(t_map *minimap, t_map *full_map)
// {
	
// }
