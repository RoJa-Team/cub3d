/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:02:51 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/15 18:32:20 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_cell_size(float width1, float height1, float width2, float height2)
{
	float	cell_x;
	float	cell_y;
	float	cell;

	cell_x = width1 / width2;
	cell_y = height1 / height2;
	if (cell_x < cell_y)
		cell = cell_x;
	else
		cell = cell_y;
	return cell;
}

int	get_cell_colour(char cell)
{
	if (cell == '0')
		return (MAP_FLOOR);
	else if (cell == '1')
		return (MAP_WALL);
	else if (cell == 'F')
		return (MAP_FIRE);
	else if (cell == 'D')
		return (MAP_DOOR);
	else if (cell != ' ')
		return (MAP_FLOOR);
	return (MAP_WALL);
}

void	draw_cell(t_map *map, int x, int y, int colour, int cell)
{
	int	c_x;
	int	c_y;
	
	c_y = 0;
	while (c_y <= cell / 2)
	{
		c_x = 0;
		while (c_x < cell)
		{
			put_pixel_img(&map->map, x + c_x, y + c_y, colour);
			put_pixel_img(&map->map, x + c_x, (y + cell) - c_y, colour);
			c_x++;
		}
		c_y++;
	}
}