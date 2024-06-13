/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:36 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:39 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_path(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

int	is_opened(char c)
{
	if (c == '\'')
	{
		if (g_data->squote_open == OPENED)
			return (OPENED);
		else
			return (CLOSED);
	}
	else if (c == '"')
	{
		if (g_data->dquote_open == OPENED)
			return (OPENED);
		else
			return (CLOSED);
	}
	return (0);
}

void	ft_waitpid(pid_t pid)
{
	int	exit;

	waitpid(pid, &exit, 0);
	if (WIFEXITED(exit))
		g_data->exit_value = WEXITSTATUS(exit);
	else if (WIFSIGNALED(exit))
		g_data->exit_value = 128 + WTERMSIG(exit);
}

int	how_many(t_token *token, t_type type)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == type)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
