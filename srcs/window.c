/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/28 19:05:35 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void new_image(t_image *img, int width, int height)
{
	img->img_ptr = mlx_new_image(game()->mlx, width, height);
	if (!img->img_ptr)
		deallocate();
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		deallocate();
}

int	game_state()
{
	if (game()->paused == 1)
	{
		deallocate();
	}
	return (0);
}

void	open_window(void)
{
	game()->mlx = mlx_init();
	game()->win = mlx_new_window(game()->mlx, WIDTH, HEIGHT, "cub3d");
	new_image(&game()->img, WIDTH, HEIGHT);
	// lock_mouse();
	fill_background(WIDTH, HEIGHT);
	mlx_hook(game()->win, 2, (1L << 0), key_hooks, NULL);
	// mlx_hook(game()->win, 2, (1L << 0), mouse_hooks, NULL);
	mlx_hook(game()->win, 17, (1L << 2), close_game, NULL);
	// mlx_hook(game()->win, 3, (1L << 1), idle, game);
	mlx_loop_hook(game()->mlx, game_state, game);
	mlx_loop(game()->mlx);
}
