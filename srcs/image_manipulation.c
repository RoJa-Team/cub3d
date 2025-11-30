/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:20:41 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 16:15:35 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_img_to_img(t_image *dst, t_image *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i <= src->h / 2)
	{
		j = 0;
		while (j < src->w)
		{
			put_pixel_img(dst, x + j, y + i, get_pixel_colour(src, j, i));
			put_pixel_img(dst, x + j, y + src->h - i, get_pixel_colour(src,
					j, src->h - i));
			j++;
		}
		i++;
	}
}

void	resize_image(t_image *image, int ratio)
{
	t_image		resized;
	t_helper	*h;

	new_image(&resized, image->w * ratio, image->h * ratio);
	h = helper();
	h->i = -1;
	while (++h->i < image->h)
	{
		h->j = -1;
		while (++h->j < image->w)
		{
			h->y = h->row - 1;
			while (++h->y <= h->row + ratio)
			{
				h->x = h->column - 1;
				while (++h->x <= h->column + ratio)
					put_pixel(&resized, h->x, h->y,
						get_pixel_colour(image, h->j, h->i));
			}
			h->column += ratio;
		}
		h->row += ratio;
		h->column = 0;
	}
	copy_image(image, &resized);
}
