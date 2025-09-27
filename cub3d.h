/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:21:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/27 17:06:24 by rafasant         ###   ########.fr       */
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


typedef enum s_identifier
{
	WALL,
	CEILING,
	FLOOR,
	DOOR,
}				t_identifier;

typedef struct s_file
{
	char			*line;
	t_line_type		line_type;
	struct s_file	*next;
}       		t_file;



typedef struct s_img
{
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_len;
	char	*addr;
	void	*img_ptr;
}					t_img;

typedef struct s_tool
{

}				t_tool;

typedef struct s_player
{
	// int		run;
	double			x;
	double			y;
	t_orientation	orient;
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
	t_texture	wall[4];
	t_texture	door[3];
	t_texture	ceiling;
	t_texture	floor;
	int			ccolour;
	int			fcolour;
}       		t_textures;

typedef struct s_map_objects
{
	int     player_count;
	int     map_width;
	int     map_height;
	char    **map;
	t_player	player;
}       		t_map_objects;

typedef	struct s_game
{
	void	*mlx;
	void	*win;
	t_img	*img;
	int		width;
	int		height;
}				t_game;

/*---------- parse_file.c ----------*/
void	parse_file(char *file);

/*---------- static_structs.c ----------*/
t_map_objects	*map_objects(void);
t_player	*player(void);
t_textures	*textures(void);
t_game	*game(void);


/*---------- window.c ----------*/
void	open_window(void);

/*---------- background.c ----------*/
int		create_rgb(int r, int g, int b);
void	put_pixel(t_img *img, int x, int y, int color);
void	fill_background(int width, int height);

/*---------- map_parse.c ----------*/
void	init_map_objects();
void	assign_map_lines(t_file *cub_file);
void	allocate_map(t_file	*cub_file);
int	map_parse(t_file *cub_file);
char	*convert_line(char *old_line);
int	valid_map(char **map);
char	**empty_array(void);
int	validate_characters(char **map);
int	is_bounded_by_walls(char **map, int x, int y, char **visited);
void	initial_orientation(char ori, int x, int y);
void	free_array(char **array);


#endif
