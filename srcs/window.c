/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/24 21:43:35 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_state()
{
	raycaster();
	mlx_put_image_to_window(game()->mlx, game()->win, screen()->canva.img_ptr, game()->image_x, game()->image_y);
	//frame_swap();
	if (game()->paused == 1)
	{
		deallocate();
	}
	return (0);
}

unsigned int	get_pixel_colour(t_image *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_len) + (x * img->bpp / 8))));
}

void	put_pixel_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000) {
		return ;
	}
	if (x >= 0 && y >= 0 && x < img->w && y < img->h) 
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	put_img_to_img(t_image *dst, t_image *src, int x, int y)
{
	int i;
	int j;

	i = 0;
	while(i < src->w)
	{
		j = 0;
		while (j < src->h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_colour(src, i, j));
			j++;
		}
		i++;
	}
}

void	open_window(void)
{
	mlx_put_image_to_window(game()->mlx, game()->win, screen()->canva.img_ptr, game()->image_x, game()->image_y);
	// mlx_put_image_to_window(game()->mlx, game()->win, textures()->hose_firing[3].img.img_ptr, 0, 0);
	// lock_mouse();
	mlx_hook(game()->win, 2, (1L << 0), key_hooks, NULL);
	// mlx_hook(game()->win, 2, (1L << 0), mouse_hooks, NULL);
	mlx_hook(game()->win, 17, (1L << 2), close_game, NULL);
	// mlx_hook(game()->win, 3, (1L << 1), idle, game);
	mlx_loop_hook(game()->mlx, game_state, game);
	mlx_loop(game()->mlx);
}
