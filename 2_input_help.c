/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_input_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:09:29 by coder             #+#    #+#             */
/*   Updated: 2022/01/19 22:17:34 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_hextoi(char *str)
{
	int   base;
	char *hex;
	int   col;

	hex = "0123456789abcdef";
	base = 16;
	col = 0;
	while (*str && ft_strchr(hex, *str))
	{
		col = col * base + (ft_strchr(hex, *str) - hex);
		str++;
	}
	return (col);
}
/*multiply with base for an extra space*/

int x_coordinate(char **line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (i);
	while (line[i] != NULL && *line[i] != '\n')
	{
		i++;
	}
	return (i);
}
