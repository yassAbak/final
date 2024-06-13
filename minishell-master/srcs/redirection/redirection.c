/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:01 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:04 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	files_handler_annex(t_token *tmp, t_type type, t_cmd *cmd)
{
	if (type == SL_REDIR)
		return (cmd->fd_in = \
		existing_file_in(tmp, cmd->fd_in));
	else if (type == DL_REDIR)
		return (cmd->fd_in = \
		create_tmp_heredoc(tmp, cmd->fd_in));
	else
		return (cmd->fd_out = \
		existing_file_out(tmp, cmd->fd_out, type));
}

int	files_handler(t_cmd *cmd, t_token *token)
{
	t_token	*tmp;
	t_type	type;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SL_REDIR || tmp->type == DL_REDIR \
		|| tmp->type == SR_REDIR || tmp->type == DR_REDIR)
		{
			type = tmp->type;
			if (tmp->next && tmp->next->type == SPACES)
				tmp = tmp->next;
			files_handler_annex(tmp->next, type, cmd);
			if (cmd->fd_in == -1 || cmd->fd_out == -1)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
