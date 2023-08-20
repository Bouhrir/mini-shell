/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:29:56 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/27 17:29:56 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whitespaces(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	separ(char input, int c)
{
	if (c == ' ' && whitespaces(input))
		return (1);
	else if (input == c)
		return (1);
	return (0);
}

int	counter(char *input, int c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (input[i])
	{
		if (separ(input[i], c) && input[i - 1] != '\\')
		{
			word++;
			while (input[i] && !separ(input[i], c))
				i++;
		}
		i++;
	}
	return (word);
}

int	check_backslash(char *input, int i)
{
	int	bs;

	bs = 0;
	i--;
	while (i >= 0 && input[i] == '\\')
	{
		i--;
		bs++;
	}
	if (bs > 1 && input[i] == ' ')
		bs = 1;
	return ((bs + 1) % 2);
}

char	*rm_delimiter(char *input, int c)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(input);
	i = 0;
	while (tmp[i])
	{
		if (separ(tmp[i], c) && check_backslash(tmp, i))
			tmp[i] = '\0';
		i++;
	}
	return (tmp);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

char	**lexical_analysis(char *input, int c)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	input = rm_delimiter(input, c);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		skip_spaces(input, &i);
		res[j] = ft_strdup(&input[i]);
		if (!ft_strncmp(res[j], "\"\"", 2))
		{
			free(res[j]);
			res[j] = ft_strdup("");
			i += 2;
		}
		else
			i += ft_strlen(res[j]);
		j++;
		while (i < len && !input[i])
			i++;
	}
	res[j] = NULL;
	return (res);
}

// char	**lexical_analysis(char *input, int c)
// {
// 	char	**res;
// 	char	*tmp;
// 	int		len;
// 	int		i;
// 	int		j;

// 	res = malloc(sizeof(char *) * (counter(input, c) + 2));
// 	if (!res)
// 		return (NULL);
// 	len = ft_strlen(input);
// 	tmp = ft_strdup(input);
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		if (separ(tmp[i], c) && check_backslash(tmp, i - 1))
// 			tmp[i] = '\0';
// 		i++;
// 	}
// 	input = tmp;
// 	i = 0;
// 	j = 0;
// 	while (i < len)
// 	{
// 		res[j] = ft_strdup(&input[i]);
// 		if (!ft_strncmp(res[j], "\"\"", 3))
// 		{
// 			tmp = ft_strdup("");
// 			free(res[j]);
// 			res[j] = tmp;
// 			i += 2;
// 		}
// 		else
// 			i += ft_strlen(res[j]);
// 		j++;
// 		while (i < len && !input[i])
// 			i++;
// 		if (i >= len)
// 			break ;
// 	}
// 	res[j] = NULL;
// 	return (res);
// }
