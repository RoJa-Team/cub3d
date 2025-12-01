/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:32:03 by rafasant          #+#    #+#             */
/*   Updated: 2025/12/01 17:32:25 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_colour(t_identifier ident, int *rgb)
{
	if (ident == FLOOR && textures()->fcolour == -1)
		textures()->fcolour = create_rgb(rgb[0], rgb[1], rgb[2]);
	else if (ident == CEILING && textures()->ccolour == -1)
		textures()->ccolour = create_rgb(rgb[0], rgb[1], rgb[2]);
	else
		return (catch()->set("Error\n%s: Duplicate map element {%s}",
				__func__, ident), 1);
	return (0);
}

int	get_colour(t_identifier ident, char *line, int i, int j)
{
	int	rgb[3];

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i] != '\0' && j < 3)
	{
		while (line[i] != '\0' && line[i] != '\n' && ft_isspace(line[i]))
			i++;
		if ((line[i] < '0' || line[i] > '9'))
			return (catch()->set("Error\n%s: Invalid colour value {%c}",
					__func__, line[i]), 1);
		rgb[j] = 0;
		if (check_rgb(line, &rgb[j], &i))
			return (1);
		j++;
		while (line[i] != '\0' && line[i] != '\n' && ft_isspace(line[i]))
			i++;
		if (line[i] == ',')
			i++;
	}
	if ((line[i] != '\0' && line[i] != '\n') || j != 3)
	{
		return (catch()->set("Error\n%s: Invalid color provided", __func__), 1);
	}
	return (assign_colour(ident, rgb));
}

int	check_rgb(char *line, int *rgb, int *i)
{
	while (line[*i] != '\0' && line[*i] != ',' && line[*i] != '\n'
		&& line[*i] != ' ')
	{
		if ((line[*i] < '0' || line[*i] > '9'))
			return (catch()->set("Error\n%s: Invalid colour value {%c}",
					__func__, line[*i]), 1);
		*rgb = *rgb * 10 + (line[(*i)++] - 48);
	}
	if (*rgb < 0 || *rgb > 255)
		return (catch()->set("Error\n%s: Invalid colour value {%d}",
				__func__, *rgb), 1);
	return (0);
}
