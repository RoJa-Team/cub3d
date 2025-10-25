/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/25 21:15:48 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_canva(t_image *canva)
{
	new_image(canva, game()->game_width, game()->game_height);
}

void	create_start(t_image *start)
{
	new_image(start, game()->game_width, game()->game_height);
}

void	create_pause(t_image *pause)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	new_image(pause, game()->game_width, game()->game_height);
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel(pause, x, HEIGHT - y, floor);
			put_pixel(pause, x, y, ceiling);
		}
	}
}

void	create_death(t_image *death)
{
	new_image(death, game()->game_width, game()->game_height);
}

void	create_finish(t_image *finish)
{
	new_image(finish, game()->game_width, game()->game_height);
}
