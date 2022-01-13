/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_input_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:09:29 by coder             #+#    #+#             */
/*   Updated: 2022/01/10 12:58:12 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_hextoi(char *str)
{
	int   base;
	char *hex;
	int   col;

	hex = "0123456789ABCDEF";
	base = 16;
	col = 0;
	while (*str != '\0')
	{
		col = col * base + (ft_strchr(hex, *str) - hex);
		// in dem man mit base multipliziert, shiftet man die breits bestehenden
		// Zahlen nach links mit der Basis multiplizieren für ein extra Feld
		str++;
	}
	return (col);
}

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
