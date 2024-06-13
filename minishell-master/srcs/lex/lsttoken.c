/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:27 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:29 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_type	what_type(char *word, t_type type)
{
	if ((int)type != -1)
		return (type);
	else if (*word == '\'' && is_opened('\'') && !is_opened('"'))
		return (S_QUOTE_OPEN);
	else if (*word == '\'' && !is_opened('\'') && !is_opened('"'))
		return (S_QUOTE_CLOSE);
	else if (*word == '"' && is_opened('"') && !is_opened('\''))
		return (D_QUOTE_OPEN);
	else if (*word == '"' && !is_opened('"') && !is_opened('\''))
		return (D_QUOTE_CLOSE);
	else if (*word == '<' && word[1] == '<')
		return (DL_REDIR);
	else if (*word == '>' && word[1] == '>')
		return (DR_REDIR);
	else if (*word == '<')
		return (SL_REDIR);
	else if (*word == '>')
		return (SR_REDIR);
	else if (*word == '|')
		return (PIPE);
	else if (ft_isspace(*word))
		return (SPACES);
	else
		return (ARGV);
}

t_token	*create_token(char *word, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strndup(word, ft_strlen(word));
	new->next = NULL;
	new->type = what_type(word, type);
	return (new);
}

void	add_token(t_token **token, char *word, t_type type)
{
	t_token	*tmp;
	t_token	*new;

	new = create_token(word, type);
	if (word)
		free(word);
	if (!(*token))
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
