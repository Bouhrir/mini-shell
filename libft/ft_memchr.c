/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:17:12 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/20 10:53:58 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	char	*t;
	size_t	i;

	i = 0;
	t = (char *)s;
	while (i < n)
	{
		if (t[i] == (char) c)
		{
			return (&t[i]);
		}
		i++;
	}
	return (0);
}
