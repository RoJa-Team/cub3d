/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:40:08 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 14:42:30 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lock_mouse(t_game *game)
{
	int	grab;

	grab = XGrabPointer(game->mlx->display, game->win->window, True,
			ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
			GrabModeAsync, GrabModeAsync, game->win->window, None, CurrentTime);
	if (grab != GrabSuccess)
		return ((void)catch()->set("Error\n%s: Failed locking mouse to window.",
				__func__), deallocate());
	XFixesHideCursor(game->mlx->display, game->win->window);
}

void	unlock_mouse(t_game *game)
{
	XUngrabPointer(game->mlx->display, CurrentTime);
	XFixesShowCursor(game->mlx->display, game->win->window);
}
