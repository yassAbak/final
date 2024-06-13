/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeu1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:45 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:47 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_to_token(t_token *token, int nb_pipe)
{
	t_token	*tmp;
	t_token	*new;
	int		nb;

	new = NULL;
	tmp = token;
	nb = nb_pipe;
	while (nb > 0)
	{
		if (tmp->type == PIPE)
			nb--;
		tmp = tmp->next;
	}
	if (tmp && tmp->type == SPACES)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		add_token(&new, ft_strjoin(NULL, tmp->str), tmp->type);
		tmp = tmp->next;
	}
	return (new);
}

int	pipe_error_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SL_REDIR || tmp->type == DL_REDIR || \
		tmp->type == SR_REDIR || tmp->type == DR_REDIR)
		{
			tmp = tmp->next;
			while (tmp && tmp->type == SPACES)
				tmp = tmp->next;
			if (!tmp)
			{
				ft_putstr_fd("minishell: syntax error \
				near unexpected token `|\'\n", 2);
				g_data->exit_value = 258;
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	pipe_error_no_arg(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type != SPACES)
			count = 1;
		tmp = tmp->next;
	}
	if (!count)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|\'\n", 2);
		g_data->exit_value = 258;
		return (0);
	}
	return (1);
}

int	pipe_error_handler(void)
{
	t_cmd	*tmp;

	tmp = g_data->cmd;
	while (tmp)
	{
		if (!pipe_error_no_arg(tmp->token) || !pipe_error_redir(tmp->token))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
