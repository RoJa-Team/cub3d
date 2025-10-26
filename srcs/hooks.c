/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:44:03 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 17:31:43 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(void *param)
{
	(void)param;
	unlock_mouse();
	deallocate();
	return (0);
}

void	pause_game()
{
	if (game()->paused == false)
		game()->paused = true;
	else if (game()->paused == true)
		game()->paused = false;
}

int	key_hooks(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_PAUSE )
		pause_game();
	else if (keycode == KEY_ESC)
		close_game(NULL);
	else if (game()->paused == true)
		return (0);
	else if (keycode == ARROW_L)
	 	turn_left();
	else if (keycode == ARROW_R)
	 	turn_right();
	// else if (keycode == KEY_CTRL)
	// 	crouch();
	// else if (keycode == KEY_SPACEBAR)
	// 	jump();
	// else if (keycode == KEY_INTERACT)
	// 	interact();
	// else if (keycode == KEY_SHOOT)
	// 	shoot();
	else if (keycode == KEY_W)
	 	move_front();
	else if (keycode == KEY_A)
	 	move_left();
	else if (keycode == KEY_S)
		move_back();
	else if (keycode == KEY_D)
		move_right();
	return (0);
}
