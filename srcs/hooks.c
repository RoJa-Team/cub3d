/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:44:03 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/12 21:51:21 by joafern2         ###   ########.fr       */
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
		player()->turn_left = 1;
	else if (keycode == ARROW_R)
		player()->turn_right = 1;
	// else if (keycode == KEY_CTRL)
	// 	crouch();
	// else if (keycode == KEY_SPACEBAR)
	// 	jump();
	// else if (keycode == KEY_INTERACT)
	// 	interact();
	// else if (keycode == KEY_SHOOT)
	// 	shoot();
	else if (keycode == KEY_W)
		player()->move_front = 1;
	else if (keycode == KEY_A)
		player()->move_right = 1;
	else if (keycode == KEY_S)
		player()->move_back = 1;
	else if (keycode == KEY_D)
		player()->move_left = 1;
	return (0);
}


int	key_release(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_W)
		player()->move_front = 0;
	else if (keycode == KEY_A)
		player()->move_right = 0;
	else if (keycode == KEY_S)
		player()->move_back = 0;
	else if (keycode == KEY_D)
		player()->move_left = 0;
	else if (keycode == ARROW_L)
		player()->turn_left = 0;
	else if (keycode == ARROW_R)
		player()->turn_right = 0;
	return (0);
}
