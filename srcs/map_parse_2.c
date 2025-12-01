/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:52:10 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 15:52:12 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_map_lines(t_file *cub_file)
{
	int		row;
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
	int		width;
	t_file	*temp;

	temp = cub_file;
	while (temp)
	{
		width = ft_strlen_c(temp->line, '\n');
		if (map_objects()->map_width < width)
			map_objects()->map_width = width;
		map_objects()->map_height++;
		temp = temp->next;
	}
	map_objects()->map = malloc(sizeof(char *)
		* (map_objects()->map_height + 1));
	if (!map_objects()->map)
		return ((void)catch()->set(
				"Error\n%s: Memory allocation error", __func__), deallocate());
}

char	*convert_line(char *old_line)
{
	int		i;
	char	*new_line;

	i = -1;
	new_line = ft_calloc(sizeof(char), map_objects()->map_width + 1);
	while (old_line[++i] != '\0' && old_line[i] != '\n')
		new_line[i] = old_line[i];
	while (i < map_objects()->map_width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	sprite_door_count(char **map, int i, int j)
{
	if (map[i][j] == 'F')
		map_objects()->sprite_count++;
	else if (map[i][j] == 'D')
		map_objects()->door_count++;
}

int	is_not_wall(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'F' || map[i][j] == 'D')
		return (1);
	else
		return (0);
}
