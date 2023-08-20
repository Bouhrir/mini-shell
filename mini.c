/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:59:51 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/19 18:13:20 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini	sh;
	t_help	norm;
	char	*store;
	int		fd;
	int		fd0;

	(void)av;
	if (ac == 1)
	{
		sh.input = NULL;
		sh.inst = NULL;
		sh.exit_status = 0;
		sh.test = 0;
		sh.env = strdup_env(env);
		get_shlvl(&sh);
		store = ft_strdup("_=/bin/bash");
		export(&sh, store);
		free(store);
		fd = dup(1);
		fd0 = dup(0);
		signal(SIGQUIT, signal_check);
		while (1)
		{
			dup2(fd, 1);
			dup2(fd0, 0);
			signal(SIGINT, signal_check);
			sh.input = readline("minishell$ ");
			if (!sh.input)
			{
				free(sh.input);
				free_env(sh.env);
				exit(sh.exit_status);
			}
			add_history(sh.input);
			sh.parse = parsing(sh.input, &norm);
			free(sh.input);
			if (!sh.parse)
				sh.exit_status = 2;
			else
			{
				sh.input = sh.parse;
				shell(sh.input, &sh, &norm);
				// system("leaks minishell | grep 'leaks for'");
			}
		}
	}
	else
		return (0);
}
