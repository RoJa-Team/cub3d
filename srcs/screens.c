/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:33:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/26 17:30:54 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_canva(t_image *canva)
{
	new_image(canva, game()->game_width, game()->game_height);
}

void	create_start(t_image *start)
{
	new_image(start, game()->game_width, game()->game_height);
}

void	create_pause(t_image *pause)
{
	new_image(pause, game()->game_width, game()->game_height);
}

void	create_death(t_image *death)
{
	new_image(death, game()->game_width, game()->game_height);
}

void	create_finish(t_image *finish)
{
	new_image(finish, game()->game_width, game()->game_height);
}
