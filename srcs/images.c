/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:02:22 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/05 18:27:00 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_image(t_image *img, int width, int height)
{
	img->img_ptr = mlx_new_image(game()->mlx, width, height);
	if (!img->img_ptr)
		return ((void)catch()->set("Error\n%s: Error creating new image.", 
			__func__), deallocate());
	img->w = width;
	img->h = height;
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, 
		&img->endian);
	if (!img->addr)
		return ((void)catch()->set("Error\n%s: Error retrieving new image address.", __func__), deallocate());
}

// void	scale_image(t_image	*img, int width, int height)
// {
// 	if (img->w == img->h / 2)
// 		scale_2to1(img, width, height);
// 	else if (img->w == img->h)
// 		scale_1to1(img, width, height);
// }

// void	scale_2to1(t_image	*img, int width, int height)
// {

// }

// void	scale_1to1(t_image	*img, int width, int height)
// {
	
// }
