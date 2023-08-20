/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:23:53 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/21 17:32:29 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char	*s, char (*f)(unsigned int, char))
{
	char	*p;
	int		i;

	i = 0;
	if (!s)
		return (0);
	p = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!p)
		return (0);
	while (s[i] != '\0')
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
