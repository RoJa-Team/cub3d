/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:12:21 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/15 20:21:32 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_window_size(t_res *display, t_res *window)
{
	if (WIDTH < 640 || HEIGHT < 360)
	{
		window->width = 640;
		window->height = 360;
	}
	else
	{
		window->width = WIDTH;
		window->height = HEIGHT;
	}
	if (display->width < WIDTH)
		window->width = display->width;
	if (display->height < HEIGHT)
		window->height = display->height;
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
	return (a);
}

void	get_aspect_ratio(t_res *display)
{
	int	g;

	g = gcd(display->width, display->height);
	display->aspect_width = display->width / g;
	display->aspect_height = display->height / g;
}
