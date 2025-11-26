/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:21:06 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/26 21:07:01 by rafasant         ###   ########.fr       */
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
# define LM 1 // LEFT MOUSE BUTTON
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_MAP 109 //M
# define KEY_CTRL 65507
# define KEY_SPACEBAR 32
# define KEY_INTERACT 101 //E
# define KEY_SHOOT 113 //Q
# define KEY_PAUSE 112 //P
# define FOV 0.99
# define MARGIN 0.3
# define WIDTH 3840 // if < 640, default 640
# define HEIGHT 2160 // if < 360, default 360
# define ERROR_IMAGE_ADDR "Error retrieving new image address."
# 	ifndef MAP
# 		define MAP_PLAYER 0x00FF00FF
# 		define MAP_WALL 0x00404040
# 		define MAP_FLOOR 0x00A0A0A0
# 		define MAP_DOOR 0x00E0A0E0
# 		define MAP_FIRE 0x00E64600
# 		define MINIMAP_RADIUS 3
# 	endif
# define debug(info, x) _Generic((x), int: print_int, long: print_long, double: print_double, float: print_float,char: print_char, char *: print_string, void *: print_pointer)(info, x) //TODO remove this

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

typedef struct s_offsets
{
	int	start_y;
	int	end_y;
	int start_x;
	int end_x;
	int	radius;
}				t_offsets;

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

typedef struct s_hose
{
	int 	x;
	int		y;
	bool	on;
	bool	power;
	t_image	curr_hose;
}       		t_hose;

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
	t_hose		*hose;
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
	bool		door;
	bool		transparent;
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
	double		x;
	double		y;
	double		dist;
	int			frame;
	double		frame_time;
	double		anim_speed;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			height;
	int			width;
	int			draw_start_x;
	int			draw_end_x;
	int			draw_start_y;
	int			draw_end_y;
	int			dissip;
	bool		active;
	t_image		img;
}       		t_sprite;

typedef struct s_door 
{
	int		x;
	int		y;
	double	open_amount;
	int		opening;
	double	offset;
	double	dist;
}				t_door;

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
	t_texture	door;
}       		t_textures;

typedef struct s_map_objects
{
	int			player_count;
	int			map_width;
	int			map_height;
	char		**map;
	int			sprite_count;
	int			door_count;
	double		*zbuff;
	t_sprite	*sprites;
	t_door		*doors;
}       		t_map_objects;

typedef struct s_map
{
	int 		x;
	int			y;
	int			map_w;
	int			map_h;
	int			map_x;
	int			map_y;
	int			cell_size;
	int			border;
	t_image		map;
	t_offsets	offsets;
}       		t_map;

typedef struct s_hud
{
	t_hose		hose;
	t_map		minimap;
	t_map		full_map;
}				t_hud;

typedef struct s_screens
{
	t_hud		hud;
	t_image		canva;
	t_image		start;
	t_image		pause;
	t_image		death;
	t_image		finish;
}				t_screens;

typedef	struct s_game
{
	int			image_x;
	int			image_y;
	int			game_width;
	int			game_height;
	bool		paused;
	bool		open_map;
	t_xvar		*mlx;
	t_win_list	*win;
}				t_game;

/*---------- parse_file.c ----------*/
void	check_filename(char *file);
t_file	*get_file_content(char *file);
char	*get_texture_path(char *line);
void	get_texture(t_orientation orien, char *line);
void	assign_colour(t_identifier ident, int *rgb);
void	get_colour(t_identifier ident, char *line);
int		check_element(char *line);
void 	parse_textures_colours(t_file **content);
void	parse_file(char *file);

/*---------- static_structs.c ----------*/
t_game			*game(void);
t_screens		*screens(void);
t_player		*player(void);
t_textures		*textures(void);
t_map_objects	*map_objects(void);
t_raycast		*raycast(void);
t_draw			*draw(void);
t_frame			*frame(void);

/*---------- resolution.c ----------*/
int 	get_frame_extents(int *w_frame_size);
int		get_work_area(t_res *display);
void	fit_aspect_ratio(t_res *display, t_res *window, int *game_width, int *game_height);
void	calculate_game_resolution(t_game *game);

/*---------- resolution_helpers.c ----------*/
void	get_window_size(t_res *display, t_res *window);
int		gcd(int a, int b);
void 	get_aspect_ratio(t_res *display);

/*---------- prepare_resources.c ----------*/
void	prepare_resources();

/*---------- full_map.c ----------*/
void    draw_full_map(t_map *full_map, t_map_objects *map_objs, t_player *player);
void	create_full_map(t_map *full_map, t_map_objects *map_objs, t_player *player);

/*---------- minimap.c ----------*/
void 	draw_minimap(t_map *minimap, t_map_objects *map_objs, t_player *player);
void	calc_minimap_offsets(t_offsets *offsets, t_map_objects *map_objs, t_player *player);
void	create_minimap(t_map *minimap, t_map_objects *map_objs, t_player *player);

/*---------- cells.c ----------*/
float	calc_cell_size(float width1, float height1, float width2, float height2);
int		get_cell_colour(char cell);
void	draw_cell(t_map *map, int x, int y, int colour, int cell);

/*---------- map_border.c ----------*/
int		lerp(int a, int b, float t);
int		gradient_brown(float t);
void	draw_border(t_image *img, int x, int y, int border);

/*------------- hose.c -------------*/
void	create_hose(t_hose *hose);
void	update_hose(t_hose *hose, t_textures *textures);

/*----------- render.c -----------*/
void	render_background(t_image *canva, int game_width, int game_height);
void	render_hud(t_screens *screens, t_map_objects *map_objs, t_player *player);
void	render(void);

/*---------- image_manipulation.c ----------*/
int		create_rgb(int r, int g, int b);

/*----------- screens.c -----------*/
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
int		game_state();
void	open_window(void);
void	put_img_to_img(t_image *dst, t_image *src, int x, int y);
unsigned int	get_pixel_colour(t_image *img, int x, int y);

/*---------- prepare_resources.c ----------*/
void	load_textures(t_textures *textures);
void	create_screens(t_screens *screens);
void	prepare_resources(void);

/*---------- images.c ----------*/
void	new_image(t_image *img, int width, int height);
void	copy_image(t_image *dest, t_image *src);
void	resize_image(t_image *image, int ratio);
int		calc_zoom_ratio(t_image *img, int game_height);
void	scale_hose_images(t_textures *texs);

/*---------- mouse.c ----------*/
void	lock_mouse();
void	unlock_mouse();
int		center_mouse(t_game *game, int *last_x, int x);
int		mouse_movement(int x, int y, t_game *game);
int 	mouse_press(int button, int mouse_x, int mouse_y, t_game *game);
int 	mouse_release(int button, int mouse_x, int mouse_y, t_game *game);

/*---------- background.c ----------*/
int		create_rgb(int r, int g, int b);
void	put_pixel(t_image *img, int x, int y, int color);

/*---------- hooks.c ----------*/
int	key_press(int keycode, void *param);
int	key_release(int keycode, void *param);

/*---------- map_parse.c ----------*/
void	init_map_objects();
void	assign_map_lines(t_file *cub_file);
void	allocate_map(t_file	*cub_file);
int		map_parse(t_file *cub_file);
char	*convert_line(char *old_line);
void	valid_map(char **map);
char	**empty_array(void);
int		validate_characters(char **map);
int		flood_fill(char **map, int x, int y, char **visited);
void	initial_orientation(char ori, int x, int y);
void	free_array(char **array);
int		is_bounded_by_walls(char **map, int height);
void	raycast_init(double dir_x, double dir_y, double plane_x, double plane_y);

/*---------- map_parse.c ----------*/
void	print_int(char *info, int data); //TODO remove this
void	print_long(char *info, long data); //TODO remove this
void	print_double(char *info, double data); //TODO remove this
void	print_float(char *info, float data); //TODO remove this
void	print_char(char *info, char data); //TODO remove this
void	print_string(char *info, char *data); //TODO remove this
void	print_pointer(char *info, void *data); //TODO remove this

/*---------- raycaster.c ----------*/
void    raycaster(t_game *game, t_raycast *raycast, t_player *player, t_draw *draw);
void	calculate_delta_dist(t_raycast *raycast, t_player *player);
void	calculate_side_dist(t_raycast *raycast, t_player *player);
void	dda(t_raycast *raycast, t_map_objects *map_objects);
void	calculate_wall(t_raycast *raycast, t_draw *draw, t_player *player, t_game *game);
t_texture	calculate_texture(t_map_objects *mo, t_raycast *raycast, t_textures *textures, t_draw *draw);
int	get_tex_color(int tex_x, int tex_y, t_texture *text);
void	draw_tex_pixel(t_draw *draw, t_screens *screen, t_texture tex, int x);
double get_door_open_amount(t_map_objects *mo, int x, int y);
t_door	*find_door(int max, t_door *d, int x, int y);

/*---------- frame_managment.c ----------*/
double	get_time(void);
void	get_speed_modifiers(t_frame *frame);
void	rotate_camera(t_player *player, double rot_speed);
void	check_movement(t_player *player, t_map_objects *mo, t_frame *frame);

/*---------- fire_sprites.c ----------------*/
void	render_fire_sprites(t_game *g, t_map_objects *mo, t_sprite *s, double delta);
void	animate_doors(t_door *d, t_map_objects *mo, t_player *p, double delta);

/*---------- lost ----------------*/


#endif
