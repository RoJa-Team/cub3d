/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:29:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/09/28 16:38:03 by joafern2         ###   ########.fr       */
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
	temp = cub_file;
	while (row < map_objects()->map_height && temp)
	{
		map_objects()->map[row] = convert_line(temp->line);
		row++;
		temp = temp->next;
	}
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
	map_objects()->map = malloc(sizeof(char *) * map_objects()->map_height + 1);
	if (!map_objects()->map)
	{
		ft_printf("Memory allocation error *allocate_map*\n");
		return ;
	}
}

int	map_parse(t_file *cub_file)
{
	allocate_map(cub_file);
	assign_map_lines(cub_file);
	if (map_objects()->map)
	{
		if (!valid_map(map_objects()->map))
			free_array(map_objects()->map);
	}
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

int	valid_map(char **map)
{
	char	**empty_arr;

	if (!validate_characters(map) || map_objects()->player_count != 1)
	{
		ft_printf("Invalid or missing characters on the map\n");
		return (0);
	}
	empty_arr = empty_array();
	if (!flood_fill(map, map_objects()->player.x, map_objects()->player.y, empty_arr)
			|| !is_bounded_by_walls(map, map_objects()->map_height))
	{
		ft_printf("Map is not bounded by walls\n");
		return (free_array(empty_arr), 0);
	}
	return (free_array(empty_arr), 1);
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
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'F' || map[i][j] == 'D' || ft_isspace(map[i][j]) || map[i][j] == '\0')
				continue ;
			else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				initial_orientation(map[i][j], i, j);
			else
				return (0);
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
		j = -1;
		while (map[i][++j])
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
		}

	}
	return (1);
}

int	flood_fill(char **map, int x, int y, char **visited)
{
	if (x < 0 || x >= map_objects()->map_height || y < 0 || y >= map_objects()->map_width)
		return (0);
	if (ft_isspace(map[x][y]))
		return (0);
	if (map[x][y] == '1' || visited[x][y])
		return (1);
	visited[x][y] = 1;
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

void	initial_orientation(char ori, int x, int y)
{
	if (ori == 'N')
		map_objects()->player.orient = NO;
	else if (ori == 'S')
		map_objects()->player.orient = SO;
	else if (ori == 'E')
		map_objects()->player.orient = EA;
	else if (ori == 'W')
		map_objects()->player.orient = WE;
	map_objects()->player_count++;
	map_objects()->player.x = x;
	map_objects()->player.y = y;
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
