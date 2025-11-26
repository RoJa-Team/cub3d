/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:22:44 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/15 15:37:09 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_image *canva, int game_width, int game_height)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	y = 0;
	while (y <= game_height / 2)
	{
		x = 0;
		while (x < game_width)
		{
			put_pixel(canva, x, y, ceiling);
			put_pixel(canva, x, game_height - y, floor);
			x++;
		}
		y++;
	}
}

void	render()
{
	render_background(&screens()->canva, game()->game_width, game()->game_height);
	animate_doors(map_objects()->doors, map_objects(), player(), frame()->frame_time);
	raycaster(game(), raycast(), player(), draw());
	get_speed_modifiers(frame());
	render_fire_sprites(game(), map_objects(), map_objects()->sprites, frame()->frame_time);
	render_hud(screens());
	mlx_put_image_to_window(game()->mlx, game()->win, screens()->canva.img_ptr, game()->image_x, game()->image_y);
	move_right(player(), map_objects(), frame());
	move_left(player(), map_objects(), frame());
	move_front(player(), map_objects(), frame());
	move_back(player(), map_objects(), frame());
	turn_right(player(), frame());
	turn_left(player(), frame());
}
