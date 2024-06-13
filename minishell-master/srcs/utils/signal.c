/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:25 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:28 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_data->exit_value = 1;
		g_data->heredoc = dup(STDIN_FILENO);
		close(STDIN_FILENO);
	}
}

void	signal_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_data->exit_value = 1;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_no_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_data->exit_value = 130;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		g_data->exit_value = 131;
		ft_putstr_fd("Quit: 3\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ctrl_d_handler(char *buff)
{
	if (!buff)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", 2);
		free_token(&(g_data->token));
		free_env(&(g_data->env));
		free(g_data);
		exit(0);
	}
}
