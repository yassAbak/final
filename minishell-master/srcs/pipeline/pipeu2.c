/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeu2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:50 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:53 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**add_cmd(t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->token = NULL;
	new->next = NULL;
	tmp = NULL;
	if (!(*cmd))
		*cmd = new;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (cmd);
}

void	set_fd_pipes(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		fd[2];

	tmp = *cmd;
	while (tmp->next)
	{
		if (pipe(fd) == -1)
			ft_error("PIPE error\n");
		tmp->fd_out = fd[1];
		tmp->next->fd_in = fd[0];
		tmp = tmp->next;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*swap;

	while (*cmd)
	{
		swap = (*cmd)->next;
		if ((*cmd)->token)
			free_token(&((*cmd)->token));
		free(*cmd);
		*cmd = swap;
	}
	*cmd = NULL;
}

void	dup_all_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 1)
		dup2(cmd->fd_out, STDOUT_FILENO);
}
