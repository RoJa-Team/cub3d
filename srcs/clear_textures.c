/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:15:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/25 20:18:28 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_wall(t_textures *textures)
{
	free_texture(&textures->wall[0]);
	free_texture(&textures->wall[1]);
	free_texture(&textures->wall[2]);
	free_texture(&textures->wall[3]);
}

void	free_textures_fire(t_textures *textures)
{
	free_texture(&textures->fire_loop[0]);
	free_texture(&textures->fire_loop[1]);
	free_texture(&textures->fire_loop[2]);
	free_texture(&textures->fire_loop[3]);
	free_texture(&textures->fire_loop[4]);
	free_texture(&textures->fire_loop[5]);
	free_texture(&textures->fire_loop[6]);
	free_texture(&textures->fire_loop[7]);
	free_texture(&textures->fire_end[0]);
	free_texture(&textures->fire_end[1]);
	free_texture(&textures->fire_end[2]);
	free_texture(&textures->fire_end[3]);
	free_texture(&textures->fire_end[4]);
}

void	free_textures_hose(t_textures *textures)
{
	free_texture(&textures->hose_idle);
	free_texture(&textures->hose_start[0]);
	free_texture(&textures->hose_start[1]);
	free_texture(&textures->hose_start[2]);
	free_texture(&textures->hose_start[3]);
	free_texture(&textures->hose_on[0]);
	free_texture(&textures->hose_on[1]);
	free_texture(&textures->hose_on[2]);
	free_texture(&textures->hose_on[3]);
	free_texture(&textures->hose_on[4]);
	free_texture(&textures->hose_on[5]);
	free_texture(&textures->hose_on[6]);
	free_texture(&textures->hose_on[7]);
	free_texture(&textures->hose_end[0]);
	free_texture(&textures->hose_end[1]);
	free_texture(&textures->hose_end[2]);
	free_texture(&textures->hose_end[3]);
	free_texture(&textures->hose_end[4]);
	free_texture(&textures->hose_end[5]);
	free_texture(&textures->hose_end[6]);
	free_texture(&textures->hose_end[7]);
}

void	free_textures_misc(t_textures *textures)
{
	free_texture(&textures->door);
	free_texture(&textures->clouds);
}

void	free_textures(t_textures *textures)
{
	free_textures_wall(textures);
	free_textures_fire(textures);
	free_textures_hose(textures);
	free_textures_misc(textures);
}
