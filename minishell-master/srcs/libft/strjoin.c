/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:11:22 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:11:24 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		lens1;
	int		lens2;
	char	*dest;
	int		i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!lens1 && !lens2)
		return (NULL);
	dest = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!dest)
		return (0);
	i = -1;
	if (s1)
		while (s1[++i])
			dest[i] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			(dest + lens1)[i] = s2[i];
	(dest + lens1)[i] = '\0';
	if (s1)
		free(s1);
	return (dest);
}

char	*ft_strjoin_no_free(char *s1, char *s2)
{
	int		lens1;
	int		lens2;
	char	*dest;
	int		i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!lens1 && !lens2)
		return (NULL);
	dest = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!dest)
		return (0);
	i = -1;
	if (s1)
		while (s1[++i])
			dest[i] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			(dest + lens1)[i] = s2[i];
	(dest + lens1)[i] = '\0';
	return (dest);
}
