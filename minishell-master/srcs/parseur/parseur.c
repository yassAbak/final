/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:34 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:36 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parser_quote(t_token *lexed)
{
	t_token	*tmp;

	tmp = NULL;
	if (g_data->squote_open != -1 || g_data->dquote_open != -1)
		parser_quote_handler(lexed, &tmp);
	return (tmp);
}

void	parser(void)
{
	t_token	*token;

	token = NULL;
	if (g_data->squote_open != -1 || g_data->dquote_open != -1)
	{
		if (g_data->squote_open == 1 || g_data->dquote_open == 1)
		{
			g_data->exit_value = 1;
			ft_putstr_fd("minishell: doesn't handle opened quotes\n", 2);
			free_token(&(g_data->token));
			return ;
		}
		token = parser_quote(g_data->token);
		free_token(&(g_data->token));
		g_data->token = token;
	}
	if (is_successive_pipes(g_data->token))
	{
		g_data->exit_value = 1;
		ft_putstr_fd("minishell: doesn't handle multiple pipes\n", 2);
		free_token(&(g_data->token));
		return ;
	}
	if (g_data->token)
		prepare_token_to_exec(g_data->token);
}
