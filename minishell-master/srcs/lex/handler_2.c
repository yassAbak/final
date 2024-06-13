/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:17 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:19 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lexer_dquote_handler(char *str, char *dest, int *i)
{
	dest = ft_strjoin_char(dest, str[*i]);
	if ((g_data->dquote_open) < 1 && g_data->squote_open < 1)
		g_data->dquote_open = 1;
	else if (g_data->squote_open < 1)
		g_data->dquote_open = 0;
	return (dest);
}

char	*lexer_squote_handler(char *str, char *dest, int *i)
{
	dest = ft_strjoin_char(dest, str[*i]);
	if (g_data->squote_open < 1 && g_data->dquote_open < 1)
		g_data->squote_open = 1;
	else if (g_data->dquote_open < 1)
		g_data->squote_open = 0;
	return (dest);
}

char	*dollar_envp(char *str, char *dest, int *i, t_env *env)
{
	int		end;
	char	*name;
	t_env	*tmp;

	end = *i;
	tmp = env;
	while (str[end + 1] && ft_isalnum(str[end + 1]))
		end++;
	name = ft_strndup(&str[*i + 1], end - (*i));
	while (tmp && !(ft_strnstr_bis(tmp->str, name, end - (*i))))
		tmp = tmp->next;
	free(name);
	if (tmp)
		dest = ft_strjoin(dest, (tmp->str + (end + 1 - (*i))));
	*i = end;
	return (dest);
}

char	*lexer_dollar_handler(char *str, char *dest, int *i, t_env *env)
{
	char	*value;

	if (g_data->squote_open < 1)
	{
		if (str[(*i) + 1] == '?')
		{
			value = ft_itoa(g_data->exit_value);
			dest = ft_strjoin(dest, value);
			free(value);
			(*i)++;
		}
		else if (ft_isalnum(str[(*i) + 1]))
			dest = dollar_envp(str, dest, i, env);
		else if (str[(*i) + 1] == '$')
		{
			dest = ft_strjoin_char(dest, str[(*i)]);
			dest = ft_strjoin_char(dest, str[(*i) + 1]);
			(*i)++;
		}
		else
			dest = ft_strjoin_char(dest, str[*i]);
	}
	else
		dest = ft_strjoin_char(dest, str[*i]);
	return (dest);
}
