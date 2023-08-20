/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:23:40 by obouhrir          #+#    #+#             */
/*   Updated: 2022/10/21 13:53:18 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
			{
				i++;
			}
			word++;
		}
	}
	return (word);
}

static long	size(char	*s, char c, int i)
{
	int	ct;

	ct = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		ct++;
	}
	return (ct);
}

static void	sp(char *s, char	**res, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			res[j] = (char *)malloc((size(s, c, i) + 1) * sizeof(char));
			if (!res[j])
				return ;
			while (s[i] && s[i] != c)
			{
				res[j][k++] = s[i++];
			}
			res[j++][k] = '\0';
		}
	}
	res[j] = NULL;
}

char	**ft_split(char	*s, char c)
{
	char	**res;

	res = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	sp(s, res, c);
	return (res);
}
