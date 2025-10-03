/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:04:01 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/03 19:29:20 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	xpm_to_img(t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(game()->mlx, \
	texture->path, &texture->img.w, &texture->img.h);
	if (texture->img.img_ptr == NULL)
		return ((void)catch()->set("Error\n%s: Error loading xpm.", __func__), deallocate());
	texture->img.addr = mlx_get_data_addr(texture->img.img_ptr, &texture->img.bpp, \
	&texture->img.line_len, &texture->img.endian);
	if (texture->img.img_ptr == NULL)
		return ((void)catch()->set("Error\n%s: Error retrieving image address.", __func__), deallocate());
}

void	load_textures()
{
	xpm_to_img(&textures()->floor);
	xpm_to_img(&textures()->ceiling);
	xpm_to_img(&textures()->door[0]);
	xpm_to_img(&textures()->door[1]);
	xpm_to_img(&textures()->door[2]);
	xpm_to_img(&textures()->wall[0]);
	xpm_to_img(&textures()->wall[1]);
	xpm_to_img(&textures()->wall[2]);
	xpm_to_img(&textures()->wall[3]);
}
