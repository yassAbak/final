/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:11 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:13 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lexer_redir_handler(char *str, char *dest, int *i)
{
	dest = ft_strjoin_char(dest, str[*i]);
	if ((str[*i] == '<' && str[(*i) + 1] == '<') || \
	(str[*i] == '>' && str[(*i) + 1] == '>'))
	{
		dest = ft_strjoin_char(dest, str[(*i) + 1]);
		(*i)++;
	}
	return (dest);
}

char	*lexer_pipe_handler(char *str, char *dest, int *i)
{
	while (str[*i] && str[*i] == '|')
	{
		dest = ft_strjoin_char(dest, str[*i]);
		if (!str[(*i) + 1] || str[(*i) + 1] != '|')
			break ;
		(*i)++;
	}
	return (dest);
}

char	*lexer_space_handler(char *str, char *dest, int *i)
{
	while (str[*i] && ft_isspace(str[(*i)]))
	{
		dest = ft_strjoin_char(dest, str[*i]);
		if (!str[(*i) + 1] || !ft_isspace(str[(*i + 1)]))
			break ;
		(*i)++;
	}
	return (dest);
}

char	*lexer_char_handler(char *str, char *dest, int *i)
{
	while (str[*i] && what_type(&str[*i], -1) == ARGV)
	{
		dest = ft_strjoin_char(dest, str[*i]);
		if (!str[(*i) + 1] || what_type(&str[(*i) + 1], -1) != ARGV)
			break ;
		(*i)++;
	}
	return (dest);
}
