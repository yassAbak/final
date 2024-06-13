/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isaln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:46:49 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:46:51 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
