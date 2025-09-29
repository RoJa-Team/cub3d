/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/29 22:42:07 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_background()
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	new_image(&screen()->background, WIDTH, HEIGHT);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&game()->background, x, y, ceiling);
			else
				put_pixel(&game()->background, x, y, floor);
		}
	}
	// mlx_put_image_to_window(game()->mlx, game()->win, game()->background.img_ptr, 0, 0);
}

void	create_start()
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	new_image(&screen()->background, WIDTH, HEIGHT);
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel(&game()->background, x, HEIGHT - y, floor);
			put_pixel(&game()->background, x, y, ceiling);
		}
	}
	// mlx_put_image_to_window(game()->mlx, game()->win, game()->background.img_ptr, 0, 0);
}