/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:51:14 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/21 16:35:13 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count = 1;
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static void	result(char *s, int n, int len)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		s[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		s[len - 1] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	len = count(n);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (0);
	s[len] = '\0';
	if (n == 0)
		*s = '0';
	result(s, n, len);
	return (s);
}

// int main()
// {
// 	printf("%s", ft_itoa(0059));
// }