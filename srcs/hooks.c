/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:44:03 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 17:43:48 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_game *game)
{
	unlock_mouse(game);
	deallocate();
	return (0);
}

void	pause_game(t_game *game)
{
	mlx_mouse_move(game->mlx, game->win, game->game_width / 2,
		game->game_height / 2);
	if (game->paused == false)
	{
		game->paused = true;
		unlock_mouse(game);
	}
	else if (game->paused == true)
	{
		game->paused = false;
		lock_mouse(game);
	}
}

void	open_full_map(t_game *game)
{
	if (game->open_map == false)
		game->open_map = true;
	else if (game->open_map == true)
		game->open_map = false;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_PAUSE)
		pause_game(game);
	else if (keycode == KEY_ESC)
		close_game(game);
	else if (game->paused == true)
		return (0);
	else if (keycode == ARROW_L)
		player()->turn_left = 1;
	else if (keycode == ARROW_R)
		player()->turn_right = 1;
	else if (keycode == KEY_SHOOT)
		screens()->hud.hose.on = true;
	else if (keycode == KEY_MAP)
		open_full_map(game);
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
	else if (keycode == KEY_SHOOT)
		screens()->hud.hose.on = false;
	return (0);
}
