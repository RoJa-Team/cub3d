/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:09:13 by rafasant          #+#    #+#             */
/*   Updated: 2025/12/01 18:25:12 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file	*new_file_content(char *line)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (catch()->set("Error\n%s: Error allocating memory",
				__func__), NULL);
	new->line = line;
	new->line_type = check_line_type(line);
	new->next = NULL;
	if (new->line_type == INVALID)
		return (catch()->set("Error\n%s: Invalid map element {%s}",
				__func__, new->line), free(new->line), free(new), NULL);
	return (new);
}

t_line_type	check_line_type(char *line)
{
	int	i;

	if (!ft_strncmp(line, "NO", 2))
		return (TEXTURE);
	else if (!ft_strncmp(line, "SO", 2))
		return (TEXTURE);
	else if (!ft_strncmp(line, "WE", 2))
		return (TEXTURE);
	else if (!ft_strncmp(line, "EA", 2))
		return (TEXTURE);
	else if (!ft_strncmp(line, "F", 1))
		return (COLOR);
	else if (!ft_strncmp(line, "C", 1))
		return (COLOR);
	else if (ft_strncmp(line, "\n", 1))
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '1')
			return (MAP);
		return (INVALID);
	}
	else
		return (INVALID);
}

void	check_textures_colours(t_textures *textures, t_file *content)
{
	int	i;

	if (catch()->error_msg != NULL)
		return (clear_list(content), deallocate());
	i = 0;
	while (i < 4)
	{
		if (textures->wall[i].path == NULL)
			return (catch()->set("Error\n%s: Missing texture in file",
					__func__), clear_list(content), deallocate());
		i++;
	}
	if (textures->fcolour == -1 || textures->ccolour == -1)
		return (catch()->set("Error\n%s: Missing color in file",
				__func__), clear_list(content), deallocate());
}

void	clear_list(t_file *content)
{
	t_file	*tmp;

	if (!content)
		return ;
	while (content != NULL)
	{
		tmp = content;
		content = content->next;
		free(tmp->line);
		free(tmp);
	}
	return ;
}
