/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:24:23 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/28 19:08:52 by rafasant         ###   ########.fr       */
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

void	free_texture(t_texture *texture)
{
	if (texture->path)
		free(texture->path);
	if (texture->img.img_ptr)
		mlx_destroy_image(game()->mlx, texture->img.img_ptr);
}

void	free_textures()
{
	free_texture(&textures()->wall[0]);
	free_texture(&textures()->wall[1]);
	free_texture(&textures()->wall[2]);
	free_texture(&textures()->wall[3]);
	free_texture(&textures()->door[0]);
	free_texture(&textures()->door[1]);
	free_texture(&textures()->door[2]);
	free_texture(&textures()->ceiling);
	free_texture(&textures()->floor);
}

void	deallocate(void)
{
	if (game()->img.img_ptr)
		mlx_destroy_image(game()->mlx, game()->img.img_ptr);
	if (game()->win)
		mlx_destroy_window(game()->mlx, game()->win);
	if (game()->mlx)
	{
		mlx_destroy_display(game()->mlx);
		free(game()->mlx);
	}
	if (map_objects()->map)
		free_map();
	free_textures();
	catch()->print();
	catch()->free();
	exit(1);
}