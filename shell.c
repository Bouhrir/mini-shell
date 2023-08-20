/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:00:01 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/19 16:35:25 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_priority(char *line, int i, int token)
{
	int hold;

    hold = i;
    while (hold > 0 && line[hold] == ' ')
        hold--;
    if (token == '>' || token == '<')
    {
        if (hold > 0 && hold != i && (line[hold] == '>' || line[hold] == '<'))
            return (1);
        else
            return (0);
    }
    else
    {
        if (hold < 1 || line[hold] == ';' || line[hold] == '>' ||
            line[hold] == '<' || line[hold] == '|')
            return (1);
        else
            return (0);
    }
	return (0);
}

int invalid_err(t_mini *sh, char *input, int sep, int i)
{
	if (sep == ';')
		ft_error("syntax error near unexpected token `;'", NULL);
	else if (sep == '|')
		ft_error("syntax error near unexpected token `|'", NULL);
	else if (sep == '>' && input[i + 1] == '>')
		ft_error("syntax error near unexpected token `>>'", NULL);
	else if (sep == '<' && input[i + 1] == '<')
		ft_error("syntax error near unexpected token `<<'", NULL);
	else if (sep == '>')
		ft_error("syntax error near unexpected token `>'", NULL);
	else if (sep == '<')
		ft_error("syntax error near unexpected token `<<'", NULL);
	sh->exit_status = 2;
	return (1);
}

int check_after_pipe(char *input, int i)
{
	if (i - 2 >= 0 && *(input - 2) == '\\')
		return (0);
	while (*input && *input == ' ')
		input++;
	if (!*input)
		return (1);
	return (0);
}

int monitor_valide(t_mini *sh, char *input, int sep, int i)
{
	if (token_priority(input, i - 1, input[i]))
	{
		if (invalid_err(sh, input, sep, i))
			return (1);
		return (0);
	}
	else if (sep == '|' && check_after_pipe(&input[i + 1], i))
	{
		ft_error("syntax error: unexpected end of file", NULL);
		sh->exit_status = 2;
		return (1);
	}
	return (0);
}

int validate_input(char *input, t_mini *sh)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' ||
			input[i] == '<' ||
			input[i] == '>' || 
			input[i] == ';')
		{
			if (monitor_valide(sh, input, input[i], i))
				return (0);
		}
		i++;
	}
	return (1);
}

void print_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
}

int	arr_len(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

void shell(char *input, t_mini *sh, t_help *help)
{
	if (validate_input(input, sh))
	{
		sh->commands = lexical_analysis(input, '|');
		sh->count = count_pipe(sh->commands);
		if (sh->count == 0)
			check_commands(sh);
		else if (sh->count)
			check_pipe(sh, help);
	}
	free(input);
}