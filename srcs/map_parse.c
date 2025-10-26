/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:29:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/10/24 23:21:46 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_objects()
{
	map_objects()->player_count = 0;
	map_objects()->map_width = 0;
	map_objects()->map_height = 0;
	map_objects()->map = NULL;
}

void	assign_map_lines(t_file *cub_file)
{
	int	row;
	t_file	*temp;

	row = 0;
	while (row < map_objects()->map_height && cub_file)
	{
		temp = cub_file;
		map_objects()->map[row] = convert_line(temp->line);
		row++;
		cub_file = temp->next;
		if (temp->line)
			free(temp->line);
		free(temp);
	}
	map_objects()->map[row] = NULL;
}

void	allocate_map(t_file	*cub_file)
{
	int	width;
	t_file	*temp;

	temp = cub_file;
	while (temp)
	{
		width = ft_strlen(temp->line);
		if (map_objects()->map_width < width)
			map_objects()->map_width = width;
		map_objects()->map_height++;
		temp = temp->next;
	}
	map_objects()->map = malloc(sizeof(char *) * (map_objects()->map_height + 1));
	if (!map_objects()->map)
		return ((void)catch()->set("Error\n%s: Memory allocation error", __func__), deallocate());
}

int	map_parse(t_file *cub_file)
{
	allocate_map(cub_file);
	assign_map_lines(cub_file);
	if (map_objects()->map)
		valid_map(map_objects()->map);
	else
		return (1);
	return (0);
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

void	valid_map(char **map)
{
	char	**empty_arr;

	if (!validate_characters(map) || map_objects()->player_count != 1)
		return ((void)catch()->set("Error\n%s: Invalid or missing characters on the map", __func__), deallocate());
	empty_arr = empty_array();
	if (!flood_fill(map, player()->x, player()->y, empty_arr)
			|| !is_bounded_by_walls(map, map_objects()->map_height))
		return (free_array(empty_arr), (void)catch()->set("Error\n%s: Map is not bounded by walls", __func__), deallocate());
	return (free_array(empty_arr));
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
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'F' || map[i][j] == 'D' || ft_isspace(map[i][j]))
			{
				j++;
				continue ;
			}
			else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				initial_orientation(map[i][j], i, j);
			else
				return (0);
			j++;
		}
	}
	return (1);
}

int	is_bounded_by_walls(char **map, int height)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (i == 0 && map[i][j] == '0')
					return (0);
			else if (i == (height - 1) && map[i][j] == '0')
				return (0);
			else if (j == 0 && map[i][j] == '0')
				return (0);
			else if (map[i][j] == '0' && (map[i][j + 1] == '\0' || map[i][j + 1] == '\n' || map[i][j + 1] == ' '))
				return (0);
			else if (map[i][j] == '0' && (ft_isspace(map[i - 1][j]) || ft_isspace(map[i + 1][j]) || ft_isspace(map[i][j - 1]) || ft_isspace(map[i][j + 1])))
				return (0);
			j++;
		}
	}
	return (1);
}

int	flood_fill(char **map, int x, int y, char **visited)
{
	if (y < 0 || y >= map_objects()->map_height || x < 0 || x >= map_objects()->map_width)
		return (0);
	if (ft_isspace(map[y][x]))
		return (0);
	if (map[y][x] == '1' || visited[y][x])
		return (1);
	visited[y][x] = 1;
	if (!flood_fill(map, x + 1, y, visited))
		return (0);
	if (!flood_fill(map, x, y + 1, visited))
		return (0);
	if (!flood_fill(map, x - 1, y, visited))
		return (0);
	if (!flood_fill(map, x, y - 1, visited))
		return (0);
	return (1);
}

void	raycast_init(double dir_x, double dir_y, double plane_x, double plane_y)
{
	player()->dir_x = dir_x;
	player()->dir_y = dir_y;
	player()->plane_x = plane_x;
	player()->plane_y = plane_y;
}

void	initial_orientation(char ori, int y, int x)
{
	if (ori == 'N')
		raycast_init(0, -1, -FOV, 0);
	else if (ori == 'S')
		raycast_init(0, 1, FOV, 0);
	else if (ori == 'E')
		raycast_init(1, 0, 0, FOV);
	else if (ori == 'W')
		raycast_init(-1, 0, 0, -FOV);
	map_objects()->player_count++;
	player()->x = x + 0.5;
	player()->y = y + 0.5;
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
