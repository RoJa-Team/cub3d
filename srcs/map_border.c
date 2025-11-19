/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:26:50 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/14 20:27:08 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int lerp(int a, int b, float t)
{
    return a + (int)((b - a) * t);
}

int gradient_brown(float t)
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