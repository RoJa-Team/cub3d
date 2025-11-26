/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:24:23 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 19:40:04 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_map(void)
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

void	free_screens(t_screens *screens)
{
	free_image(&screens->hud.full_map.map);
	free_image(&screens->hud.minimap.map);
	free_image(&screens->start);
	free_image(&screens->canva);
	free_image(&screens->pause);
	free_image(&screens->death);
	free_image(&screens->finish);
}

void	deallocate(void)
{
	if (map_objects()->map)
		free_map();
	if (map_objects()->sprites)
		free(map_objects()->sprites);
	if (map_objects()->doors)
		free(map_objects()->doors);
	if (map_objects()->zbuff)
		free(map_objects()->zbuff);
	free_textures(textures());
	free_screens(screens());
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
