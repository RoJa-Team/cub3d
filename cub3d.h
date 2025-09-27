/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:21:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/27 14:38:24 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "catch_lib/catch.h"
# include "minilibx/mlx.h"

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef enum e_line_type
{
	TEXTURE,
	COLOR,
	MAP
}       		t_line_type;

typedef enum e_orientation
{
	NO,
	SO,
	WE,
	EA
}       		t_orientation;


// typedef enum s_identifier
// {
// 	WALL,
// 	CEILING,
// 	FLOOR,
// 	DOOR,
// }				t_identifier;

typedef struct s_file
{
	char			*line;
	t_line_type		line_type;
	struct s_file	*next;
}       		t_file;

typedef	struct s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	int	width;
	int	height;
}

typedef struct s_img
{
	int	w;
	int	h;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}					t_img;

typedef struct s_tool
{

}				t_tool;

typedef struct s_player
{
	// int		run;
	double			x;
	double			y;
	t_tool			*tool;
}				t_player;

typedef struct s_texture
{
	char			*path;
	t_img			img;
	t_orientation	orient;
}       		t_texture;

typedef struct s_textures
{
	t_texture	*wall;
	t_texture	*door_open;
	t_texture	*door_closed;
	int		*ceiling_color;
	int		*floor_color;
}       		t_textures;

typedef struct s_map_objects
{
	int     player;
	int     map_width;
	int     map_height;
	char    **map;
}       		t_map_objects;

/*---------- static_structs.c ----------*/
t_map_objects	*map_objects(void);
t_player	*player(void);
t_textures	*textures(void);
t_game	*game(void);


/*---------- window.c ----------*/
void	open_window(void);

/*---------- background.c ----------*/

#endif
