/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:39:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/16 13:22:17 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_ptr_quantity(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**ptrptr;
	size_t	index;
	size_t	start;
	size_t	end;
	size_t	ptr_quanity;

	index = 0;
	start = 0;
	if (s == NULL)
		return (NULL);
	ptr_quanity = ft_ptr_quantity(s, c);
	ptrptr = malloc((ptr_quanity + 1) * sizeof(char *));
	if (ptrptr == NULL)
		return (NULL);
	while (index != ptr_quanity)
	{
		while (s[start] != '\0' && s[start] == c)
			start++;
		end = start;
		while (s[end] != '\0' && s[end] != c)
			end++;
		ptrptr[index] = ft_substr(s, start, (end - start));
		start = end;
		index++;
	}
	ptrptr[index] = NULL;
	return (ptrptr);
}

size_t	ft_ptr_quantity(char const *s, char c)
{
	size_t	counter;
	size_t	quantity;

	counter = 0;
	quantity = 0;
	if (s[0] == '\0')
		return (0);
	while (s[counter] != '\0')
	{
		if (s[counter] != c && (s[counter + 1] == c || s[counter + 1] == '\0'))
			quantity++;
		counter++;
	}
	return (quantity);
}
