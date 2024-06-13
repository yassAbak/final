/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:20 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:23 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_shell_level(t_env *env)
{
	int		shell_level;

	while (env && env->next)
	{
		if (ft_strncmp("SHLVL=", env->str, 6) == 0)
		{
			shell_level = ft_atoi(&(env->str[6]));
			return (shell_level);
		}
		env = env->next;
	}
	return (1);
}

void	change_level(t_env *env)
{
	char	*level_char;
	int		shell_level;
	char	*shlvl;

	shell_level = get_shell_level(g_data->env) + 1;
	shlvl = ft_strndup("SHLVL=", 6);
	while (env && env->next)
	{
		if (ft_strncmp("SHLVL=", env->str, 6) == 0)
		{
			free(env->str);
			level_char = ft_itoa(shell_level);
			env->str = ft_strjoin(shlvl, level_char);
			free(level_char);
			return ;
		}
		env = env->next;
	}
}
