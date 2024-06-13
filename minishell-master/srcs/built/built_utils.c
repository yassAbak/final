/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:03 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:06 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_err_strerror(char *cmd, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	is_valid_builtin(char *target, char *str, int allchar)
{
	int	i;
	int	add;

	i = -1;
	if (allchar)
	{
		while (str[++i])
		{
			add = 0;
			if (str[i] >= 65 && str[i] <= 90)
				add = 32;
			if ((str[i] + add) != target[i])
				return (0);
		}
		if (str[i] || target[i])
			return (0);
	}
	else if (ft_strncmp(target, str, ft_strlen(target)) != 0 \
	|| (ft_strlen(target) != ft_strlen(str)))
		return (0);
	return (1);
}

void	builtin_handler(t_token *token, int pipeflag)
{
	if (is_valid_builtin("echo", token->str, 1))
		ft_echo(token);
	else if (is_valid_builtin("cd", token->str, 0))
		ft_cd(token, g_data->env);
	else if (is_valid_builtin("pwd", token->str, 1))
		ft_pwd();
	else if (is_valid_builtin("export", token->str, 0))
		ft_export(token, g_data->env);
	else if (is_valid_builtin("unset", token->str, 0))
		ft_unset(token);
	else if (is_valid_builtin("env", token->str, 1))
		ft_env(g_data->env);
	else if (is_valid_builtin("exit", token->str, 0))
		ft_exit(token, pipeflag);
}

void	builtin_handler_parent(t_token *token)
{
	if (is_valid_builtin("cd", token->str, 0))
		ft_cd(token, g_data->env);
	else if (is_valid_builtin("export", token->str, 0))
		ft_export(token, g_data->env);
	else if (is_valid_builtin("unset", token->str, 0))
		ft_unset(token);
	else if (is_valid_builtin("exit", token->str, 0))
		ft_exit(token, 0);
}
