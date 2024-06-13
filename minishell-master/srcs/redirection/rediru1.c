/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediru1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:08 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:10 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	existing_file_in(t_token *token, int fd)
{
	if (fd > 0)
		close(fd);
	if (!token || token->str[0] == ';' || token->str[0] == '&' \
	|| token->type == SL_REDIR || token->type == SR_REDIR \
	|| token->type == DL_REDIR || token->type == DR_REDIR)
		return (in_out_error(token));
	fd = open(token->str, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf_err("minishell: ", ": ", token->str);
		perror(0);
		g_data->exit_value = 1;
		return (-1);
	}
	return (fd);
}

int	existing_file_out(t_token *token, int fd, t_type type)
{
	if (fd > 1)
		close(fd);
	if (!token || token->str[0] == ';' || token->str[0] == '&' \
	|| token->type == SL_REDIR || token->type == SR_REDIR \
	|| token->type == DL_REDIR || token->type == DR_REDIR)
		return (in_out_error(token));
	if (type == SR_REDIR)
		fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf_err("minishell: ", ": ", token->str);
		perror(0);
		g_data->exit_value = 1;
		return (-1);
	}
	return (fd);
}

t_token	*new_exec_token(t_token *old)
{
	t_token	*new;
	t_token	*tmp;

	tmp = old;
	new = NULL;
	while (tmp)
	{
		if (tmp->type == SL_REDIR || tmp->type == SR_REDIR \
		|| tmp->type == DR_REDIR || tmp->type == DL_REDIR)
		{
			tmp = tmp->next;
			while (tmp && tmp->type != ARGV)
				tmp = tmp->next;
			tmp = tmp->next;
			if (tmp && tmp->type == SPACES)
				tmp = tmp->next;
		}
		else
		{
			add_token(&new, ft_strjoin(NULL, tmp->str), tmp->type);
			tmp = tmp->next;
		}
	}
	return (new);
}

void	set_fd_redir(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_token	*new;

	tmp = *cmd;
	while (tmp)
	{
		if (is_there_input_redir(tmp->token) \
		|| is_there_output_redir(tmp->token))
			files_handler(tmp, tmp->token);
		if (tmp->fd_in == -1 || tmp->fd_out == -1)
		{
			free_cmd(cmd);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = *cmd;
	while (tmp)
	{
		new = new_exec_token(tmp->token);
		free_token(&(tmp->token));
		tmp->token = new;
		tmp = tmp->next;
	}
}
