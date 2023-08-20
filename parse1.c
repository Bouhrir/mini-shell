/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:43:09 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/28 21:43:09 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bs_previous(char *input, int start)
{
	int	i;

	i = 0;
	while (start && input[start - 1] == '\\')
		i++;
	return ((i + 1) % 2);
}

int	special_char(char c)
{
	if (c == '$' || c == '\\' || c == ';' || c == '|' || c == '\'')
		return (1);
	return (0);
}

int	special_chars_count(char *input, int start, int end, char quote)
{
	int	i;
	int	len;

	i = start + 1;
	len = 0;
	while (i < end)
	{
		if (quote != '\'' && special_char(input[i]))
			len++;
		else if (input[i] == ' ' || input[i] == '\t')
			len++;
		i++;
	}
	return (len);
}

char	*qalloc(char *input, int start, int end, char quote)
{
	char	*all;

	all = malloc(sizeof(char) * ((end - start)
				+ special_chars_count(input, start, end, quote) + 1));
	if (!all)
		return (NULL);
	return (all);
}

char	*between_quotes(char *input, int start, int end, char quote)
{
	char	*res;
	int		i;
	int		j;

	i = start + 1;
	j = 0;
	res = qalloc(input, start, end, quote);
	while (i < end)
	{
		if (quote == '\''
			&& (special_char(input[i])
				|| (input[i - 1] == '\\' && ft_isalpha(input[i]))))
			res[j++] = '\\';
		else
		{
			if (input[i] == ' ' || input[i] == '\t'
				|| input[i] == '|' || input[i] == ';' || input[i] == '\'')
				res[j++] = '\\';
			if (input[i - 1] == '\\'
				&& (input[i] == '|' || ft_isalpha(input[i])))
				res[j++] = '\\';
		}
		res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}

void quote_error(char quote)
{
	if (quote == '\'')
		ft_error("unexpected EOF while looking for matching `''", NULL);
	else
		ft_error("unexpected EOF while looking for matching `\"'", NULL);
}

char *endof_quote(char *input, char quote, int start, int *end)
{
	int		i;
	char	*res;

	i = start + 1;
	*end = 0;
	if (input[i] == quote && i > 1 && input[i - 2] == ' ')
	{
		*end += i + 1;
		return (ft_strdup("\"\""));
	}
	while (input[i])
	{
		if (input[i] == quote && (quote == '\'' || bs_previous(input, i)))
		{
			*end += (start + 1);
			res = between_quotes(input, start, *end, quote);
			return (res);
		}
		(*end)++;
		i++;
	}
	quote_error(quote);
	return (NULL);
}
