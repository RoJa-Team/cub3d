/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/24 20:37:13 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_background(int game_width, int game_height)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;
	t_image	*canva;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	canva = &screen()->canva;
	while (++y <= game_height / 2)
	{
		x = -1;
		while (++x < game_width)
		{
			put_pixel(canva, x, game_height - y, floor);
			put_pixel(canva, x, y, ceiling);
		}
	}
}

t_image	*resize_image(t_image *image, int ratio)
{
    int	x;
	int	y;
	int	i;
	int	j;
	int	column = 0;
	int	row = 0;
	unsigned int	color;
	char	*dst;
    t_image *resized = malloc(sizeof(t_image));
    
    new_image(resized, image->w * ratio, image->h * ratio);
	i = 0;
    while(i < image->h)
	{
		j = 0;
        while(j < image->w)
		{

            color = *(unsigned int *)((image->addr + (i * image->line_len) + (j * image->bpp / 8)));
			y = row;
            while(y <= row + ratio)
			{
				x = column;
                while(x <= column + ratio)
				{
					dst = resized->addr + (y * resized->line_len + x * (resized->bpp / 8));
					*(unsigned int*)dst = color;
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
	mlx_destroy_image(game()->mlx, image->img_ptr);
	image->addr = resized->addr;
	image->w = resized->w;
	image->h = resized->h;
	image->bpp = resized->bpp;
	image->endian = resized->endian;
	image->line_len = resized->line_len;
	image->img_ptr = resized->img_ptr;
	free(resized);
	return (image);
}

int	calculate_zoom_ratio(t_image *img)
{
	int	ratio;
	int	image_max_size;

	image_max_size = 0.3 * game()->game_height;
	ratio = image_max_size / img->h;
	return(ratio);
}

void	add_view()
{
	int	ratio;

	ratio = calculate_zoom_ratio(&textures()->wall[1].img);
	put_img_to_img(&screen()->canva, resize_image(&textures()->wall[1].img, ratio), screen()->canva.w - textures()->wall[1].img.w, screen()->canva.h - textures()->wall[1].img.h);
	ratio = calculate_zoom_ratio(&textures()->idle_hose.img);
	put_img_to_img(&screen()->canva, resize_image(&textures()->idle_hose.img, ratio), (screen()->canva.w / 2) - (textures()->idle_hose.img.w / 2), screen()->canva.h - textures()->idle_hose.img.h);
}

void	add_minimap()
{
	
}

void	create_canva()
{
	calculate_resolution(&game()->game_width, &game()->game_height);
	new_image(&screen()->canva, game()->game_width, game()->game_height);
	add_background(game()->game_width, game()->game_height);
	add_view();
	// add_minimap();
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
}