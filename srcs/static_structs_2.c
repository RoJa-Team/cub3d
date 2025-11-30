/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:28:22 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 16:28:23 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*game(void)
{
	static t_game	game;
	static int		initialized;

	if (!initialized)
	{
		initialized = 1;
		game.mlx = mlx_init();
	}
	return (&game);
}

t_raycast	*raycast(void)
{
	static t_raycast	raycast;
	static int			initialized;

	if (!initialized)
	{
		raycast.camera_x = 0;
		raycast.ray_dir_x = 0;
		raycast.ray_dir_y = 0;
		raycast.delta_dist_x = 1;
		raycast.delta_dist_y = 1;
		raycast.step_x = 0;
		raycast.step_y = 0;
		raycast.side_dist_x = 0;
		raycast.side_dist_y = 0;
		raycast.map_x = 0;
		raycast.map_y = 0;
		raycast.side = -1;
		raycast.hit = 0;
		raycast.perp_wall_dist = 0;
		raycast.door = false;
		initialized = 1;
	}
	return (&raycast);
}

t_draw	*draw(void)
{
	static t_draw	draw;
	static int		initialized;

	if (!initialized)
	{
		draw.line_height = 0;
		draw.draw_start = 0;
		draw.draw_end = 0;
		initialized = 1;
	}
	return (&draw);
}
