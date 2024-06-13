/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:19 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:22 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_token *token, t_env *env)
{
	t_token	*arg;

	arg = token->next;
	if (arg && arg->type == SPACES)
		arg = arg->next;
	if (!arg)
		return (change_path(env, "HOME", "HOME=", 5));
	else if (ft_strncmp_bis(arg->str, '-') == 0)
	{
		if (change_path(env, "OLDPWD", "OLDPWD=", 7) != -1)
			ft_pwd();
	}
	else
	{
		oldpwd_change(env);
		if (chdir(arg->str) == -1)
		{
			printf_err_strerror("cd", arg->str);
			g_data->exit_value = 1;
		}
		pwd_change(env);
	}
	return (0);
}
