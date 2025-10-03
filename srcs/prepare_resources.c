/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:56:14 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/03 23:01:01 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	load_screens()
// {
// 	create_start();
// 	create_paused();
// 	create_died();
// 	create_finish();
// 	create_canva();
// 	create_background();
// }

void	load_textures()
{
	load_textures_wall();
	load_textures_fire();
	load_textures_hose();
	load_textures_misc();
}

void	init_mlx()
{
	game()->mlx = mlx_init();
}

void	prepare_resources()
{
	init_mlx();
	load_textures();
	// load_screens();
	create_canva();
	// create_background();
}