/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/07 19:50:07 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_background(int game_width, int game_height)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;
	t_image	*canva;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	canva = &screen()->canva;
	while (++y <= game_height / 2)
	{
		x = -1;
		while (++x < game_width)
		{
			put_pixel(canva, x, game_height - y, floor);
			put_pixel(canva, x, y, ceiling);
		}
	}
}

void	add_view()
{

}

void	add_minimap()
{
	
}

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

int	gcd(int a, int b)
{
	int	temp;

    while (b != 0)
	{
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void get_aspect_ratio(t_resolution *display)
{
	int	g;

    g = gcd(display->width, display->height);
    display->aspect_width = display->width / g;
    display->aspect_height = display->height / g;
}

void fit_aspect_ratio(t_resolution *display, t_resolution *window, int *game_width, int *game_height)
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

void	get_window_size(t_resolution *display, t_resolution *window)
{
	window->width = WIDTH;
	window->height = HEIGHT;
	if (display->width < WIDTH)
		window->width = display->width;
	if (display->height < HEIGHT)
		window->height = display->height;
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

void	create_canva()
{
	int	game_width;
	int	game_height;

	calculate_resolution(&game_width, &game_height);
	new_image(&screen()->canva, game_width, game_height);
	add_background(game_width, game_height);
	put_img_to_img(&screen()->canva, &textures()->wall[1].img, screen()->canva.w - textures()->wall[1].img.w, screen()->canva.h - textures()->wall[1].img.h);
	// add_view();
	// add_minimap();
}

void	create_pause()
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	new_image(&screen()->pause, WIDTH, HEIGHT);
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel(&screen()->pause, x, HEIGHT - y, floor);
			put_pixel(&screen()->start, x, y, ceiling);
		}
	}
}