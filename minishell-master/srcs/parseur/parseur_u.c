/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:29 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:31 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dollar_before_quote(t_token *token)
{
	int	i;

	i = 0;
	if (token->type == ARGV)
	{
		while (token->str[i])
			i++;
		if (token->str[i - 1] == '$' && (token->next->type == S_QUOTE_OPEN \
		|| token->next->type == D_QUOTE_OPEN))
			return (1);
	}
	return (0);
}

void	find_correct_dquote_type(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == D_QUOTE_CLOSE)
		{
			count++;
			if (count % 2 != 0)
				tmp->type = D_QUOTE_OPEN;
		}
		tmp = tmp->next;
	}
}

void	parser_quote_handler(t_token *lexed, t_token **token)
{
	char	*word;
	t_token	*tmp;
	int		ref;

	tmp = lexed;
	while (tmp)
	{
		word = NULL;
		if (tmp->type == S_QUOTE_OPEN || tmp->type == D_QUOTE_OPEN)
		{
			ref = (int)tmp->type;
			tmp = tmp->next;
			while ((int)tmp->type != ref + 1)
			{
				word = ft_strjoin(word, tmp->str);
				tmp = tmp->next;
			}
			add_token(token, word, ARGV);
		}
		else if (!is_dollar_before_quote(tmp))
			add_token(token, ft_strjoin(NULL, tmp->str), -1);
		tmp = tmp->next;
	}
}

void	prepare_token_to_exec(t_token *token)
{
	t_token	*new;
	char	*word;
	t_token	*tmp;

	new = NULL;
	tmp = token;
	while (tmp)
	{
		word = ft_strjoin(NULL, tmp->str);
		if (tmp->type == ARGV)
		{
			while (tmp->next && tmp->type == ARGV && tmp->next->type == ARGV)
			{
				tmp = tmp->next;
				word = ft_strjoin(word, tmp->str);
			}
			add_token(&new, word, ARGV);
		}
		else
			add_token(&new, word, -1);
		tmp = tmp->next;
	}
	free_token(&(g_data->token));
	g_data->token = new;
}
