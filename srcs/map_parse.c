/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:29:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/19 20:33:21 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	valid_map(char **map)
{
	char	**empty_arr;

	if (!validate_characters(map) || map_objects()->player_count != 1)
		return ((void)catch()->set(
				"Error\n%s: Invalid/missing characters on the map", __func__),
			deallocate());
	empty_arr = empty_array();
	if (!flood_fill(map, player()->x, player()->y, empty_arr)
		|| !is_bounded_by_walls(map, map_objects()->map_height))
		return (free_array(empty_arr), (void)catch()->set(
				"Error\n%s: Map is not bounded by walls", __func__),
			deallocate());
	return (free_array(empty_arr));
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
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'F'
				|| map[i][j] == 'D' || ft_isspace(map[i][j]))
				sprite_door_count(map, i, j);
			else if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				initial_orientation(map[i][j], i, j);
			else
				return (0);
			j++;
		}
	}
	return (1);
}

int	flood_fill(char **map, int x, int y, char **visited)
{
	if (y < 0 || y >= map_objects()->map_height
		|| x < 0 || x >= map_objects()->map_width)
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

int	is_bounded_by_walls(char **map, int height)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] && map[i][j] != '\n')
		{
			if (i == 0 && is_not_wall(map, i, j))
				return (0);
			else if (i == (height - 1) && is_not_wall(map, i, j))
				return (0);
			else if (j == 0 && is_not_wall(map, i, j))
				return (0);
			else if (is_not_wall(map, i, j) && (map[i][j + 1] == '\0'
				|| map[i][j + 1] == '\n' || map[i][j + 1] == ' '))
				return (0);
			else if (is_not_wall(map, i, j) && (ft_isspace(map[i - 1][j])
				|| ft_isspace(map[i + 1][j]) || ft_isspace(map[i][j - 1])
				|| ft_isspace(map[i][j + 1])))
				return (0);
		}
	}
	return (1);
}
