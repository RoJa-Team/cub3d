/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:29:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/03 21:41:42 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_cub_file	*cub_file(void)
{
	static	t_cub_file map_objects;

	return (&cub_file);
}

t_map_objects	*map_objects(void)
{
	static	t_map_objects map_objects;

	return (&map_objects);
}

void	init_map_objects()
{
	map_objects() = malloc(sizeof(t_game_objects));
	if (!map_objects())
	{
		ft_printf("Memory allocation error *init_map_objects\n");
		return (0);
	}
	map_objects()->player = 0;
	map_objects()->player_x = 0;
	map_objects()->player_y = 0;
	map_objects()->map_width = 0;
	map_objects()->map_height = 0;
	map_objects()->map = NULL;
	map_objects()->orientation = NULL;
}

int	map_parse(char *cub_file)
{
	allocate_map();
	assign_map_lines();
	if (map_objects->map)
	{
		if (!valid_map(map_objects()->map))
		{
			free_array(map_objects()->map);
			free(map_objects());
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

void	allocate_map(int fd)
{
	t_file	*cub_file;
	int	width;

	cub_file = file();
	while (cub_file != NULL)
	{
		if (cub_file->type == MAP)
			break ;
		cub_file = cub_file->next;
	}
	while (cub_file && cub_file->type == MAP)
	{
		width = ft_strlen(cub_file->line);
		if (map_objects()->map_width < width)
			map_objects()->map_width = width;
		map_objects()->map_height++;
		cub_file = cub_file->next;
	}
	map_objects()->map = malloc(sizeof(char *) * map_objects()->map_height + 1);
	if (!map_objects()->map)
	{
		ft_printf("Memory allocation error *allocate_map*\n");
		return ;
	}
}

void	assign_map_lines(int fd)
{
	int	row;
	int	size;
	t_file	cub_file;

	row = 0;
	cub_file = file();
	while (cub_file != NULL)
	{
		if (cub_file->type == MAP)
			break ;
		cub_file = cub_file->next;
	}
	while (row < map_objects()->map_height && cub_file)
	{
		map_objects()->map[row] = convert_line(cub_file->line);
		row++;
		cub_file = cub_file->next;
	}
}

char	*convert_line(char *old_line)
{
	int	i;
	char	*new_line;

	i = -1;
	new_line = ft_calloc(sizeof(char),  map_objects()->map_width + 1);
	while (old_line[++i])
		new_line[i] = old_line[i];
	while (i <= map_objects()->map_width)
	{
		new_line[i] = ' ';
		i++;
	}
	return (new_line);
}

int	valid_map(char **map)
{
	char	**empty_array;

	if (!validate_characters(map) || map_objects()->player != 1)
	{
		ft_printf("Invalid or missing characters on the map\n");
		return (0);
	}
	empty_array = empty_array();
	if (!is_bounded_by_walls(map, map_objects()->player_x, map_objects()->player_y), empty_array)
	{
		ft_printf("Map is not bounded by walls\n");
		return (free_array(empty_array), 0);
	}
	return (free_array(empty_array), 1);
}

char	**empty_array(void)
{
	char	**empty_array;
	int	i;

	i = -1;
	empty_array = ft_calloc(sizeof(char *), map_objects()->map_height + 1);
	while (++i < map_objects()->map_height)
		empty_array[i] = ft_calloc(sizeof(char), map_objects()->map_width + 1);
	return (empty_array);
}


int	validate_characters(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == )
				continue ;
			else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				initial_orientation(map[i][j], i, j);
			else
				return (0);
		}
	}
	return (1);
}

int	is_bounded_by_walls(char **map, int x, int y, int **visited)
{
	if (x < 0 || x >= map_objects()->map_height || y < 0 || y >= map_objects()->map_width)
		return (0);
	if (map[x][y] == ' ')
		return (0);
	if (map[x][y] == '1' || visited[x][y])
		return (1);
	visited[x][y] = 1;
	if (!is_bounded_by_walls(map, x+1, y, visited))
		return (0);
	if (!is_bounded_by_walls(map, x, y+1, visited))
		return (0);
	if (!is_bounded_by_walls(map, x-1, y, visited))
		return (0);
	if (!is_bounded_by_walls(map, x, y-1, visited))
		return (0);
	return (1);
}

void	initial_orientation(char ori, int x, int y)
{
	if (ori == 'N')
		map_objects->orientation = NO;
	else if (ori == 'S')
		map_objects->orientation = SO;
	else if (ori == 'E')
		map_objects->orientation = EA;
	else if (ori == 'W')
		map_objects->orientation = WE;
	map_objects()->player++;
	map_objects()->player_x = x;
	map_objects()->player_y = y;
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
