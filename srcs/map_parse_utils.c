/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:33:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/11/30 15:33:48 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_objects(void)
{
	map_objects()->player_count = 0;
	map_objects()->map_width = 0;
	map_objects()->map_height = 0;
	map_objects()->map = NULL;
}

void	raycast_init(double dir_x, double dir_y, double plane_x, double plane_y)
{
	player()->dir_x = dir_x;
	player()->dir_y = dir_y;
	player()->plane_x = plane_x;
	player()->plane_y = plane_y;
}

void	initial_orientation(char ori, int y, int x)
{
	if (ori == 'N')
		raycast_init(0, -1, FOV, 0);
	else if (ori == 'S')
		raycast_init(0, 1, -FOV, 0);
	else if (ori == 'E')
		raycast_init(1, 0, 0, FOV);
	else if (ori == 'W')
		raycast_init(-1, 0, 0, -FOV);
	map_objects()->player_count++;
	player()->x = x + 0.5;
	player()->y = y + 0.5;
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**empty_array(void)
{
	char	**empty_array;
	int		i;

	i = -1;
	empty_array = ft_calloc(sizeof(char *), map_objects()->map_height + 1);
	while (++i < map_objects()->map_height)
		empty_array[i] = ft_calloc(sizeof(char), map_objects()->map_width + 1);
	return (empty_array);
}
