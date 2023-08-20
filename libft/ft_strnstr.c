/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:00:14 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/20 13:20:45 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;
	char	*n;

	j = 0;
	i = 0;
	h = (char *)haystack;
	n = (char *)needle;
	if (n[i] == '\0')
		return (h);
	while (h[j] != '\0' && j < len)
	{
		i = 0;
		while (h[j + i] == n[i] && j + i < len)
		{
			i++;
			if (n[i] == '\0')
				return (&h[j]);
		}
		j++;
	}
	return (0);
}
