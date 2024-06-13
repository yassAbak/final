/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:56 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:58 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	in_out_error(t_token *token)
{
	ft_putstr_fd ("minishell: syntax error near unexpected token `", 2);
	if (!token)
		ft_putstr_fd ("newline\'\n", 2);
	else if (token->str[0] == ';')
		ft_putstr_fd (";\'\n", 2);
	else if (token->str[0] == '&')
		ft_putstr_fd ("&\'\n", 2);
	else
	{
		ft_putstr_fd (token->str, 2);
		ft_putstr_fd ("\'\n", 2);
	}
	g_data->exit_value = 258;
	return (-1);
}

void	gnl_and_write(char *str, int fd)
{
	char	*buff;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_heredoc);
	while (1)
	{
		buff = readline("> ");
		if (!buff || !ft_strcmp(str, buff))
			break ;
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	close(fd);
	if (g_data->heredoc != -1)
		dup2(g_data->heredoc, STDIN_FILENO);
}

int	create_tmp_heredoc(t_token *token, int fd)
{
	int	fd_hd[2];

	if (fd > 0)
		close(fd);
	if (!token || token->str[0] == ';' || token->str[0] == '&' \
	|| token->type == SL_REDIR || token->type == SR_REDIR \
	|| token->type == DL_REDIR || token->type == DR_REDIR)
		return (in_out_error(token));
	if (pipe(fd_hd) == -1)
	{
		printf_err("minishell: ", ": ", token->str);
		perror(0);
		g_data->exit_value = 1;
		return (-1);
	}
	gnl_and_write(token->str, fd_hd[1]);
	if (g_data->heredoc != -1)
	{
		g_data->heredoc = -1;
		return (-1);
	}
	return (fd_hd[0]);
}
