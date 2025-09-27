/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:32:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/27 16:45:51 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_window(void)
{
	game()->width = 1920;
	game()->height = 1080;
	game()->mlx = mlx_init();
	game()->win = mlx_new_window(game()->mlx, game()->width, game()->height, "cub3d");
	game()->img->img_ptr = mlx_new_image(game()->mlx, game()->width, game()->height);
	game()->img->addr = mlx_get_data_addr(game()->img->img_ptr, &game()->img->bpp,
		&game()->img->line_len, &game()->img->endian);
	while (1)
		mlx_loop(game()->mlx);
}

