/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:23 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:25 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokensize(t_token *token, int pipe)
{
	t_token	*tmp;
	int		i;
	int		nb;

	i = 0;
	nb = pipe;
	tmp = token;
	while (nb > 0)
	{
		if (tmp->type == PIPE)
			nb--;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != SPACES)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
