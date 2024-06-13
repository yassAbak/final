/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:11:05 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:11:07 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char *str, int len)
{
	char	*dest;
	int		i;

	i = -1;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (0);
	while (++i < len)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}
