/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:29:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/01 21:57:45 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef enum e_line_type
{
	TEXTURE;
	COLOR;
	MAP;
}	t_line_type;

typedef struct s_cub_file
{
	char	*line;
	t_line_type	line_type;
	s_cub_file	*next;
}	t_cub_file;

typedef struct s_map_objects
{
	int	player;
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
}

int	map_parse(char *cub_file)
{
	get_map();
	if (map_objects->map)
	{
		if (!valid_map(map_objects()->map))
		{
			free_map(map_objects()->map);
			free(map_objects());
			return (1);
		}
	}
	return (0);
}

void	get_map(void)
{
	allocate_map();
	if (!map_objects()->map)
		return ;
	assign_map_lines();
	close(fd);
}

void	allocate_map(int fd)
{
	t_file	cub_file;
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
		map_objects()->map[row] = malloc(sizeof(char) * map_objects()->map_width + 1);
		map_objects()->map[row] = cub_file->line;
		row++;
		cub_file = cub_file->next;
	}
}
