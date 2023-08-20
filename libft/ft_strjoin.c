/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:47:22 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/20 10:48:06 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*p;
	int		i;
	int		j;
	int		x;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!p)
		return (0);
	x = 0;
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		p[x++] = s1[i++];
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		p[x++] = s2[j++];
	}
	p[x] = '\0';
	return (p);
}
