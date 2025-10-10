/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:11:15 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/07 20:12:56 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_work_area(t_resolution *display)
{
	Atom			property;
	Atom			actual_type;
	long			*workarea;
	unsigned long	dummy;
	unsigned char	*data;

	property = XInternAtom(game()->mlx->display, "_NET_WORKAREA", False);
	data = NULL;
	if (XGetWindowProperty(game()->mlx->display, game()->mlx->root, property, 0L, 4L, False, XA_CARDINAL, &actual_type, &display->width, &dummy, &dummy, &data) == Success && data != NULL)
	{
		workarea = (long *)data;
		display->width = workarea[2];
		display->height = workarea[3];
		XFree(data);
		return 1;
	}
	return 0;
}

int get_frame_extents(int *w_frame_size)
{
    Atom			property;
    Atom			actual_type;
    int				actual_format;
    unsigned long nitems, bytes_after;
    unsigned char *data = NULL;

	property = XInternAtom(game()->mlx->display, "_NET_FRAME_EXTENTS", False);
	data = NULL;
    if (XGetWindowProperty(game()->mlx->display, game()->win->window, property, 0, 4, False, XA_CARDINAL, &actual_type, &actual_format, &nitems, &bytes_after, &data) == Success && data != NULL)
    {
        long *extents = (long *)data;
		*w_frame_size = extents[2];
        XFree(data);
        return 1;
    }
    return 0;
}

void	fit_aspect_ratio(t_resolution *display, t_resolution *window, int *game_width, int *game_height)
{
    float	game_aspect;
    float	window_aspect;
	
	game_aspect = (float)display->aspect_width / (float)display->aspect_height;
	window_aspect = (float)window->width / (float)window->height;
    if (window_aspect > game_aspect)
	{
        // if window is wider, limit by height
        *game_height = window->height;
        *game_width  = (int)(window->height * game_aspect);
    }
	else
	{
        // if iwndow is taller, limit by width
        *game_width  = window->width;
        *game_height = (int)(window->width / game_aspect);
    }
}

void	calculate_resolution(int *game_width, int *game_height)
{
	int				w_frame_size;
	t_resolution	display;
	t_resolution	window;

	get_work_area(&display);
	get_aspect_ratio(&display);
	get_window_size(&display, &window);
	game()->win = mlx_new_window(game()->mlx, window.width, window.height, "cub3d");
	get_frame_extents(&w_frame_size);
	if (display.height == window.height)
		window.height = window.height - w_frame_size;
	fit_aspect_ratio(&display, &window, game_width, game_height);
	game()->x = ((window.width - *game_width) / 2);
	game()->y = ((window.height - *game_height) / 2);
}
