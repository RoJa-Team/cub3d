/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/12 22:34:01 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_state()
{
	if (game()->paused == 1)
		deallocate();
	render();
	return (0);
}

void	open_window(void)
{
	// lock_mouse();
	mlx_hook(game()->win, 2, (1L << 0), key_hooks, NULL);
	mlx_hook(game()->win, 3, (1L << 1), key_release, NULL);
	// mlx_hook(game()->win, 2, (1L << 0), mouse_hooks, NULL);
	mlx_hook(game()->win, 17, (1L << 2), close_game, NULL);
	// mlx_hook(game()->win, 3, (1L << 1), idle, game);
	mlx_loop_hook(game()->mlx, game_state, game);
	mlx_loop(game()->mlx);
}
