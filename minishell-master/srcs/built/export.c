/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:43 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:46 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_export(t_token *arg)
{
	int	i;

	i = 0;
	while (arg->str[i])
	{
		if (arg->type == SPACES)
			return (0);
		if (((arg->str[0] >= '0' && arg->str[0] <= '9') \
		|| !ft_isalnum(arg->str[i])))
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg->str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_data->exit_value = 1;
			return (0);
		}
		i++;
		if (arg->str[i] == '=')
			break ;
	}
	return (1);
}

int	find_char(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	handle_no_param(t_env *env)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!find_char(tmp->str, '='))
			printf("export %s\n", tmp->str);
		else
		{
			i = -1;
			printf("export ");
			while (tmp->str[++i] != '=')
				printf("%c", tmp->str[i]);
			printf("%c\"", tmp->str[i++]);
			while (tmp->str[i])
				printf("%c", tmp->str[i++]);
			printf("\"\n");
		}
		tmp = tmp->next;
	}
	return (1);
}

int	replace_var(t_env *env, t_token *arg)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, arg->str, (ft_strlen_env(tmp->str))) == 0)
		{
			free(tmp->str);
			tmp->str = ft_strndup(arg->str, ft_strlen(arg->str));
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_token *token, t_env *env)
{
	t_token	*arg;

	arg = token->next;
	if (arg && arg->type == SPACES)
		arg = arg->next;
	if (!arg)
		return (handle_no_param(env));
	while (arg)
	{
		if (error_export(arg))
		{
			if (replace_var(env, arg) == 0)
				add_env(&env, arg->str);
		}
		arg = arg->next;
	}
	return (0);
}
