/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:22:44 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 17:50:00 by rafasant         ###   ########.fr       */
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
	raycaster();
	render_hud(screens());
	mlx_put_image_to_window(game()->mlx, game()->win, screens()->canva.img_ptr, game()->image_x, game()->image_y);
}