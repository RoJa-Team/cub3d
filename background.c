/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:10:03 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/27 13:50:55 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;	
}

void	fill_background(int width, int height, int color)
{
	int	x;
	int	y;
	int	*ceiling;
	int	*floor;

	x = -1;
	y = -1;
	ceiling = &textures()->ceiling;
	floor = &textures()->floor;
	ceiling	= create_rgb(ceiling->r, ceiling->g, ceiling->b);
	floor = create_rgb(floor->r, floor->g, floor->b);
	while (++y < height)
	{
		while (++x < width)
		{
			if (y < height / 2)
				put_pixel(game()->img, x, y, ceiling);
			else
				put_pixel(game()->img, x, y, floor);
		}
	}
}
