/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:09:00 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:43:00 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	*g_data;

void	init_global(char **envp)
{
	g_data = malloc(sizeof(t_global));
	if (!g_data)
		return ;
	g_data->shell_level = 2;
	g_data->token = NULL;
	g_data->cmd = NULL;
	g_data->heredoc = -1;
	g_data->env = init_env(envp);
	change_level(g_data->env);
	g_data->squote_open = -1;
	g_data->dquote_open = -1;
	g_data->exit_value = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char		*buff;
	extern int	rl_catch_signals;

	(void)argc;
	(void)argv;
	init_global(envp);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, &signal_interactive);
		signal(SIGQUIT, SIG_IGN);
		buff = readline("shell$ ");
		ctrl_d_handler(buff);
		lexer(buff, g_data->env);
		free(buff);
		parser();
		if (g_data->token)
			exec_handler(tenv_to_tab(g_data->env));
		free_all(1);
	}
	rl_clear_history();
	return (0);
}
