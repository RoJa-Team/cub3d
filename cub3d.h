/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:21:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/14 23:15:23 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/Xatom.h>
# include <sys/time.h>
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
# define CELL_SIZE 16
# define FOV 0.99
# define TEX_FIRE 1
# define MARGIN 0.3
# define WIDTH 3840 // if < 640, default 640
# define HEIGHT 2160 // if < 360, default 360
# define ERROR_IMAGE_ADDR "Error retrieving new image address."
# define debug(info, x) _Generic((x), int: print_int, long: print_long, double: print_double, char: print_char, char *: print_string, void *: print_pointer)(info, x) //TODO remove this

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_res
{
	int	width;
	int	height;
	int	aspect_width;
	int	aspect_height;
}				t_res;

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
}				t_image;

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
	int			move_left;
	int			move_right;
	int			move_front;
	int			move_back;
	int			turn_left;
	int			turn_right;
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

typedef struct s_frame
{
	double			move_speed;
	double			rot_speed;
	double			frame_time;
}			t_frame;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
	int			frame;
	double			frame_time;
	double			anim_speed;
	double			transform_x;
	double			transform_y;
	int			screen_x;
	int			height;
	int			width;
	int			draw_start_x;
	int			draw_end_x;
	int			draw_start_y;
	int			draw_end_y;
}       		t_sprite;

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
	t_texture	hose_idle;
	t_texture	hose_start[4];
	t_texture	hose_on[8];
	t_texture	hose_end[8];
	t_texture	fire_loop[8];
	t_texture	fire_end[5];
	t_texture	wall[4];
	t_texture	door[3];
}       		t_textures;

typedef struct s_map_objects
{
	int     player_count;
	int     map_width;
	int     map_height;
	char    **map;
	int	sprite_count;
	double	*zbuff;
	t_sprite	*sprites;
	t_player	player;
}       		t_map_objects;

typedef struct s_hud
{
	int 	x;
	int		y;
	t_image	img;
}				t_hud;

typedef struct s_screens
{
	t_hud	hose;
	t_hud	minimap;
	t_image	canva;
	t_image	start;
	t_image	pause;
	t_image	death;
	t_image	finish;
}				t_screens;

typedef	struct s_game
{
	int			image_x;
	int			image_y;
	int			game_width;
	int			game_height;
	bool		paused;
	t_xvar		*mlx;
	t_win_list	*win;
}				t_game;

/*---------- parse_file.c ----------*/
void	parse_file(char *file);

/*---------- static_structs.c ----------*/
t_game			*game(void);
t_screens		*screens(void);
t_player		*player(void);
t_textures		*textures(void);
t_map_objects	*map_objects(void);
t_raycast			*raycast(void);
t_draw		*draw(void);
t_frame		*frame(void);
t_sprite *sprite(void);

/*---------- resolution.c ----------*/
int get_frame_extents(int *w_frame_size);
int	get_work_area(t_res *display);
void	fit_aspect_ratio(t_res *display, t_res *window, int *game_width, int *game_height);
void	calculate_game_resolution(t_game *game);

/*---------- resolution_helpers.c ----------*/
void	get_window_size(t_res *display, t_res *window);
int	gcd(int a, int b);
void get_aspect_ratio(t_res *display);

/*---------- prepare_resources.c ----------*/
void	prepare_resources();

/*---------- hud.c ----------*/
void	create_hose(t_hud *hose);
void	create_minimap(t_hud *minimap);
void	render_hud(t_screens *screens);


/*---------- render.c ----------*/
void	render_background(t_image *canva, int game_width, int game_height);

void	render();


/*---------- image_manipulation.c ----------*/
int	create_rgb(int r, int g, int b);

/*---------- screens.c ----------*/
void	create_canva(t_image *canva);
void	create_start(t_image *start);
void	create_pause(t_image *pause);
void	create_death(t_image *death);
void	create_finish(t_image *finish);


/*---------- xpms.c ----------*/
void	xpm_to_img(char *path, t_image *img);
void	load_textures_wall(t_textures *textures);
void	load_textures_fire(t_textures *textures);
void	load_textures_hose(t_textures *textures);
void	load_textures_misc(t_textures *textures);
void	put_pixel_img(t_image *img, int x, int y, int color);

/*---------- clear.c ----------*/
void	free_texture(t_texture *texture);
void	deallocate(void);
int		close_game(void *param);

/*---------- clear_textures.c ----------*/
void	free_textures_wall(t_textures *textures);
void	free_textures_fire(t_textures *textures);
void	free_textures_hose(t_textures *textures);
void	free_textures_misc(t_textures *textures);
void	free_textures(t_textures *textures);

/*---------- window.c ----------*/
int	game_state();
void	open_window(void);
void put_img_to_img_quadrants(t_image *dst, t_image *src, int x, int y);
void	put_img_to_img(t_image *dst, t_image *src, int x, int y);
unsigned int	get_pixel_colour(t_image *img, int x, int y);

/*---------- prepare_resources.c ----------*/
void	create_canva();


/*---------- images.c ----------*/
void	new_image(t_image *img, int width, int height);
void	copy_image(t_image *dest, t_image *src);
void	resize_image(t_image *image, int ratio);
int		calc_zoom_ratio(t_image *img, int game_height);
void	scale_hose_images(t_textures *texs);

/*---------- mouse.c ----------*/
int		lock_mouse();
int		unlock_mouse();
int		mouse_hooks(int keycode, void *param);


/*---------- background.c ----------*/
int		create_rgb(int r, int g, int b);
void	put_pixel(t_image *img, int x, int y, int color);

/*---------- hooks.c ----------*/
int	key_hooks(int keycode, void *param);
int	key_release(int keycode, void *param);

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
void	print_long(char *info, long data); //TODO remove this
void	print_double(char *info, double data); //TODO remove this
void	print_char(char *info, char data); //TODO remove this
void	print_string(char *info, char *data); //TODO remove this
void	print_pointer(char *info, void *data); //TODO remove this

/*---------- raycaster.c ----------*/
void    raycaster(t_game *game, t_raycast *raycast, t_player *player, t_draw *draw);
void	calculate_delta_dist(t_raycast *raycast, t_player *player);
void	calculate_side_dist(t_raycast *raycast, t_player *player);
void	dda(t_raycast *raycast, t_map_objects *map_objects);
void	calculate_wall(t_raycast *raycast, t_draw *draw, t_player *player, t_game *game);
void	calculate_texture(int x, t_raycast *raycast, t_textures *textures, t_draw *draw);
int	get_tex_color(int tex_x, int tex_y, t_texture *text);
void	draw_tex_pixel(t_draw *draw, t_screens *screen, t_texture tex, int x);

/*---------- frame_managment.c ----------*/
double	get_time(void);
void	get_speed_modifiers(t_frame *frame);
void	turn_left(t_player *player, t_frame *frame);
void	turn_right(t_player *player, t_frame *frame);
void	move_right(t_player *player, t_map_objects *map_objects, t_frame *frame);
void	move_left(t_player *player, t_map_objects *map_objects, t_frame *frame);
void	move_front(t_player *player, t_map_objects *map_objects, t_frame *frame);
void	move_back(t_player *player, t_map_objects *map_objects, t_frame *frame);


/*---------- lost ----------------*/
void	add_background(int game_width, int game_height);
void	add_view();


void	render_fire_sprites(t_game *g, t_map_objects *mo, t_sprite *s, double delta);

#endif
