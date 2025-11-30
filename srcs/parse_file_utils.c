/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:09:13 by rafasant          #+#    #+#             */
/*   Updated: 2025/11/30 17:18:21 by rafasant         ###   ########.fr       */
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
	new->next = NULL;
	return (new);
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
