/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:31:28 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 17:41:30 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_filename(char *file)
{
	char	*ext;
	int		i;

	i = 0;
	ext = ".cub";
	while (file[i])
		i++;
	i = i - 4;
	while (file[i])
	{
		if (file[i] != *ext)
			return ((void)catch()->set("Error\n%s: File [%s] isn't a .cub file",
					__func__, file), deallocate());
		i++;
		ext++;
	}
}

t_file	*get_file_content(char *file, int fd)
{
	char	*line;
	t_file	*tmp;
	t_file	*content;
	t_file	*new_content;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (catch()->set("Error\n%s: Error opening file", __func__),
			deallocate(), NULL);
	content = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_content = new_file_content(line);
		if (new_content == NULL)
			return (clear_list(content), deallocate(), NULL);
		if (content == NULL)
			content = new_content;
		else
			tmp->next = new_content;
		tmp = new_content;
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

void	parse_textures_colours(t_file **content)
{
	t_file	*tmp;

	while (1)
	{
		tmp = *content;
		if (tmp == NULL || tmp->line == NULL)
			return ;
		if (tmp->line[0] == '\0')
		{
		}
		else
		{
			if (!check_element(tmp->line))
				break ;
		}
		*content = tmp->next;
		if (tmp->line)
			free(tmp->line);
		free(tmp);
	}
}

int	check_element(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		get_texture(NO, &line[2]);
	else if (!ft_strncmp(line, "SO", 2))
		get_texture(SO, &line[2]);
	else if (!ft_strncmp(line, "WE", 2))
		get_texture(WE, &line[2]);
	else if (!ft_strncmp(line, "EA", 2))
		get_texture(EA, &line[2]);
	else if (!ft_strncmp(line, "F", 1))
		get_colour(FLOOR, &line[1], 0, 0);
	else if (!ft_strncmp(line, "C", 1))
		get_colour(CEILING, &line[1], 0, 0);
	else if (ft_strncmp(line, "\n", 1))
		return (0);
	return (1);
}

void	parse_file(char *file)
{
	t_file	*content;

	check_filename(file);
	content = get_file_content(file, 0);
	parse_textures_colours(&content);
	map_parse(content);
}
