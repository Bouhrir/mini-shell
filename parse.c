/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:56:27 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/28 20:56:27 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//==============================quote parse=========================

char *rm_quotes(char *input, int *start, int *end)
{
	char 	*res;
	char	quote;

	*start = 0;
	while (input[*start])
	{
		if ((input[*start] == '\'' || input[*start] == '\"')
			&& bs_previous(input, *start))
		{
			quote = input[*start];
			res = endof_quote(input, quote, *start, end);
			return (res);
		}
		(*start)++;
	}
	*start = -1;
	return (input);
}

char	*quote_join(char *input, char *in_quote, char *buff, int start)
{
	char	*prev_quote;
	char	*str;
	char	*str1;

	prev_quote = malloc(sizeof(char) * (start + 1));
	if (!prev_quote)
		return (NULL);
	ft_strlcpy(prev_quote, input, start + 1);
	str = ft_strjoin(buff, prev_quote);
	free(prev_quote);
	str1 = ft_strjoin(str, in_quote);
	free(str);
	free(in_quote);
	return (str1);
}

char	*parse_join(char *input, char *in_quote, char *buff, int start)
{
	char	*res;

	if (start != -1)
		res = quote_join(input, in_quote, buff, start);
	else
	{
		if (ft_strcmp(buff, ""))
			res = ft_strdup(in_quote);
		else
			res = ft_strjoin(buff, in_quote);
	}
	return (res);
}

char	*quotes_parse(char *input, t_help *norm)
{
	int	i;

	norm->start = 0;
	norm->end = 0;
	norm->buff = ft_strdup("");
	i = 0;
	while (input[i])
	{
		norm->in_quote = rm_quotes(&input[i], &norm->start, &norm->end);
		if (!norm->in_quote)
		{
			free(norm->buff);
			return (NULL);
		}
		norm->tmp = parse_join(&input[i], norm->in_quote,
				norm->buff, norm->start);
		free(norm->buff);
		norm->buff = norm->tmp;
		if (norm->start == -1)
			break ;
		else
			i += norm->end + 1;
	}
	return (norm->buff);
}

//==============================backslash parse=========================
int	specialchar_check(char c, int check)
{
	if (check == 1 && (c == '\'' || c == '\"'))
		return (1);
	else if (check == 2 && (ft_isalpha(c)
			|| c == ' ' || c == '\t'
			|| c == '|' || c == ';'
			|| c == '$' || c == '\\'))
		return (1);
	else if (check == 3 && c == '\\')
		return (1);
	return (0);
}

char	*rm_safe(char *str, char *bs)
{
	char	*tmp;
	char	*res;
	int		str_len;
	int		bs_len;

	str_len = ft_strlen(str);
	bs_len = ft_strlen(bs);
	tmp = malloc((str_len - bs_len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, str_len - bs_len + 1);
	res = ft_strjoin(tmp, ++bs);
	free(tmp);
	return (res);
}

void	rm_bs(char **str, char *bs)
{
	char	*res;

	res = rm_safe(*str, bs);
	free(*str);
	*str = ft_strdup(res);
	free(res);
}

char *bs_parse(char *str, int bs_check)
{
	char	*bs;
	char	*res;

	res = ft_strdup(str);
	if (*str == '\\' && !*(str + 1))
	{
		*res = '\0';
		str++;
	}
	while (*str)
	{
		bs = ft_strchr(str, '\\');
		if (!bs)
			break ;
		if (specialchar_check(*(bs + 1), bs_check))
			rm_bs(&res, bs);
		str = (bs + 1);
		if (*str == '\\')
			str++;
	}
	return (res);
}
//==============================parse=========================

char	*parsing(char *input, t_help *norm)
{
	char	*res;
	char	*buff;

	buff = quotes_parse(input, norm);
	res = NULL;
	if (buff)
	{
		res = bs_parse(buff, 1);
		free(buff);
	}
	return (res);
}

// int main()
// {
// 	printf("%s\n", check_quotes("ksjdkjds'dsjdsl'ds"));
// }