/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:22:28 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/31 16:22:28 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_bs(char *str, int c)
{
	int	bs;
	int	i;

	i = 0;
	bs = 0;
	while (str[i])
	{
		if ((c == ' ' && str[i] == ' ')
			|| (c == '$' && str[i] == '$'
				&& (!str[i + 1] || str[i + 1] == ' ')))
			bs++;
		i++;
	}
	return (bs);
}

char	*escape_bs(char *str, int c)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + count_bs(str, c) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] != '\\')
		{
			if (!str[i + 1] || str[i + 1] == '\\' || str[i + 1] == ' ')
				res[j++] = '\\';
		}
		else if (c == '\\' && str[i] == c)
			res[j++] = '\\';
		res[j++] = str[i];
		i++;
	}
	res[j++] = '\0';
	return (res);
}

char	*get_env_value(t_mini *sh, int i)
{
	char	*value;
	char	*tmp;

	if (sh->env[i])
		value = ft_strdup(ft_strchr(sh->env[i], '=') + 1);
	else
		value = ft_strdup("");
	tmp = ft_strdup(value);
	free(value);
	value = escape_bs(tmp, '\\');
	free(tmp);
	return (value);
}

char	*var_expand(char *var, t_mini *sh)
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen(var);
	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], var, len) && sh->env[i][len] == '=')
			break ;
		else
			i++;
	}
	res = get_env_value(sh, i);
	return (res);
}

char	*append_exp(char *append, char *exp)
{
	char	*res;

	if (*exp == '\\' && !(*(exp + 1)))
		return (append);
	res = ft_strjoin(exp, append);
	free(exp);
	return (res);
}

char	*parse_exp(char *lex_env, int sign, t_mini *sh)
{
	char	*tmp;
	char	*backup;

	backup = ft_strdup("");
	if (lex_env[1] == '?')
	{
		free(lex_env);
		lex_env = ft_itoa(sh->exit_prev);
	}
	else if (sign)
	{
		tmp = ft_strdup(lex_env);
		free(lex_env);
		lex_env = var_expand(tmp, sh);
		free(tmp);
	}
	tmp = ft_strdup(backup);
	free(backup);
	backup = ft_strjoin(lex_env, tmp);
	return (lex_env);
}

char	*expd(char *str, t_mini *sh)
{
	char	*tmp;

	if (str[1] == '?')
	{
		free(str);
		str = ft_itoa(sh->exit_prev);
	}
	else if (str[0] == '$')
	{
		str++;
		tmp = ft_strdup(str);
		str = var_expand(tmp, sh);
		free(tmp);
	}
	return (str);
}

char *expansion(t_mini *sh, char *command)
{
	char	**lex_env;
	int		i;
	char	*res;
	char	*hold;

	hold = ft_strdup("");
	command = escape_bs(command, '$');
	lex_env = ft_split(command, ' ');
	i = 0;
	while (lex_env[i])
	{
		command = expd(lex_env[i], sh);
		res = ft_strjoin(command, " ");
		hold = ft_strjoin(hold, res);
		free(res);
		i++;
	}
	return (hold);
}

