/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:55 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:57 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg(char *str)
{
	if ((not_alnum(str)))
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_data->exit_value = 1;
		return (0);
	}
	return (1);
}

int	ft_strlen_env(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

void	del_elem_env(t_token *arg, t_env *env)
{
	t_env	*before;
	t_env	*actual;
	t_env	*after;

	actual = env;
	before = NULL;
	while (actual)
	{
		after = actual->next;
		if (!ft_strncmp(actual->str, arg->str, ft_strlen_env(actual->str)))
		{
			if (before == NULL)
				env = after;
			else if (!after)
				before->next = NULL;
			else
				before->next = after;
			free(actual->str);
			free(actual);
			if (before == NULL)
				actual = env;
		}
		before = actual;
		actual = after;
	}
}

void	ft_unset(t_token *token)
{
	t_token	*arg;

	arg = token->next;
	while (arg)
	{
		if (arg->type == SPACES || !check_arg(arg->str))
			arg = arg->next;
		else
		{
			del_elem_env(arg, g_data->env);
			arg = arg->next;
		}
	}
}
