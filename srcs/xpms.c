/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:04:01 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/10 22:13:33 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	xpm_to_img(char *path, t_image *img)
{
	img->img_ptr = mlx_xpm_file_to_image(game()->mlx, \
	path, &img->w, &img->h);
	if (img->img_ptr == NULL)
		return ((void)catch()->set("Error\n%s: Error loading xpm {%s}.", __func__, path), deallocate());
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, \
	&img->line_len, &img->endian);
	if (img->img_ptr == NULL)
		return ((void)catch()->set("Error\n%s: Error retrieving image address.", __func__), deallocate());
}

void	load_textures_wall()
{
	xpm_to_img(textures()->wall[NO].path, &textures()->wall[0].img);
	xpm_to_img(textures()->wall[SO].path, &textures()->wall[1].img);
	xpm_to_img(textures()->wall[WE].path, &textures()->wall[2].img);
	xpm_to_img(textures()->wall[EA].path, &textures()->wall[3].img);
}

void	load_textures_fire()
{
	xpm_to_img("textures/edited/fire_loop1.xpm", &(textures()->fire_loop[0].img));
	xpm_to_img("textures/edited/fire_loop2.xpm", &(textures()->fire_loop[1].img));
	xpm_to_img("textures/edited/fire_loop3.xpm", &(textures()->fire_loop[2].img));
	xpm_to_img("textures/edited/fire_loop4.xpm", &(textures()->fire_loop[3].img));
	xpm_to_img("textures/edited/fire_loop5.xpm", &(textures()->fire_loop[4].img));
	xpm_to_img("textures/edited/fire_loop6.xpm", &(textures()->fire_loop[5].img));
	xpm_to_img("textures/edited/fire_loop7.xpm", &(textures()->fire_loop[6].img));
	xpm_to_img("textures/edited/fire_loop8.xpm", &(textures()->fire_loop[7].img));
	xpm_to_img("textures/edited/burning_end_1.xpm", &(textures()->fire_ending[0].img));
	xpm_to_img("textures/edited/burning_end_2.xpm", &(textures()->fire_ending[1].img));
	xpm_to_img("textures/edited/burning_end_3.xpm", &(textures()->fire_ending[2].img));
	xpm_to_img("textures/edited/burning_end_4.xpm", &(textures()->fire_ending[3].img));
	xpm_to_img("textures/edited/burning_end_5.xpm", &(textures()->fire_ending[4].img));
}

void	load_textures_hose()
{
	xpm_to_img("textures/edited/hose.xpm", &(textures()->idle_hose.img));
	xpm_to_img("textures/edited/hose_firing1.xpm", &(textures()->hose_start[0].img));
	xpm_to_img("textures/edited/hose_firing2.xpm", &(textures()->hose_start[1].img));
	xpm_to_img("textures/edited/hose_firing3.xpm", &(textures()->hose_start[2].img));
	xpm_to_img("textures/edited/hose_firing4.xpm", &(textures()->hose_start[3].img));
	xpm_to_img("textures/edited/hose_firing5.xpm", &(textures()->hose_firing[0].img));
	xpm_to_img("textures/edited/hose_firing6.xpm", &(textures()->hose_firing[1].img));
	xpm_to_img("textures/edited/hose_firing7.xpm", &(textures()->hose_firing[2].img));
	xpm_to_img("textures/edited/hose_firing8.xpm", &(textures()->hose_firing[3].img));
	xpm_to_img("textures/edited/hose_firing9.xpm", &(textures()->hose_firing[4].img));
	xpm_to_img("textures/edited/hose_firing10.xpm", &(textures()->hose_firing[5].img));
	xpm_to_img("textures/edited/hose_firing11.xpm", &(textures()->hose_firing[6].img));
	xpm_to_img("textures/edited/hose_firing12.xpm", &(textures()->hose_firing[7].img));
	xpm_to_img("textures/edited/hose_ending1.xpm", &(textures()->hose_ending[0].img));
	xpm_to_img("textures/edited/hose_ending2.xpm", &(textures()->hose_ending[1].img));
	xpm_to_img("textures/edited/hose_ending3.xpm", &(textures()->hose_ending[2].img));
	xpm_to_img("textures/edited/hose_ending4.xpm", &(textures()->hose_ending[3].img));
	xpm_to_img("textures/edited/hose_ending5.xpm", &(textures()->hose_ending[4].img));
	xpm_to_img("textures/edited/hose_ending6.xpm", &(textures()->hose_ending[5].img));
	xpm_to_img("textures/edited/hose_ending7.xpm", &(textures()->hose_ending[6].img));
	xpm_to_img("textures/edited/hose_ending8.xpm", &(textures()->hose_ending[7].img));
}

void	load_textures_misc()
{
	xpm_to_img("textures/edited/door_closed.xpm", &(textures()->door[0].img));
	xpm_to_img("textures/edited/door_semi_open.xpm", &(textures()->door[1].img));
	xpm_to_img("textures/edited/door_open.xpm", &(textures()->door[2].img));
	xpm_to_img("textures/edited/clouds.xpm", &(textures()->clouds.img));
}
