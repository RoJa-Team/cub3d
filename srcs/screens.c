/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/03 19:28:42 by rafasant         ###   ########.fr       */
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
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel(&screen()->background, x, HEIGHT - y, floor);
			put_pixel(&screen()->background, x, y, ceiling);
		}
	}
	// mlx_put_image_to_window(game()->mlx, game()->win, game()->background.img_ptr, 0, 0);
}

void	create_pause()
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	new_image(&screen()->pause, WIDTH, HEIGHT);
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel(&screen()->pause, x, HEIGHT - y, floor);
			put_pixel(&screen()->start, x, y, ceiling);
		}
	}
	// mlx_put_image_to_window(game()->mlx, game()->win, game()->background.img_ptr, 0, 0);
}