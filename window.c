/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/27 14:38:35 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_window(void)
{
	game()->width = 1920;
	game()->height = 1080;
	game()->mlx = mlx_init();
	game()->win = mlx_new_window(mlx, game()->img->width, game()->height, "cub3d");
	game()->img->img = mlx_new_image(game()->mlx, game()->width, game()->height);
	game()->img->addr = mlx_get_data_addr(game()->img->img, &game()->img->bpp,
		&game()->img->line_len, &game()->img->endian);
	while (1)
		mlx_loop(game()->mlx);
}

