/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/10 22:39:37 by rafasant         ###   ########.fr       */
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
	debug("resized w", resized->w);
	debug("resized h", resized->h);
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
	return (image);
}

t_image	*resize_image2(t_image *image, int ratio)
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
	debug("resized w", resized->w);
	debug("resized h", resized->h);
	i = 0;
    while(i < image->h)
	{
		j = 0;
        while(j < image->w)
		{

            color = *(unsigned int *)((image->addr + (i * image->line_len) + (j * image->bpp / 8)));
			x = row;
            while(x <= row + ratio)
			{
				y = column;
                while(y <= column + ratio)
				{
					dst = resized->addr + (y * resized->line_len + x * (resized->bpp / 8));
					*(unsigned int*)dst = color;
					y++;
                }
				x++;
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
	return (image);
}

void	add_view()
{
	
	put_img_to_img(&screen()->canva, resize_image(&textures()->wall[1].img, 10), screen()->canva.w - textures()->wall[1].img.w, screen()->canva.h - textures()->wall[1].img.h);
	debug("wall[1].img w", textures()->wall[1].img.w);
	debug("wall[1].img h", textures()->wall[1].img.h);
	put_img_to_img(&screen()->canva, resize_image(&textures()->idle_hose.img, 10), (screen()->canva.w / 2) - (textures()->idle_hose.img.w / 2), screen()->canva.h - textures()->idle_hose.img.h);
}

void	add_minimap()
{
	
}



void	create_canva()
{
	int	game_width;
	int	game_height;

	calculate_resolution(&game_width, &game_height);
	new_image(&screen()->canva, game_width, game_height);
	add_background(game_width, game_height);
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