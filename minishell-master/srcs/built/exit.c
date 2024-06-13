/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:38 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:41 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arg(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type != SPACES)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	handle_arg_one(char *str, int pipeflag)
{
	long long	exit_value;

	if (ft_isdigit_str(str))
	{
		exit_value = ft_atoi(str) % 256;
		if (!pipeflag && isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", 2);
		free_all(pipeflag);
		exit(exit_value);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_all(pipeflag);
	exit(255);
}

void	handle_no_arg(int pipeflag)
{
	if (!pipeflag && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	free_all(pipeflag);
	exit(0);
}

void	ft_exit(t_token *token, int pipeflag)
{
	t_token	*arg;
	int		count;

	arg = token->next;
	count = count_arg(arg);
	if (arg && arg->type == SPACES)
		arg = arg->next;
	if (arg && count == 1)
		handle_arg_one(arg->str, pipeflag);
	else if (arg && count > 1)
	{
		if (!ft_isdigit_str(arg->str))
			handle_arg_one(arg->str, pipeflag);
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", 2);
		g_data->exit_value = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (pipeflag)
			exit(1);
	}
	else
		handle_no_arg(pipeflag);
}
