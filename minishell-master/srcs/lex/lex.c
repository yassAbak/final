/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:22 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:24 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_type_handler(char *str, int *i, t_token **token)
{
	char	*word;

	word = NULL;
	if (str[*i] == '<' || str[*i] == '>')
		word = lexer_redir_handler(str, word, i);
	else if (str[*i] == '|')
		word = lexer_pipe_handler(str, word, i);
	else if (ft_isspace(str[*i]))
		word = lexer_space_handler(str, word, i);
	else if (str[*i] == '\'')
		word = lexer_squote_handler(str, word, i);
	else if (str[*i] == '"')
		word = lexer_dquote_handler(str, word, i);
	else
		word = lexer_char_handler(str, word, i);
	add_token(token, word, -1);
}

char	*dollar_loop(char *str, int *i, t_env *env)
{
	char	*dest;

	dest = NULL;
	while (str[(*i)])
	{
		if (str[*i] == '\'')
			dest = lexer_squote_handler(str, dest, i);
		else if (str[*i] == '"')
			dest = lexer_dquote_handler(str, dest, i);
		else if (str[(*i)] == '$')
			dest = lexer_dollar_handler(str, dest, i, env);
		else
			dest = ft_strjoin_char(dest, str[*i]);
		(*i)++;
	}
	return (dest);
}

void	lexer(char *str, t_env *env)
{
	t_token	*token;
	char	*newstr;
	int		i;	

	token = NULL;
	i = 0;
	if (str[i])
		add_history(str);
	while (str[i] && ft_isspace(str[i]))
		i++;
	newstr = dollar_loop(str, &i, env);
	if (!newstr)
	{
		g_data->exit_value = 0;
		return ;
	}
	g_data->squote_open = -1;
	g_data->dquote_open = -1;
	i = -1;
	while (newstr[++i])
		lexer_type_handler(newstr, &i, &token);
	free(newstr);
	g_data->token = token;
}
