/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:58:41 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/20 11:17:33 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int		len;
	char	*s;

	s = (char *)str;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return (&s[len]);
		len--;
	}
	return (NULL);
}
