/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:07 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:10 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_char(char *s1, char c)
{
	int		lens1;
	char	*dest;
	int		i;

	lens1 = ft_strlen(s1);
	dest = malloc(sizeof(char) * (lens1 + 2));
	if (!dest)
		return (0);
	i = -1;
	if (s1)
		while (s1[++i])
			dest[i] = s1[i];
	if (c)
		(dest + lens1)[0] = c;
	(dest + lens1)[1] = '\0';
	if (s1)
		free(s1);
	return (dest);
}
