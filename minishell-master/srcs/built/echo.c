/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:27 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:29 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_only_spaces(t_token *token)
{
	t_token		*tmp;

	tmp = token;
	while (tmp && tmp->type == SPACES)
		tmp = tmp->next;
	if (tmp)
		return (0);
	return (1);
}

int	is_option(t_token *token, int *flag)
{
	int	i;

	i = 0;
	if (token->str[0] == '-')
	{
		i++;
		while (token->str[i] && token->str[i] == 'n')
			i++;
		if (!token->str[i])
		{
			*flag = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_echo(t_token *token)
{
	int		flag;
	t_token	*tmp;

	flag = 0;
	tmp = token->next;
	while (tmp)
	{
		while (tmp && tmp->type == SPACES)
			tmp = tmp->next;
		if (tmp && is_option(tmp, &flag))
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPACES)
				tmp = tmp->next;
		}
		while (tmp)
		{
			if (!is_only_spaces(tmp))
				ft_putstr_fd(tmp->str, 1);
			tmp = tmp->next;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (g_data->exit_value = 0);
}
