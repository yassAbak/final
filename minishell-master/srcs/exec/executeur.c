/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:05 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:08 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_annex(char *pathname, char **cmd, char **envp)
{
	DIR	*dir;

	dir = opendir(cmd[0]);
	if (dir)
	{
		closedir(dir);
		printf_err("minishell: ", ": is a directory\n", cmd[0]);
		exit(126);
	}
	else if (execve(pathname, cmd, envp) == -1)
	{
		printf_err("minishell: ", ": ", pathname);
		perror(0);
		ft_free_tab(cmd);
		ft_free_tab(envp);
		exit(127);
	}
}

void	ft_exec(char **cmd, char **envp)
{
	char	*pathname;
	int		i;

	i = 0;
	while (envp[i] && !(ft_strnstr_bis(envp[i], "PATH", 4)))
		i++;
	pathname = getpath(cmd[0], envp);
	if (!pathname)
	{
		if (is_path(cmd[0]) || !envp[i])
			printf_err("minishell: ", ": No such file or directory\n", cmd[0]);
		else
			printf_err("minishell: ", ": command not found\n", cmd[0]);
		ft_free_tab(cmd);
		ft_free_tab(envp);
		exit(127);
	}
	else
		ft_exec_annex(pathname, cmd, envp);
}

void	exec_process_annex(char **args, char **envp, t_cmd **cmd)
{
	dup_all_fd((*cmd));
	close_fds_cmd((*cmd));
	if (is_there_builtin((*cmd)->token))
	{
		ft_free_tab(envp);
		builtin_handler((*cmd)->token, 0);
	}
	else
		ft_exec(args, envp);
	exit(g_data->exit_value);
}

void	exec_process(char **args, char **envp, t_cmd **cmd)
{
	if (!check_parent_builtin(args, envp, cmd))
		return ;
	(*cmd)->child_pid = fork();
	if ((*cmd)->child_pid == -1)
	{
		close_fds_cmd((*cmd));
		ft_error("minishell: fork: Resource temporarily unavailable\n");
	}
	else if ((*cmd)->child_pid == 0)
		exec_process_annex(args, envp, cmd);
	close_fds_cmd((*cmd));
	ft_waitpid((*cmd)->child_pid);
	if (args)
		ft_free_tab(args);
	if (envp)
		ft_free_tab(envp);
}

void	exec_handler(char **envp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_no_interactive);
	signal(SIGQUIT, &signal_no_interactive);
	g_data->cmd = malloc(sizeof(t_cmd));
	if (!g_data->cmd)
		return ;
	g_data->cmd = NULL;
	token_to_cmd(&(g_data->cmd));
	if (!g_data->cmd || !g_data->cmd->token)
	{
		if (g_data->cmd)
			free_cmd(&(g_data->cmd));
		return ;
	}
	if (g_data->cmd->next)
		pipe_exec(envp);
	else
		exec_process(token_to_tab(g_data->cmd->token), envp, &(g_data->cmd));
	free_cmd(&(g_data->cmd));
}
