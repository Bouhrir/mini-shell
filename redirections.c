/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 00:20:22 by obouhrir          #+#    #+#             */
/*   Updated: 2023/08/01 00:20:22 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_length_two_arr(char **str) {
	int count = 0;
	while (str[count])
		count++;
	return count;
}

char	**join_tables(char **table1, char **table2)
{
	int		count;
	int		index;
	int		size;
	char	**dst;

	count = 0;
	index = 0;
	size = count_length_two_arr(table1) + count_length_two_arr(table2);
	dst = malloc(sizeof(char *) * (size + 1));
	while (table1[count])
		dst[index++] = table1[count++];
	count = 0;
	while (table2[count])
		dst[index++] = table2[count++];
	dst[index] = NULL;
	return (dst);
}

typedef struct t_data
{
	char	**dst;
	int		index;
	int		count;
	char	**dst_two;
}	t_data;

int	is_redirect(char *red)
{
	if (ft_strcmp(red, ">") || ft_strcmp(red, ">>") \
		|| ft_strcmp(red, "<") || ft_strcmp(red, "<<"))
		return (1);
	return (0);
}

int	count_redirection_and_files(char **args)
{
	int	count;
	int	count_returend;

	count = 0;
	count_returend = 0;
	while (args[count])
	{
		if (is_redirect(args[count]))
		{
			if (args[count + 1])
				count_returend++;
			count_returend++;
		}
		count++;
	}
	if (count_returend == 0)
		return (1);
	return (count_returend);
}

int	count_argment_without_red(char **args)
{
	int	count;
	int	reterned_count;

	count = 0;
	reterned_count = 0;
	while (args[count])
	{
		if (count == 0 && !is_redirect(args[count]))
			reterned_count++;
		else
			if (count - 1 >= 0 && !is_redirect(args[count - 1]) \
				&& !is_redirect(args[count]))
				reterned_count++;
		count++;
	}
	return (reterned_count);
}


int	init_data_structer_sort_args(t_data *data, char **oldargs)
{
	data->index = 0;
	data->count = 0;
	data->dst = malloc(sizeof(char *) * (count_redirection_and_files(oldargs) + 1));
	if (!data->dst)
		return (1);
	data->dst_two = malloc(sizeof(char *) * (count_argment_without_red(oldargs) + 1));
	return (0);
}

void	split_redirection_and_files(t_data *data, char **oldargs)
{
	while (oldargs[data->count])
	{
		if (is_redirect(oldargs[data->count]))
		{
			data->dst[data->index] = oldargs[data->count];
			data->index++;
			data->count++;
			if (!oldargs[data->count])
				break ;
			if (oldargs[data->count])
			{
				data->dst[data->index] = oldargs[data->count];
				data->index++;
			}
		}
		if (!*oldargs[data->count])
			break ;
		data->count++;
	}
	data->dst[data->index] = NULL;
}

void	split_args_are_not_redirections(t_data *data, char **oldargs)
{
	while (oldargs[data->count])
	{
		if (data->count == 0 && !is_redirect(oldargs[data->count]))
		{
			data->dst_two[data->index] = ft_strdup(oldargs[data->count]);
			data->index++;
		}
		else
		{
			if (data->count - 1 >= 0 && !is_redirect(oldargs[data->count - 1]) \
				&& !is_redirect(oldargs[data->count]))
			{
				data->dst_two[data->index] = ft_strdup(oldargs[data->count]);
				data->index++;
			}
		}
		data->count++;
	}
	data->dst_two[data->index] = NULL;
}

char	**sort_args(char **oldargs)
{
	t_data		data;
	char		**new_args;

	if (init_data_structer_sort_args(&data, oldargs))
		return (NULL);
	split_redirection_and_files(&data, oldargs);
	data.index = 0;
	data.count = 0;
	split_args_are_not_redirections(&data, oldargs);
	new_args = join_tables(data.dst_two, data.dst);
	return (new_args);
}

//-------------------------------------------------------------------------------
int red_error(t_mini *sh, int input, int output)
{
	char *msg;

	msg = NULL;
	if (input > 2)
	{
		if (input < 4)
			msg = ft_strjoin("syntax error near unexpected token `", "<'");
		else
			msg = ft_strjoin("syntax error near unexpected token `", "<<'");
		ft_error(msg, NULL);
		free(msg);
		sh->exit_status = 2;
		return (1);
	}
	if (output > 2)
	{
		if (output < 4)
			msg = ft_strjoin("syntax error near unexpected token `", ">'");
		else
			msg = ft_strjoin("syntax error near unexpected token `", ">>'");
		ft_error(msg, NULL);
		free(msg);
		sh->exit_status = 2;
		return (1);
	}
	return (0);
}

int	valide_redirection(t_mini *sh, char *str)
{
	int	input;
	int	output;
	int	i;

	input = 0;
	output = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			input++;
		else if (str[i] == '>')
			output++;
		else if (str[i] != ' ')
		{
			input = 0;
			output = 0;
		}
		i++;
	}
	if (red_error(sh, input, output))
		return (0);
	return (1);
}

int	red_exists(t_mini *sh, int i)
{
	struct stat	st;
	int			fd;

	fd = -1;
	if ((fd = open (sh->args[i + 1], O_RDONLY, 0644)) == -1)
	{
		if (stat(sh->args[i + 1], &st) != -1)
		{
			if (!(st.st_mode & S_IRUSR) ||
				(st.st_mode & S_IRUSR && (!(st.st_mode & S_IXUSR))))
			{
				sh->exit_status = 1;
				ft_error(" Permission denied", sh->args[i + 1]);
			}
		}
		else
		{
			sh->exit_status = 1;
			ft_error(" No such file or directory", sh->args[i + 1]);
		}
	}
	return (fd);
}
int red_input(t_mini *sh, int i)
{
	int	fd;

	fd = -1;
	if (sh->args[i + 1])
	{
		fd = red_exists(sh, i);
		if (fd != -1)
			dup2(fd, 0);
	}
	else
	{
		sh->exit_status = 2;
		ft_error("syntax error near unexpected token `newline'", NULL);
	}
	if (i == 0 && sh->args[0])
	{
		free(sh->first_arg);
		sh->first_arg = ft_strdup(sh->args[0]);
	}
	return (fd);
}

int red_append(t_mini *sh, int i)
{
	int fd;

	fd = -1;
	if (!sh->args[i + 1])
	{
		sh->exit_status = 2;
		ft_error("syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		if ((fd = open(sh->args[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		{
			sh->exit_status = 1;
			ft_error(" No such file or directory", sh->args[i + 1]);
		}
		else
			dup2(fd, 1);
	}
	return (fd);
}

int red_output(t_mini *sh, int i)
{
	int fd;

	fd = -1;
	if (sh->args[i + 1])
	{
		if ((fd = open(sh->args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		{
			sh->exit_status = 1;
			ft_error(" No such file or directory", sh->args[i + 1]);
		}
		else
			dup2(fd, 1);
	}
	else
	{
		sh->exit_status = 2;
		ft_error("syntax error near unexpected token `newline'", NULL);
	}
	return (fd);
}

int herdoc(t_mini *sh, int i)
{
	int		fd;
	char	*input;

	fd = -1;
	sh->exit_status = 1;
	unlink("/tmp/jobna");
	fd = open("/tmp/jobna", O_CREAT | O_WRONLY, 0777);
	while (1)
	{
		// signal(SIGINT, signal_check);
		input = readline("heredoc> ");
		if (!input)
			break ;
		if (ft_strcmp(input, sh->args[i + 1]))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, fd);
	}
	close (fd);
	sh->exit_status = 0;
	fd = open("/tmp/jobna", O_RDONLY, 0777);
	return (fd);
}

int	check_redirections(t_mini *sh)
{
	int	fd;
	int	i;

	sh->args = sort_args(sh->args);
	i = 0;
	while (sh->args[i])
	{
		if (valide_redirection(sh, sh->args[i]))
		{
			if (ft_strcmp(sh->args[i], "<<") && sh->args[i + 1])
			{
				if (fd != -1)
				{
					fd = herdoc(sh, i);
					if (fd != -1)
						dup2(fd, 0);
				}
			}
			else if (ft_strcmp(sh->args[i], "<"))
				fd = red_input(sh, i);
			else if (ft_strcmp(sh->args[i], ">"))
				fd = red_output(sh, i);
			else if (ft_strcmp(sh->args[i], ">>"))
				fd = red_append(sh, i);
		}
		else
		{
			fd = -1;
			break ;
		}
		i++;
	}
	int count = 0;
	while (sh->args[count]) {
		if (is_redirect(sh->args[count]))
			break;
		count++;
	}
	char **dst = malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (sh->args[count]) {
		if (is_redirect(sh->args[count]))
			break;
		dst[count] = sh->args[count];
		count++;
	}
	dst[count] = 0;
	sh->args = dst;
	return (fd);
}
