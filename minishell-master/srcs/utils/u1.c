/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:31 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:33 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(char *str)
{
	if (str)
		printf("%s\n", str);
	if (g_data->token)
		free_token(&(g_data->token));
	if (g_data->cmd)
		free_cmd(&(g_data->cmd));
	return (-2);
}

int	is_successive_pipes(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			if (ft_strlen(tmp->str) > 1)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	free_token(t_token **token)
{
	t_token	*swap;

	if (!(*token) || !token)
		return ;
	while (*token)
	{
		swap = (*token)->next;
		free((*token)->str);
		free(*token);
		*token = swap;
	}
	*token = NULL;
}

void	free_env(t_env **env)
{
	t_env	*swap;

	if (!(*env))
		return ;
	while (*env)
	{
		swap = (*env)->next;
		free((*env)->str);
		free(*env);
		*env = swap;
	}
	*env = NULL;
}

char	**tenv_to_tab(t_env *env)
{
	char	**tab;
	int		i;
	t_env	*tmp;

	tab = malloc(sizeof(char *) * (ft_envsize(g_data->env) + 1));
	if (!tab)
		return (NULL);
	tmp = env;
	i = -1;
	while (++i < ft_envsize(g_data->env))
	{
		tab[i] = ft_strndup(tmp->str, ft_strlen(tmp->str));
		tmp = tmp->next;
	}
	tab[ft_envsize(g_data->env)] = NULL;
	return (tab);
}
