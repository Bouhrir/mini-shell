/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:54:32 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/20 10:34:19 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t	len)
{
	char	*str;
	size_t	i;

	str = (char *) b;
	i = 0;
	while (i < len)
		str[i++] = (char)c;
	return (str);
}
