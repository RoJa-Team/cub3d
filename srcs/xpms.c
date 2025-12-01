/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:04:01 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 19:30:58 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	xpm_to_img(char *path, t_image *img)
{
	img->img_ptr = mlx_xpm_file_to_image(game()->mlx, path, &img->w, &img->h);
	if (img->img_ptr == NULL)
		return ((void)catch()->set("Error\n%s: Error loading xpm {%s}.",
				__func__, path), deallocate());
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (img->img_ptr == NULL)
		return ((void)catch()->set("Error\n%s: Error retrieving image address.",
				__func__), deallocate());
}

void	load_textures_wall(t_textures *t)
{
	if (t->wall[SO].path != NULL || t->wall[NO].path != NULL
		|| t->wall[EA].path != NULL || t->wall[WE].path != NULL)
	{
		xpm_to_img(t->wall[NO].path, &t->wall[0].img);
		xpm_to_img(t->wall[SO].path, &t->wall[1].img);
		xpm_to_img(t->wall[WE].path, &t->wall[2].img);
		xpm_to_img(t->wall[EA].path, &t->wall[3].img);
	}
	else
		return ((void)catch()->set("Error\n%s: Missing texture.",
				__func__), deallocate());
}

void	load_textures_fire(t_textures *t)
{
	xpm_to_img("textures/edited/fire_loop1.xpm", &(t->fire_loop[0].img));
	xpm_to_img("textures/edited/fire_loop2.xpm", &(t->fire_loop[1].img));
	xpm_to_img("textures/edited/fire_loop3.xpm", &(t->fire_loop[2].img));
	xpm_to_img("textures/edited/fire_loop4.xpm", &(t->fire_loop[3].img));
	xpm_to_img("textures/edited/fire_loop5.xpm", &(t->fire_loop[4].img));
	xpm_to_img("textures/edited/fire_loop6.xpm", &(t->fire_loop[5].img));
	xpm_to_img("textures/edited/fire_loop7.xpm", &(t->fire_loop[6].img));
	xpm_to_img("textures/edited/fire_loop8.xpm", &(t->fire_loop[7].img));
	xpm_to_img("textures/edited/burning_end_1.xpm", &(t->fire_end[0].img));
	xpm_to_img("textures/edited/burning_end_2.xpm", &(t->fire_end[1].img));
	xpm_to_img("textures/edited/burning_end_3.xpm", &(t->fire_end[2].img));
	xpm_to_img("textures/edited/burning_end_4.xpm", &(t->fire_end[3].img));
	xpm_to_img("textures/edited/burning_end_5.xpm", &(t->fire_end[4].img));
}

void	load_textures_hose(t_textures *t)
{
	xpm_to_img("textures/edited/hose.xpm", &(t->hose_idle.img));
	xpm_to_img("textures/edited/hose_firing1.xpm", &(t->hose_start[0].img));
	xpm_to_img("textures/edited/hose_firing2.xpm", &(t->hose_start[1].img));
	xpm_to_img("textures/edited/hose_firing3.xpm", &(t->hose_start[2].img));
	xpm_to_img("textures/edited/hose_firing4.xpm", &(t->hose_start[3].img));
	xpm_to_img("textures/edited/hose_firing5.xpm", &(t->hose_on[0].img));
	xpm_to_img("textures/edited/hose_firing6.xpm", &(t->hose_on[1].img));
	xpm_to_img("textures/edited/hose_firing7.xpm", &(t->hose_on[2].img));
	xpm_to_img("textures/edited/hose_firing8.xpm", &(t->hose_on[3].img));
	xpm_to_img("textures/edited/hose_firing9.xpm", &(t->hose_on[4].img));
	xpm_to_img("textures/edited/hose_firing10.xpm", &(t->hose_on[5].img));
	xpm_to_img("textures/edited/hose_firing11.xpm", &(t->hose_on[6].img));
	xpm_to_img("textures/edited/hose_firing12.xpm", &(t->hose_on[7].img));
	xpm_to_img("textures/edited/hose_ending1.xpm", &(t->hose_end[0].img));
	xpm_to_img("textures/edited/hose_ending2.xpm", &(t->hose_end[1].img));
	xpm_to_img("textures/edited/hose_ending3.xpm", &(t->hose_end[2].img));
	xpm_to_img("textures/edited/hose_ending4.xpm", &(t->hose_end[3].img));
	xpm_to_img("textures/edited/hose_ending5.xpm", &(t->hose_end[4].img));
	xpm_to_img("textures/edited/hose_ending6.xpm", &(t->hose_end[5].img));
	xpm_to_img("textures/edited/hose_ending7.xpm", &(t->hose_end[6].img));
	xpm_to_img("textures/edited/hose_ending8.xpm", &(t->hose_end[7].img));
}

void	load_textures_misc(t_textures *t)
{
	xpm_to_img("textures/edited/slide_door.xpm", &(t->door.img));
}
