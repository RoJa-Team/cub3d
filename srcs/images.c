/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:02:22 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 17:09:58 by rafasant         ###   ########.fr       */
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
		return ((void)catch()->set("Error\n%s: Error retrieving new image address.", 
			__func__), deallocate());
}

void	copy_image(t_image *dest, t_image *src)
{
	mlx_destroy_image(game()->mlx, dest->img_ptr);
	dest->addr = src->addr;
	dest->w = src->w;
	dest->h = src->h;
	dest->bpp = src->bpp;
	dest->endian = src->endian;
	dest->line_len = src->line_len;
	dest->img_ptr = src->img_ptr;
}

void	resize_image(t_image *image, int ratio)
{
    int	x;
	int	y;
	int	i;
	int	j;
	int	column = 0;
	int	row = 0;
	unsigned int	color;
    t_image	resized;
    
    new_image(&resized, image->w * ratio, image->h * ratio);
	i = 0;
    while(i < image->h)
	{
		j = 0;
        while(j < image->w)
		{
			color = get_pixel_colour(image, j, i);
			y = row;
            while(y <= row + ratio)
			{
				x = column;
                while(x <= column + ratio)
				{
					put_pixel(&resized, x, y, color);
					x++;
                }
				y++;
            }
            column += ratio;
			j++; 
        }
        row += ratio;
        column = 0;
		i++;
    }
	copy_image(image, &resized);
}

int	calc_zoom_ratio(t_image *img, int game_height)
{
	int	ratio;
	int	image_max_size;

	image_max_size = 0.3 * game_height;
	ratio = image_max_size / img->h;
	return(ratio);
}

void	scale_hose_images(t_textures *texs)
{
	int	height;

	height = game()->game_height;
	resize_image(&texs->hose_idle.img, calc_zoom_ratio(&texs->hose_idle.img, height));
	resize_image(&texs->hose_start[0].img, calc_zoom_ratio(&texs->hose_start[0].img, height));
	resize_image(&texs->hose_start[1].img, calc_zoom_ratio(&texs->hose_start[1].img, height));
	resize_image(&texs->hose_start[2].img, calc_zoom_ratio(&texs->hose_start[2].img, height));
	resize_image(&texs->hose_start[3].img, calc_zoom_ratio(&texs->hose_start[3].img, height));
	resize_image(&texs->hose_on[0].img, calc_zoom_ratio(&texs->hose_on[0].img, height));
	resize_image(&texs->hose_on[1].img, calc_zoom_ratio(&texs->hose_on[1].img, height));
	resize_image(&texs->hose_on[2].img, calc_zoom_ratio(&texs->hose_on[2].img, height));
	resize_image(&texs->hose_on[3].img, calc_zoom_ratio(&texs->hose_on[3].img, height));
	resize_image(&texs->hose_on[4].img, calc_zoom_ratio(&texs->hose_on[4].img, height));
	resize_image(&texs->hose_on[5].img, calc_zoom_ratio(&texs->hose_on[5].img, height));
	resize_image(&texs->hose_on[6].img, calc_zoom_ratio(&texs->hose_on[6].img, height));
	resize_image(&texs->hose_on[7].img, calc_zoom_ratio(&texs->hose_on[7].img, height));
	resize_image(&texs->hose_end[0].img, calc_zoom_ratio(&texs->hose_end[0].img, height));
	resize_image(&texs->hose_end[1].img, calc_zoom_ratio(&texs->hose_end[1].img, height));
	resize_image(&texs->hose_end[2].img, calc_zoom_ratio(&texs->hose_end[2].img, height));
	resize_image(&texs->hose_end[3].img, calc_zoom_ratio(&texs->hose_end[3].img, height));
	resize_image(&texs->hose_end[4].img, calc_zoom_ratio(&texs->hose_end[4].img, height));
	resize_image(&texs->hose_end[5].img, calc_zoom_ratio(&texs->hose_end[5].img, height));
	resize_image(&texs->hose_end[6].img, calc_zoom_ratio(&texs->hose_end[6].img, height));
	resize_image(&texs->hose_end[7].img, calc_zoom_ratio(&texs->hose_end[7].img, height));
}
