/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:20:41 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 17:06:35 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_img_to_img(t_image *dst, t_image *src, int x, int y)
{
	int i;
	int j;

	i = 0;
	while(i <= src->h / 2)
	{
		j = 0;
		while (j < src->w)
		{
			put_pixel_img(dst, x + j, y + i, get_pixel_colour(src, j, i));
			put_pixel_img(dst, x + j, y + src->h - i, get_pixel_colour(src, j, src->h - i));
			j++;
		}
		i++;
	}
}