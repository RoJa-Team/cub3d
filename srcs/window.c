/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/26 21:45:49 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_state()
{
	if (game()->paused == 1)
		return (0);
	render();
	return (0);
}

void	open_window(void)
{
	lock_mouse();
	mlx_hook(game()->win, 2, (1L << 0), key_press, NULL);
	mlx_hook(game()->win, 3, (1L << 1), key_release, NULL);
	mlx_hook(game()->win, 4, (1L << 2), mouse_press, game());
	mlx_hook(game()->win, 5, (1L << 3), mouse_release, game());
	mlx_hook(game()->win, 6, (1L << 6), mouse_movement, game());
	mlx_hook(game()->win, 17, (1L << 2), close_game, NULL);
	// mlx_hook(game()->win, 3, (1L << 1), idle, game);
	mlx_loop_hook(game()->mlx, game_state, game);
	mlx_loop(game()->mlx);
}
