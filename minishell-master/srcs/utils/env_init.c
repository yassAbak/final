/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:15 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:17 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_elem_env(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = ft_strndup(str, ft_strlen(str));
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	if (!str)
		return ;
	new = create_elem_env(str);
	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "OLDPWD=", 7) != NULL)
			i++;
		add_env(&env, envp[i]);
	}
	return (env);
}
