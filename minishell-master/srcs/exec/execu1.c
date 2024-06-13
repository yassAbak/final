/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execu1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:00 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:03 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**token_to_tab(t_token *token)
{
	t_token	*tmp;
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (tokensize(token, 0) + 1));
	if (!tab)
		return (NULL);
	tmp = token;
	i = 0;
	while (i < tokensize(token, 0))
	{
		if (tmp->type != SPACES)
		{
			tab[i] = ft_strndup(tmp->str, ft_strlen(tmp->str));
			i++;
		}
		tmp = tmp->next;
	}
	tab[tokensize(token, 0)] = NULL;
	return (tab);
}

char	*getpath_annex(char **splitpath, char *cmd)
{
	int		i;
	char	*finalpath;

	i = -1;
	while (splitpath[++i])
	{
		finalpath = ft_strjoin_no_free(splitpath[i], "/");
		finalpath = ft_strjoin(finalpath, cmd);
		if (access(finalpath, F_OK) == 0)
		{
			ft_free_tab(splitpath);
			return (finalpath);
		}
		free(finalpath);
	}
	ft_free_tab(splitpath);
	return (NULL);
}

char	*getpath(char *cmd, char **envp)
{
	int		i;
	char	**splitpath;

	i = 0;
	if (cmd[0] == '\0')
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[i] && !(ft_strnstr_bis(envp[i], "PATH", 4)))
		i++;
	if (!envp[i])
		return (NULL);
	splitpath = ft_split(envp[i] + 5, ':');
	return (getpath_annex(splitpath, cmd));
}

int	check_parent_builtin(char **args, char **envp, t_cmd **cmd)
{
	int	old_in;
	int	old_out;

	old_in = dup(0);
	old_out = dup(1);
	if (is_valid_builtin("cd", (*cmd)->token->str, 0) || \
	is_valid_builtin("export", (*cmd)->token->str, 0) || \
	is_valid_builtin("unset", (*cmd)->token->str, 0) || \
	is_valid_builtin("exit", (*cmd)->token->str, 0))
	{
		ft_free_tab(envp);
		if (args)
			ft_free_tab(args);
		dup_all_fd((*cmd));
		close_fds_cmd((*cmd));
		builtin_handler_parent((*cmd)->token);
		if ((*cmd)->fd_in)
			dup2(old_in, STDIN_FILENO);
		if ((*cmd)->fd_out > 1)
			dup2(old_out, STDOUT_FILENO);
		return (0);
	}
	else
		return (1);
}

void	token_to_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	while (++i <= how_many(g_data->token, PIPE))
		add_cmd(cmd);
	tmp = *cmd;
	i = -1;
	while (tmp && ++i > -1)
	{
		tmp->token = NULL;
		tmp->token = token_to_token(g_data->token, i);
		tmp->fd_in = 0;
		tmp->fd_out = 1;
		tmp = tmp->next;
	}
	if (i > 0)
		set_fd_pipes(cmd);
	set_fd_redir(cmd);
	free_token(&(g_data->token));
}
