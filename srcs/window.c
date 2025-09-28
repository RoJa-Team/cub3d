/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/27 18:54:16 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_window(void)
{
	game()->width = WIDTH;
	game()->height = HEIGHT;
	game()->mlx = mlx_init();
	game()->win = mlx_new_window(game()->mlx, game()->width, game()->height, "cub3d");
	game()->img.img_ptr = mlx_new_image(game()->mlx, game()->width, game()->height);
	game()->img.addr = mlx_get_data_addr(game()->img.img_ptr, &game()->img.bpp,
		&game()->img.line_len, &game()->img.endian);
	mlx_hook(game()->win, 2, (1L << 0), hooks, NULL);
	mlx_hook(game()->win, 17, (1L << 2), close_game, NULL);
	// mlx_hook(game()->win, 3, (1L << 1), idle, game);
	// mlx_loop_hook(game()->mlx, render, game);
	mlx_loop(game()->mlx);
}
