/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/06 21:19:40 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_background(int game_width, int game_height)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	y = -1;
	ceiling = textures()->ccolour;
	floor = textures()->fcolour;
	while (++y <= game_height / 2)
	{
		x = -1;
		while (++x < game_width)
		{
			put_pixel(&screen()->canva, x, game_height - y, floor);
			put_pixel(&screen()->canva, x, y, ceiling);
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

// int	get_frame_extents(t_xvar *xvar, Window win, int *left, int *right, int *top, int *bottom)
// {
// 	Atom property = XInternAtom(xvar->display, "_NET_FRAME_EXTENTS", False);
// 	Atom actual_type;
// 	int actual_format;
// 	unsigned long nitems, bytes_after;
// 	unsigned char *prop = NULL;

// 	if (XGetWindowProperty(xvar->display, win, property, 0, 4, False, XA_CARDINAL,
// 			&actual_type, &actual_format, &nitems, &bytes_after, &prop)
// 		== Success && prop != NULL)
// 	{
// 		long *extents = (long *)prop;
// 		*left   = extents[0];
// 		*right  = extents[1];
// 		*top    = extents[2];
// 		*bottom = extents[3];
// 		XFree(prop);
// 		return (1);
// 	}
// 	return (0);
// }

// int get_frame_extents(t_xvar *xvar, Window win, int *left, int *right, int *top, int *bottom)
// {
//     Atom			property;
//     Atom			actual_type;
//     int				actual_format;
//     unsigned long nitems, bytes_after;
//     unsigned char *data = NULL;

// 	property = XInternAtom(xvar->display, "_NET_FRAME_EXTENTS", False);
// 	data = NULL;
//     if (XGetWindowProperty(xvar->display, win, property, 0, 4, False, XA_CARDINAL, &actual_type, &actual_format, &nitems, &bytes_after, &property) == Success && data != NULL)
//     {
//         long *extents = (long *)data;
//         *left   = extents[0];
//         *right  = extents[1];
//         *top    = extents[2];
//         *bottom = extents[3];
//         XFree(property);
//         return 1;
//     }
//     return 0;
// }

// void get_display_resolution(t_resolution *display_info)
// {
// 	int		screen;
//     Display	*display;
	
// 	display = XOpenDisplay(NULL);
//     if (!display)
// 		return ((void)catch()->set("Error\n%s: Error retrieving monitor resolution.", __func__), deallocate());
// 	screen = DefaultScreen(display);
// 	get_work_area(display, screen, &display_info->width, &display_info->height);
// 	debug("screen width", display_info->width);
// 	debug("screen height", display_info->height);
//     XCloseDisplay(display);
// }

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
	debug("aspect width", display->aspect_width);
	debug("aspect height", display->aspect_height);
}

void fit_aspect_ratio(t_resolution *display, t_resolution *window, int *game_width, int *game_height)
{
    float	game_aspect;
    float	window_aspect;
	// int		window_width;
	// int		window_height;
	
	window->width = WIDTH;
	window->height = HEIGHT;
	if (display->width < WIDTH)
		window->width = display->width;
	if (display->height < HEIGHT)
		window->height = display->height;
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
	debug("game width", *game_width);
	debug("game height", *game_height);
}

// void fit_aspect_ratio(int aspect_width, int aspect_height, int *game_width, int *game_height)
// {
// 	float game_aspect;
// 	float window_aspect;
// 	game_aspect = (float)aspect_width / (float)aspect_height;
// 	window_aspect = (float)WIDTH / (float)HEIGHT;
// 	if (window_aspect > game_aspect)
// 	{
// 		// Container is wider → limited by height
// 		*game_height = HEIGHT;
// 		*game_width = (int)(HEIGHT * game_aspect);
// 	}
// 	else
// 	{
// 		// Container is taller → limited by width
// 		*game_width = WIDTH;
// 		*game_height = (int)(WIDTH / game_aspect);
// 	} 
// }

void	calculate_resolution(int *game_width, int *game_height)
{
	t_resolution	display;
	t_resolution	window;

	// get_display_resolution(&display);
	get_work_area(&display);
	get_aspect_ratio(&display);
	fit_aspect_ratio(&display, &window, game_width, game_height);
	game()->win = mlx_new_window(game()->mlx, window.width, window.height, "cub3d");
	game()->x = ((window.width - *game_width) / 2);
	game()->y = ((window.height - *game_height) / 2);
	debug("x", game()->x);
	debug("y", game()->y);
}

void	create_canva()
{
	int	game_width;
	int	game_height;

	calculate_resolution(&game_width, &game_height);
	debug("width", game_width);
	debug("height", game_height);
	new_image(&screen()->canva, game_width, game_height);
	add_background(game_width, game_height);
	put_img_to_img(&screen()->canva, &textures()->wall[1].img, game_width - textures()->wall[1].img.w, game_height - textures()->wall[1].img.h);
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