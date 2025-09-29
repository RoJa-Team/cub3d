/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:31:28 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/28 18:26:42 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_filename(char *file)
{
	char	*ber;
	int		i;

	i = 0;
	ber = ".cub";
	while (file[i])
		i++;
	i = i - 4;
	while (file[i])
	{
		if (file[i] != *ber)
			return ((void)catch()->set("Error\n%s: File [%s] isn't a .ber file", __func__, file), deallocate());
		i++;
		ber++;
	}
}

t_file	*get_file_content(char *file)
{
	int		fd;
	char	*line;
	t_file	*tmp;
	t_file	*content;
	t_file	*new_content;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (catch()->set("Error\n%s: Error opening file", __func__), deallocate(), NULL);
	content = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_content = malloc(sizeof(t_file));
		if (!new_content)
			return (catch()->set("Error\n%s: Error allocating memory", __func__), deallocate(), NULL);
		new_content->line = line;
		new_content->next = NULL;
		if (content == NULL)
			content = new_content;
		else
			tmp->next = new_content;
		tmp = new_content;
		line = get_next_line(fd);
	}
	return (content);
}

char	*get_texture_path(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n' && line[i] == ' ')
		i++;
	len = 0;
	while (line[len + i] != '\0' && line[len + i] != ' ')
		len++;
	path = ft_strndup(&line[i], len);
	if (path == NULL)
		return (catch()->set("Error\n%s: Memory allocation failed", __func__), deallocate(), NULL);
	return (path);
}

void	get_texture(t_orientation orien, char *line)
{
	if (textures()->wall[orien].path == NULL)
	{
		textures()->wall[orien].orient = orien;
		textures()->wall[orien].path = get_texture_path(&line[2]);
	}
	else
		return (catch()->set("Error\n%s: Duplicate map element {%s}", __func__, orien), deallocate());
}

void	assign_colour(t_identifier ident, int *rgb)
{
	if (ident == FLOOR && textures()->fcolour == -1)
		textures()->fcolour = create_rgb(rgb[0], rgb[1], rgb[2]);
	else if (ident == CEILING && textures()->ccolour == -1)
		textures()->ccolour = create_rgb(rgb[0], rgb[1], rgb[2]);
	else
		return (catch()->set("Error\n%s: Duplicate map element {%s}", __func__, ident), deallocate());
}

void	get_colour(t_identifier ident, char *line)
{
	int	i;
	int	j;
	int	rgb[3];

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i] != '\0' && j < 3)
	{
		while (line[i] != '\0' && line[i] != '\n' && ft_isspace(line[i]))
			i++;
		if ((line[i] < '0' || line[i] > '9'))
			return (catch()->set("Error\n%s: Invalid colour value {%s}", __func__, line[i]), deallocate());
		rgb[j] = 0;
		while (line[i] != '\0' && (line[i] >= '0' && line[i] <= '9'))
		{
			rgb[j] = rgb[j] * 10 + (line[i] - 48);
			i++;
		}
		if (rgb[j] < 0 || rgb[j] > 255)
			return (catch()->set("Error\n%s: Invalid colour value {%s}", __func__, line[i]), deallocate());
		j++;
		while (line[i] != '\0' && line[i] != '\n' && ft_isspace(line[i]))
			i++;
		if (line[i] == ',')
			i++;
	}
	assign_colour(ident, rgb);
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
		get_colour(FLOOR, &line[1]);
	else if (!ft_strncmp(line, "C", 1))
		get_colour(CEILING, &line[1]);
	else if (ft_strncmp(line, "\n", 1))
		return (0);
	return (1);
}

void parse_textures_colours(t_file **content)
{
	t_file	*tmp;

	while (1)
	{
		tmp = *content;
		if (tmp == NULL || tmp->line == NULL)
			return ;
		if (tmp->line[0] == '\0')
		{}
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

void	parse_file(char *file)
{
	t_file	*content;

	check_filename(file);
	if (catch()->error_msg != NULL)
		return ;
	content = get_file_content(file);
	if (content == NULL || catch()->error_msg != NULL)
		return ;
	parse_textures_colours(&content);
	map_parse(content);
}
