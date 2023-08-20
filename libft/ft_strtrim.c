/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:49:18 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/20 11:25:23 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	int	i;
	int	len;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] != '\0')
	{
		if (!(ft_strchr(set, (int)s1[i])))
		{
			s1 = &s1[i];
			break ;
		}
		i++;
	}
	len = ft_strlen(s1);
	while (len > 0)
	{
		if (!(ft_strchr(set, (int)s1[len -1])))
			break ;
		len--;
	}
	return (ft_substr(s1, 0, len));
}
