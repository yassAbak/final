/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:40 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:42 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->fd_in)
			close(tmp->fd_in);
		if (tmp->fd_out > 1)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
}

void	child(char **envp, t_cmd **cmd)
{
	(*cmd)->child_pid = fork();
	if ((*cmd)->child_pid == -1)
	{
		close_fds_cmd(*cmd);
		ft_error("minishell: fork: Resource temporarily unavailable\n");
	}
	else if ((*cmd)->child_pid == 0)
	{
		dup_all_fd(*cmd);
		close_fds_cmd(*cmd);
		if (is_there_builtin((*cmd)->token))
			builtin_handler((*cmd)->token, 1);
		else
			ft_exec(token_to_tab((*cmd)->token), envp);
		exit(g_data->exit_value);
	}
	if ((*cmd)->fd_in > 0)
		close((*cmd)->fd_in);
	if ((*cmd)->fd_out > 1)
		close((*cmd)->fd_out);
}

void	pipe_exec(char **envp)
{
	t_cmd	*tmp;

	if (!pipe_error_handler())
		return ;
	tmp = g_data->cmd;
	while (tmp)
	{
		child(envp, &tmp);
		tmp = tmp->next;
	}
	tmp = g_data->cmd;
	while (tmp)
	{
		ft_waitpid(tmp->child_pid);
		tmp = tmp->next;
	}
	if (envp)
		ft_free_tab(envp);
}
