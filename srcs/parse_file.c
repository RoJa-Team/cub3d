/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:31:28 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/24 23:09:16 by rafasant         ###   ########.fr       */
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
			return (catch()->set("Error\n %s: File [%s] isn't a .ber file", __func__, file));
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
		return (NULL);
		// deallocate(catch()->set("Error\n %s: Error opening file", __func__));
	content = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_content = malloc(sizeof(t_file));
		if (!new_content)
			return (NULL);
			// deallocate(catch()->set("Error\n %s: Error allocating memory", __func__));
		new_content->line = line;
		if (content == NULL)
			content = new_content;
		else
			tmp->next = new_content;
		tmp = new_content;
		line = get_next_line(fd);
	}
	return (content);
}

int	static ft_len_wspc(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		
	}
}

char	*get_path(char *line)
{
	int		len;
	char	*path;

	while (*line != '\0' && *line == ' ')
		line++;
	len = 0;
	while (line[len] != '\0' && line[len] != ' ')
		len++;
	path = ft_strndup(line, len);
	if (path == NULL)
		deallocate(catch()->set("Error\n %s: Malloc allocation failed", __func__));
	return (path);
}

void	check_element(char *line)
{
	t_orientation	orien;

	if (!ft_strncmp(line, "NO", 2))
		orien = NO;
	else if (!ft_strncmp(line, "SO", 2))
		orien = SO;
	else if (!ft_strncmp(line, "WE", 2))
		orien = WE;
	else if (!ft_strncmp(line, "EA", 2))
		orien = EA;
	if (textures()->wall[orien].orient == NULL)
	{
		textures()->wall[orien].orient = orien;
		textures()->wall[orien].path = get_path(&line[2]);
	}
	else
		deallocate(catch()->set("Error\n %s: Duplicate map element {%s}", __func__, orien));
}

void parse_textures(t_file *content)
{
	t_file	*tmp;

	tmp = content;
	while (1)
	{
		if (tmp == NULL || tmp->line == NULL)
			return ;
		if (tmp->line[0] == '\0')
		{}
		else
			check_element(tmp->line);
		
		tmp = tmp->next;
	}
}

void parse_colours(t_file *content)
{
	t_file	*tmp;

	tmp = content;
	while (1)
	{
		if (tmp == NULL)
			return ;
		if ()
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
	parse_textures(content);
	parse_colours(content);
	parse_map(content);
	// parse_map(content);
	// int	i = 0;
	// while (content != NULL)
	// {
	// 	ft_printf("line %d: %s\n", i, content->line);
	// 	content = content->next;
	// 	i++;
	// }
}