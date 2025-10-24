/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:24:23 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/24 20:57:42 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map()
{
	int	i;

	i = 0;
	while (map_objects()->map[i] != NULL)
	{
		if (map_objects()->map[i])
			free(map_objects()->map[i]);
		i++;
	}
	free(map_objects()->map);
}

void	free_image(t_image *image)
{
	if (image->img_ptr)
		mlx_destroy_image(game()->mlx, image->img_ptr);
}

void	free_texture(t_texture *texture)
{
	if (texture->path)
		free(texture->path);
	free_image(&texture->img);
}

void	free_textures_wall()
{
	free_texture(&textures()->wall[0]);
	free_texture(&textures()->wall[1]);
	free_texture(&textures()->wall[2]);
	free_texture(&textures()->wall[3]);
}

void	free_textures_fire()
{
	free_texture(&textures()->fire_loop[0]);
	free_texture(&textures()->fire_loop[1]);
	free_texture(&textures()->fire_loop[2]);
	free_texture(&textures()->fire_loop[3]);
	free_texture(&textures()->fire_loop[4]);
	free_texture(&textures()->fire_loop[5]);
	free_texture(&textures()->fire_loop[6]);
	free_texture(&textures()->fire_loop[7]);
	free_texture(&textures()->fire_ending[0]);
	free_texture(&textures()->fire_ending[1]);
	free_texture(&textures()->fire_ending[2]);
	free_texture(&textures()->fire_ending[3]);
	free_texture(&textures()->fire_ending[4]);
}

void	free_textures_hose()
{
	free_texture(&textures()->idle_hose);
	free_texture(&textures()->hose_start[0]);
	free_texture(&textures()->hose_start[1]);
	free_texture(&textures()->hose_start[2]);
	free_texture(&textures()->hose_start[3]);
	free_texture(&textures()->hose_firing[0]);
	free_texture(&textures()->hose_firing[1]);
	free_texture(&textures()->hose_firing[2]);
	free_texture(&textures()->hose_firing[3]);
	free_texture(&textures()->hose_firing[4]);
	free_texture(&textures()->hose_firing[5]);
	free_texture(&textures()->hose_firing[6]);
	free_texture(&textures()->hose_firing[7]);
	free_texture(&textures()->hose_ending[0]);
	free_texture(&textures()->hose_ending[1]);
	free_texture(&textures()->hose_ending[2]);
	free_texture(&textures()->hose_ending[3]);
	free_texture(&textures()->hose_ending[4]);
	free_texture(&textures()->hose_ending[5]);
	free_texture(&textures()->hose_ending[6]);
	free_texture(&textures()->hose_ending[7]);
}

void	free_textures_misc()
{
	free_texture(&textures()->door[0]);
	free_texture(&textures()->door[1]);
	free_texture(&textures()->door[2]);
	free_texture(&textures()->clouds);
}

void	free_textures()
{
	free_textures_wall();
	free_textures_fire();
	free_textures_hose();
	free_textures_misc();
}

void	free_screens()
{
	free_image(&screen()->minimap);
	free_image(&screen()->start);
	free_image(&screen()->canva);
	free_image(&screen()->pause);
	free_image(&screen()->death);
	free_image(&screen()->finish);
}

void	deallocate(void)
{
	if (map_objects()->map)
		free_map();
	free_textures();
	free_screens();
	if (game()->win)
		mlx_destroy_window(game()->mlx, game()->win);
	if (game()->mlx)
	{
		mlx_destroy_display(game()->mlx);
		free(game()->mlx);
	}
	catch()->print();
	catch()->free();
	exit(1);
}