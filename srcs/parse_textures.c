/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:31:12 by rafasant          #+#    #+#             */
/*   Updated: 2025/12/01 17:07:11 by rafasant         ###   ########.fr       */
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
				__func__), NULL);
	return (path);
}

int	get_texture(t_orientation orien, char *line)
{
	if (textures()->wall[orien].path == NULL)
	{
		textures()->wall[orien].orient = orien;
		textures()->wall[orien].path = get_texture_path(line);
		if (textures()->wall[orien].path == NULL)
			return (1);
		return (0);
	}
	else
		return (catch()->set("Error\n%s: Duplicate map element {%s}",
				__func__, orien), 1);
}
