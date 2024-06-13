/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:46 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:49 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_there_builtin(t_token *token)
{
	if (is_valid_builtin("echo", token->str, 1) || \
	is_valid_builtin("cd", token->str, 0) || \
	is_valid_builtin("pwd", token->str, 1) || \
	is_valid_builtin("export", token->str, 0) || \
	is_valid_builtin("unset", token->str, 0) || \
	is_valid_builtin("env", token->str, 1) || \
	is_valid_builtin("exit", token->str, 0))
		return (1);
	return (0);
}

int	is_there_type(t_token *token, t_type type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_there_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SL_REDIR || tmp->type == DL_REDIR || \
		tmp->type == SR_REDIR || tmp->type == DR_REDIR)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_there_input_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SL_REDIR || tmp->type == DL_REDIR)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_there_output_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SR_REDIR || tmp->type == DR_REDIR)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
