/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:21:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/03 19:50:57 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "catch.h"

typedef enum e_line_type
{
	TEXTURE;
	COLOR;
	MAP;
}	t_line_type;

typedef enum e_orientation
{
	NO;
	EA
	SO;
	WE;
}	t_orientation;

typedef struct s_cub_file
{
	char	*line;
	t_line_type	line_type;
	s_cub_file	*next;
}	t_cub_file;

typedef struct s_map_objects
{
	int	player;
	t_orientation	orientation;
	int	player_x;
	int	player_y;
	int	map_width;
	int	map_height;
	char	**map;
}	t_map_objects;

#endif
