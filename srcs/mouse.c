/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:34:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/28 17:26:04 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	lock_mouse()
{
    // // Request to receive events (added StructureNotifyMask!)
    // XSelectInput(game()->mlx->display, game()->win->window,
    //              ExposureMask | KeyPressMask | StructureNotifyMask);

    // // Show the window
    // XMapWindow(game()->mlx->display, game()->win->window);

    // --- Now try to grab the pointer ---
    int grab = XGrabPointer(game()->mlx->display,
                            game()->win->window,
                            True,
                            ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                            GrabModeAsync,
                            GrabModeAsync,
                            game()->win->window,
                            None,
                            CurrentTime);
    if (grab != GrabSuccess)
        fprintf(stderr, "Failed to grab pointer: %d\n", grab);
    else
		printf("Pointer successfully grabbed!\n");
	return 0;
}

int	unlock_mouse()
{
	XUngrabPointer(game()->mlx->display, CurrentTime);
    return 0;
}

int	mouse_hooks(int keycode, void *param)
{
	(void)param;
	printf("%d\n", keycode);
	// if (keycode == KEY_ESC)
	// 	close_game(NULL);
	// else if (keycode == ARROW_L)
	// 	turn_left();
	// else if (keycode == ARROW_R)
	// 	turn_right();
	// else if (keycode == KEY_CTRL)
	// 	crouch();
	// else if (keycode == KEY_SPACEBAR)
	// 	jump();
	// else if (keycode == KEY_INTERACT)
	// 	interact();
	// else if (keycode == KEY_SHOOT)
	// 	shoot();
	// else if (keycode == KEY_PAUSE)
	// 	pause_game();
	// else if (keycode == KEY_W)
	// 	move_front();
	// else if (keycode == KEY_A)
	// 	move_left();
	// else if (keycode == KEY_S)
	// 	move_back();
	// else if (keycode == KEY_D)
	// 	move_right();
	return (0);
}