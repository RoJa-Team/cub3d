/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:44:03 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/28 12:24:55 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(void *param)
{
	(void)param;
	deallocate();
	return (0);
}

int	hooks(int keycode, void *param)
{
	(void)param;
	// game->map.player.dir = keycode;
	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		close_game(NULL);
	// else if (keycode == ARROW_L)
	// 	turn_left();
	// else if (keycode == ARROW_R)
	// 	turn_right();
	// else if (keycode == KEY_CTRL)
	// 	crouch();
	// else if (keycode == KEY_SPACEBAR)
	// 	jump();
	// else if (keycode == KEY_INTERACT)
	// 	turn_left();
	// else if (keycode == KEY_SHOOT)
	// 	turn_left();
	// else if (keycode == KEY_W)
	// 	move_front();
	// else if (keycode == KEY_A)
	// 	move_left();
	// else if (keycode == KEY_S)
	// 	move_back();
	// else if (keycode == KEY_D)
	// 	move_right();
	
	// else if (keycode = )
	// if (game->map.player.run == 5)
	// 	game->map.player.run = 0;
	// game->map.player.idle = -1;
	return (0);
}