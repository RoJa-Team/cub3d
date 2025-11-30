/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:31:12 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 17:08:58 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n' && line[i] == ' ')
		i++;
	len = 0;
	while (line[len + i] != '\0' && line[len + i] != '\n'
		&& line[len + i] != ' ')
		len++;
	path = ft_strndup(&line[i], len);
	if (path == NULL)
		return (catch()->set("Error\n%s: Memory allocation failed",
				__func__), deallocate(), NULL);
	return (path);
}

void	get_texture(t_orientation orien, char *line)
{
	if (textures()->wall[orien].path == NULL)
	{
		textures()->wall[orien].orient = orien;
		textures()->wall[orien].path = get_texture_path(line);
	}
	else
		return (catch()->set("Error\n%s: Duplicate map element {%s}",
				__func__, orien), deallocate());
}
