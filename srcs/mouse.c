/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:34:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/26 22:08:34 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_hide(t_xvar *xvar, t_win_list *win)
{
	static char data[1] = {0};
	Cursor cursor;
	Pixmap blank;
	XColor dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);
}

void	mouse_show(t_xvar *xvar, t_win_list *win)
{
	XUndefineCursor(xvar->display, win->window);
}

void	lock_mouse()
{
	int	grab;

	grab = XGrabPointer(game()->mlx->display, game()->win->window, True, 
	ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, 
	GrabModeAsync, game()->win->window, None, CurrentTime);
	if (grab != GrabSuccess)
		return ((void)catch()->set("Error\n%s: Failed locking mouse to window.", 
			__func__), deallocate());
	// mlx_mouse_hide(game()->mlx, game()->win);
}

void	unlock_mouse()
{
	XUngrabPointer(game()->mlx->display, CurrentTime);
	// mouse_show(game()->mlx, game()->win);
}

int	center_mouse(t_game *game, int *last_x, int x)
{
	if (x <= 0 || x >= game->game_width)
	{
		*last_x = game->game_width / 2;
		mlx_mouse_move(game->mlx, game->win, *last_x, game->game_height / 2);
		return (1);
	}
	return (0);
}

int	mouse_movement(int x, int y, t_game *game)
{
	int			diff_x;
	static int	last_x = -1;
	
	(void)y;
	if (game->paused)
		return (0);
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	if (center_mouse(game, &last_x, x))
		return (0);
	diff_x = x - last_x;
	last_x = x;
	if (diff_x != 0)
	{
		if (diff_x > 0)
			rotate_camera(player(), frame()->rot_speed * 0.25);
		if (diff_x < 0)
			rotate_camera(player(), -frame()->rot_speed * 0.25);
	}
	return (0);
}

int mouse_press(int button, int mouse_x, int mouse_y, t_game *game)
{
	if (button == 1)
	{
		player()->hose->on = true;
	}
	(void)mouse_x;
	(void)mouse_y;
	(void)game;
	return (0);
}

int mouse_release(int button, int mouse_x, int mouse_y, t_game *game)
{
	if (button == 1)
	{
		player()->hose->on = false;
	}
	(void)mouse_x;
	(void)mouse_y;
	(void)game;
	return (0);
}