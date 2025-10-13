/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:21:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/10/13 19:54:27 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "catch_lib/catch.h"
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include "math.h"

# define KEY_ESC 65307
# define ARROW_L 65361
# define ARROW_R 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_CTRL 65507
# define KEY_SPACEBAR 32
# define KEY_INTERACT 101 //E
# define KEY_SHOOT 113 //Q
# define KEY_PAUSE 112 //P
# define WIDTH 900
# define HEIGHT 900
# define CELL_SIZE 16
# define FOV 0.66
# define TEX_SIZE 32
# define ERROR_IMAGE_ADDR "Error retrieving new image address."
# define debug(info, x) _Generic((x), int: print_int, char *: print_string, void *: print_pointer)(info, x) //TODO remove this

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

typedef struct s_image
{
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_len;
	char	*addr;
	void	*img_ptr;
}					t_image;

typedef struct s_tool
{

}				t_tool;

typedef struct s_player
{
	// int		run;
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	t_tool			*tool;
}				t_player;

typedef struct	s_raycast
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			step_x;
	double			step_y;
	double			side_dist_x;
	double			side_dist_y;
	int			map_x;
	int			map_y;
	int			side;
	int			hit;
	double			perp_wall_dist;
}				t_raycast;


typedef struct	s_draw
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double			wall_x;
	int			tex_x;
	int			tex_y;
	double			step;
	double			tex_pos;
	int			color;
}				t_draw;

typedef struct s_texture
{
	char			*path;
	t_image			img;
	t_orientation	orient;
}       		t_texture;

typedef struct s_textures
{
	int			ccolour;
	int			fcolour;
    	t_texture	clouds;
    	t_texture	idle_hose;
    	t_texture	hose_start[4];
    	t_texture	hose_firing[8];
    	t_texture	hose_ending[8];
    	t_texture	fire_loop[8];
    	t_texture	fire_ending[5];
	t_texture	wall[4];
	t_texture	door[3];
}       		t_textures;

typedef struct s_map_objects
{
	int     player_count;
	int     map_width;
	int     map_height;
	char    **map;
	t_player	player;
}       		t_map_objects;

typedef struct s_screen
{
	t_image	start;
	t_image	canva;
	t_image	pause;
	t_image	death;
	t_image	finish;
	t_image	background;
}				t_screen;

typedef	struct s_game
{
	bool		paused;
	t_xvar		*mlx;
	t_win_list	*win;
}				t_game;

/*---------- parse_file.c ----------*/
void	parse_file(char *file);

/*---------- static_structs.c ----------*/
t_game			*game(void);
t_screen		*screen(void);
t_player		*player(void);
t_textures		*textures(void);
t_map_objects	*map_objects(void);
t_raycast			*raycast(void);
t_draw		*draw(void);

/*---------- xpms.c ----------*/
void	prepare_resources();

/*---------- xpms.c ----------*/
void	xpm_to_img(char *path, t_image *img);
void	load_textures_wall();
void	load_textures_fire();
void	load_textures_hose();
void	load_textures_misc();
void	put_pixel_img(t_image *img, int x, int y, int color);

/*---------- clear.c ----------*/
void	deallocate(void);

int	close_game(void *param);

/*---------- window.c ----------*/
void	open_window(void);

/*---------- prepare_resources.c ----------*/
void	create_canva();
void	create_background();


/*---------- images.c ----------*/
void new_image(t_image *img, int width, int height);

/*---------- mouse.c ----------*/
int		lock_mouse();
int		unlock_mouse();
int		mouse_hooks(int keycode, void *param);


/*---------- background.c ----------*/
int		create_rgb(int r, int g, int b);
void	put_pixel(t_image *img, int x, int y, int color);

/*---------- background.c ----------*/
int	key_hooks(int keycode, void *param);

/*---------- map_parse.c ----------*/
void	init_map_objects();
void	assign_map_lines(t_file *cub_file);
void	allocate_map(t_file	*cub_file);
int	map_parse(t_file *cub_file);
char	*convert_line(char *old_line);
void	valid_map(char **map);
char	**empty_array(void);
int	validate_characters(char **map);
int	flood_fill(char **map, int x, int y, char **visited);
void	initial_orientation(char ori, int x, int y);
void	free_array(char **array);
int	is_bounded_by_walls(char **map, int height);
void	raycast_init(double dir_x, double dir_y, double plane_x, double plane_y);

/*---------- map_parse.c ----------*/
void	print_int(char *info, int data); //TODO remove this
void	print_string(char *info, char *data); //TODO remove this
void	print_pointer(char *info, void *data); //TODO remove this

/*---------- raycaster.c ----------*/
void    raycaster(void);
void	calculate_delta_dist(void);
void	calculate_side_dist(void);
void	dda(void);
void	calculate_wall(void);
void	calculate_texture(void);
int	get_tex_color(int tex_x, int tex_y, t_texture *text);
void	draw_tex_pixel(int x);
#endif
