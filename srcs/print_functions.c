/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:10:49 by rafasant          #+#    #+#             */
/*   Updated: 2025/09/28 16:10:57 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_int(char *info, int data) //TODO remove this
{
	ft_printf("\n%s: >%d<\n", info, data);
}

void	print_string(char *info, char *data) //TODO remove this
{
	ft_printf("\n%s: >%s<\n", info, data);
}

void	print_pointer(char *info, void *data) //TODO remove this
{
	ft_printf("\n%s: >%p<\n", info, data);
}