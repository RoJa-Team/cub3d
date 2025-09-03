/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:31:28 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/03 22:40:46 by rafasant         ###   ########.fr       */
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
		if (!content)
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

void	parse_file(char *file)
{
	int		fd;
	char	*line;
	t_file	*content;

	check_filename(file);
	if (catch()->error_msg != NULL)
		return ;
	content = get_file_content(file);
	if (content == NULL || catch()->error_msg != NULL)
		return ;
	parse_textures_colors(content);
	parse_map(content);
}