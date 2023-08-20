/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:30:54 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/30 15:30:54 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_err_msg(t_mini *sh)
{
	char	*backup;

	backup = ft_strdup("exit: ");
	backup = ft_strjoin(backup, sh->args[1]);
	ft_error(" numeric argument required", backup);
	free(backup);
	exit(255);
}

int	toomany(char *arg)
{
	if (arg)
	{
		ft_error("exit: too many arguments", NULL);
		return (1);
	}
	else
		return (0);
}

void	all_exit(int handler, t_mini *sh)
{
	sh_cleaner(sh);
	exit(handler);
}

void	to_exit(t_mini *sh)
{
	int		handler;
	char	*box;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	if (sh->args[1])
	{
		box = sh->args[1];
		while (box[i])
		{
			if (box[i] == '-')
				i++;
			if (!ft_isdigit(box[i]))
				write_err_msg(sh);
			i++;
		}
		handler = ft_atoi(box);
		if (toomany(sh->args[2]))
			handler = 1;
	}
	else
		handler = sh->exit_status;
	all_exit(handler, sh);
}
