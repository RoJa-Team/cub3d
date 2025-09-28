/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:10:03 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/28 19:06:59 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	fill_background(int width, int height)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			if (y < height / 2)
				put_pixel(&game()->img, x, y, ceiling);
			else
				put_pixel(&game()->img, x, y, floor);
		}
	}
	mlx_put_image_to_window(game()->mlx, game()->win, game()->img.img_ptr, 0, 0);
}
